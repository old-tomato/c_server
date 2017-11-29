//
// Created by zkl on 11/28/17.
//

#include <cstring>
#include "ServerContent.h"
#include "LoginController.h"

ServerContent *sc;

struct ClientInfo {
    uv_stream_t *client;
    uv_buf_t *buf;
};

ClientInfo *getNewClientInfo(uv_stream_t *stream, const uv_buf_t *buf) {
    ClientInfo *clientInfo = new ClientInfo;
    clientInfo->client = stream;
    clientInfo->buf = new uv_buf_t;
    size_t len = buf->len;
    clientInfo->buf->len = len;
    clientInfo->buf->base = new char[len];
    memcpy(clientInfo->buf->base, buf->base, len);
    return clientInfo;
}

void onCreateThread(void* arg){
    int result;
    ClientInfo *clientInfo = (ClientInfo *)arg;
    if(sc->afterGetDataCallBack == NULL){
        cout << "callback is null , just clear" << endl;
        goto END;
    }
    result = sc->afterGetDataCallBack(clientInfo->client , clientInfo->buf);
    if(result == 0){
        cout << "return 0" << endl;
        goto END;
    } else{
        cout << "return not 0 " << endl;
        goto END;
    }

    END:
    delete[] clientInfo->buf->base;
    uv_close((uv_handle_t *)clientInfo->client , NULL);
    cout << "pthread : " << pthread_self() << "buf->base : " << &(clientInfo->buf->base) << " will exit " << endl;
}

void onAlloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->len = suggested_size;
    buf->base = new char[suggested_size];
}


void onRead(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
    if (nread < 0) {
        cout << "nread < 0" << endl;
        if (nread == UV_EOF) {
            cout << "nread error" << endl;
        }else{

        }
    }
    if (nread == 0) {
        // how to get there
        cout << "nread == 0" << endl;
    }
    if (nread > 0) {
        cout << "nread > 0" << endl;

        ClientInfo *clientInfo = getNewClientInfo(stream, buf);

        uv_thread_t uvt;
        uv_thread_create(&uvt , onCreateThread , (void*)clientInfo);

    }
    delete[] buf->base;
}



void onConnect(uv_stream_t *server, int status) {
    if (status < 0) {
        cout << "connect error" << endl;
        return;
    }

    cout << "get connect " << endl;

    // init client
    uv_tcp_t *client = new uv_tcp_s;
    uv_tcp_init(sc->getLoop(), client);
    if (uv_accept(server, (uv_stream_t *) client) == 0) {
        cout << "accept success" << endl;
        // start to read
        uv_read_start((uv_stream_t *) client, onAlloc, onRead);
    } else {
        cout << "accept failed" << endl;
    }
}

uv_tcp_t server;

void ServerContent::start() {

    sc = this;

    uv_tcp_init(defaultLoop, &server);

    sockaddr_in addr;
    uv_ip4_addr(serverIp.c_str(), port, &addr);

    uv_tcp_bind(&server, (sockaddr *) &addr, 0);

    uv_listen((uv_stream_t *) &server, backLog, onConnect);

    uv_run(defaultLoop, UV_RUN_DEFAULT);
}