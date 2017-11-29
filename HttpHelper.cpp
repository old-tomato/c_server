//
// Created by zkl on 11/28/17.
//

#include "HttpHelper.h"

int findBlockIndex(string request, int *fromWindow) {
    if (boost::starts_with(request, "GET")) {
        return -2;
    }
    const char *str = request.c_str();
    for (int x = 0; x < request.length(); ++x) {
        if (x == (request.length() - 1)) {
            return -1;
        }
        if (str[x] == '\n' && str[x + 1] == '\n') {
            return x;
        }
        if ((x + 3) < request.length() - 1) {
            if (str[x] == '\r' && str[x + 1] == '\n' && str[x + 2] == '\r' && str[x + 3] == '\n') {
                *fromWindow = 1;
                return x;
            }
        }
    }
    return -1;
}

HttpHelper::HttpHelper(string req){
    this->request = req;
    string head;
    string body;
    int isFromWindows = 0;
    int index = findBlockIndex(request, &isFromWindows);
    if (index > -1) {
        head = request.substr(0, index);

        if (isFromWindows) {
            body = request.substr(index + 3, request.length());
        } else {
            body = request.substr(index + 1, request.length());
        }
    } else if (index == -2) {
        // get
        head = request;
        body = "";
    } else {
        // can not find data
        cout << "can not find data " << endl;
        return;
    }

    vector<string> headList;
    // sample
    boost::split(headList, head, boost::is_any_of("\n"));

    /**
     *  GET /request/login HTTP/1.1
        Host: 192.168.1.11:9009
        Connection: keep-alive
        Content-Length: 128
        Postman-Token: a1ab96ed-31a4-f298-9e3d-3e2790250194
        Cache-Control: no-cache
        Origin: chrome-extension://fhbjgbiflinjbdggehcddcbncdddomop
        User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36
        Content-Type: application/x-www-form-urlencoded
        Accept: '*'/*
        Accept-Encoding: gzip, deflate
        Accept-Language: zh-CN,zh;q=0.8
     */

    // POST or GET
    vector<string> firstLine;
    boost::split(firstLine, headList[0], boost::is_any_of(" "));
    // TODO need add other type
    this->requestType = firstLine[0] == "GET" ? this->GET : this->POST;
    this->route = string(firstLine[1]);
    this->httpVersion = string(firstLine[2]);

    if (this->requestType == POST) {
        this->content = body;
    }
}

string HttpHelper::responseJson(int code, string message) {
    string json = message;

    string data = "HTTP/1.1 ";

    data.append(boost::lexical_cast<string>(code))
            .append(" ")
            .append("OK")
            .append(" ")
            .append("\n")
            .append("Content-Type:application/json;charset=UTF-8\n")
            .append("Content-Length:").append(boost::lexical_cast<string>(json.length()))
            .append("\n\n")
            .append(json);

    return data;
}

string HttpHelper::getRoute() {
    return this->route;
}

string HttpHelper::getContent() {
    return this->content;
}
