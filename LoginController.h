//
// Created by zkl on 11/28/17.
//

#ifndef SRS_C_SERVER_LOGINCONTOLLER_H
#define SRS_C_SERVER_LOGINCONTOLLER_H

#include <string>
#include <mysql/mysql.h>
#include <cjson/cJSON.h>

#include <boost/algorithm/algorithm.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "SqlHelper.h"

using namespace std;

class LoginController {

public:
    int loginRoute(string route , string content , string ** result);
    int userRegist(string content, string ** result);

};


#endif //SRS_C_SERVER_LOGINCONTOLLER_H
