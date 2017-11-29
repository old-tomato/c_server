//
// Created by zkl on 11/28/17.
//

#ifndef SRS_C_SERVER_SERVERCONTENT_H
#define SRS_C_SERVER_SERVERCONTENT_H

#include <string>
#include <utility>
#include <uv.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

class ServerContent {

private:
    int port = 9009;
    int backLog = 128;
    string path = "";
    string serverIp = "0.0.0.0";

    uv_loop_t * defaultLoop = uv_default_loop();



public:
    explicit ServerContent(int port = 9009) : port(port){};

    explicit ServerContent(uv_loop_t * loop , int port = 9009) : port(port),defaultLoop(loop){};

    void setServerIp(string serverIP)
    {
        this->serverIp = serverIP;
    }

    void start();

    uv_loop_t * getLoop(){
        return this->defaultLoop;
    }

    int (*afterGetDataCallBack)(uv_stream_t * client , const uv_buf_t * buf);
};


#endif //SRS_C_SERVER_SERVERCONTENT_H
