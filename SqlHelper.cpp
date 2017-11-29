//
// Created by zkl on 11/28/17.
//

#include "SqlHelper.h"

SqlHelper * SqlHelper::helper = NULL;

SqlHelper * SqlHelper::getInstance(){
    if(helper == NULL){
        helper = new SqlHelper();
        helper->initConnect();
    }
    return helper;
}

void SqlHelper::initConnect(){
    cout << "init connect : " << mysql << endl;
    mysql = mysql_init(mysql);
    if(mysql == NULL){
        cout << "mysql init error" << endl;
        return;
    }
    cout << "init success" << endl;

    mysql = mysql_real_connect(mysql , "127.0.0.1" , "root" , "1111" , "srs_database" , 3306 , NULL , 0);
    cout << mysql_error(mysql) << endl;
    if(mysql == NULL){
        cout << "mysql connect error" << endl;
        return;
    }
    cout << "connect success" << endl;
}

vector<vector<string*>*> * SqlHelper::select(string sql , int * fieldCount){
    if(mysql == NULL){
        cout << "conn not ready" << endl;
        return NULL;
    }

    int result = mysql_query(mysql , sql.c_str());
    if(result != 0){
        cout << "mysql query error : " << mysql_error(mysql) << endl;
        return NULL;
    }
    *fieldCount = mysql_field_count(mysql);
    MYSQL_RES * res = NULL;
    res = mysql_store_result(mysql);
    if(res == NULL){
        return NULL;
    }
    
    vector<vector<string*>* > * resData = new vector<vector<string*>*>;

    MYSQL_ROW row;
    // fetch one row
    
    while((row = mysql_fetch_row(res)) != NULL){
        vector<string*> * data = new vector<string*>;
        for(int x = 0 ; x < *fieldCount ; ++ x){
            string* cellData = new string(row[x]);
            data->push_back(cellData);
        }
        resData->push_back(data);
    }

    return resData;
}

void SqlHelper::freeMySqlRes(vector<vector<string*>* > * resData){
    if(resData == NULL){
        return;
    }
    for(auto it = resData->begin() ; it != resData->end() ; ++ it){
        vector<string *> * t2 = *it;
        if(t2 == NULL){
            continue;
        }
        for(auto it2 = t2->begin() ; it2 != t2->end() ; ++ it2){
            delete *it2;
        }
        delete t2;
    }
    delete resData;

}

int SqlHelper::execute(string sql){
    if(mysql == NULL){
        return -1;
    }
    int i = mysql_query(mysql , sql.c_str());
    cout << i << endl;
    return i;
}

void SqlHelper::killConnect(){
    if(mysql == NULL){
        return;
    }
    mysql_close(mysql);

}