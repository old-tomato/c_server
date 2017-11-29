#include <iostream>
#include <utility>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <mysql/mysql.h>
#include <cjson/cJSON.h>

#include "ServerContent.h"
#include "HttpHelper.h"
#include "SqlHelper.h"
#include "LoginController.h"

using namespace std;

void onAfterWrite(uv_write_t* req, int status){
    if(status < 0){
        cout << "write failed" << endl;
    }else{
        cout << "write success" << endl;
    }
}

int doWork(string route , string content , string ** result){
    if(boost::starts_with(route , "/login")){
        LoginController loginC;
        loginC.loginRoute(route , content , result);
    }
    return 0;
}

int afterGetDataCallBack(uv_stream_t * client , const uv_buf_t * buf){
    HttpHelper helper(buf->base);

    string content = helper.getContent();
    string route = helper.getRoute();
    cout << content << endl;
    cout << route << endl;

    string * resultData;

    doWork( route,  content, &resultData);

    cout << *resultData << endl;

//    string data = helper.responseJson(200 , *resultData);
//    uv_write_t * uvw = new uv_write_t;
//    uv_buf_t bufBack = uv_buf_init(const_cast<char *>(data.c_str()), data.length());
//    uv_write(uvw , client , &bufBack , 1 , onAfterWrite);

    return 0;
}

int main() {

    ServerContent sv;
    sv.afterGetDataCallBack = afterGetDataCallBack;
    sv.start();

    return 0;
}