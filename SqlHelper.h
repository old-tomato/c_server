//
// Created by zkl on 11/28/17.
//

#ifndef SRS_C_SERVER_SQLHELPER_H
#define SRS_C_SERVER_SQLHELPER_H

#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class SqlHelper {
private:
    MYSQL * mysql = NULL;
    static SqlHelper * helper;
    SqlHelper(){};
    void initConnect();
public:
    static SqlHelper * getInstance();
    vector<vector<string*>*> * select(string sql , int * fieldCount);
    int execute(string sql);
    void freeMySqlRes(vector<vector<string*>* > * resData);
    void killConnect();
};


#endif //SRS_C_SERVER_SQLHELPER_H
