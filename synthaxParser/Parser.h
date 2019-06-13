//
// Created by kugelblitz on 6/8/19.
//

#ifndef INVINCIBLE_CLIENTLOGIC_PARSER_H
#define INVINCIBLE_CLIENTLOGIC_PARSER_H

#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <client/Requests.h>
#include <nlohmann/json.hpp>

using nlohmann::json;

class Parser {

public:
    json scriptTypeofRequestParser(std::string &script);

private:
    json insertParser(std::vector<std::string> strings);
    json selectParser(std::vector<std::string> strings);
    json updateParser(std::vector<std::string> strings);
    json deleteParser(std::vector<std::string> strings);

};


#endif //INVINCIBLE_CLIENTLOGIC_PARSER_H
