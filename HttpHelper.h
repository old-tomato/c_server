//
// Created by zkl on 11/28/17.
//

#ifndef SRS_C_SERVER_HTTPHELPER_H
#define SRS_C_SERVER_HTTPHELPER_H

#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

class HttpHelper {
private:

    string request;
    string route;
    string content;
    int requestType;
    string httpVersion;

public:
    static const int GET = 0;
    static const int POST = 1;

    explicit HttpHelper(string request);
    string getContent();
    string getRoute();

    string responseJson(int code , string message);
};


#endif //SRS_C_SERVER_HTTPHELPER_H
