//
// Created by zkl on 11/28/17.
//

#include "LoginController.h"

int LoginController::loginRoute(string route, string content, string **result) {

    string path = route.substr(strlen("/login"), route.length());

    if (boost::equal(path, "/regist") == 0) {
        userRegist(content, result);
    }
    return 0;
}

int LoginController::userRegist(string content, string **result) {

    cJSON *obj = cJSON_Parse(content.c_str());
    cJSON *objUsername = cJSON_GetObjectItem(obj, "username");
    cJSON *objPassword = cJSON_GetObjectItem(obj, "password");
    cout << objUsername->valuestring << endl;
    cout << objPassword->valuestring << endl;


    SqlHelper *helper = SqlHelper::getInstance();

    ostringstream osql;
    osql << "insert into user_info (user_id , username , password , type , session , account_balance , create_time) "
         << "values ("
         << "111" << ","
         << "\"" << objUsername->valuestring << "\"" << ","
         << "\"" << objPassword->valuestring << "\"" << ","
         << 1 << ","
         << "\"" << "session" << "\"" << ","
         << 2.01 << ","
         << "now()"
         << ")";

    string sql = osql.str();
    cout << sql << endl;

    cout << "sql execute : " << helper->execute(sql) << endl;

    cJSON *objRes = cJSON_CreateObject();
    cJSON_AddStringToObject(objRes , "result" , "OK");
    cJSON_AddStringToObject(objRes , "message" , "OK");
    cJSON_AddNumberToObject(objRes , "code" , 200);

    *result = new string(cJSON_Print(objRes));

    return 0;
}