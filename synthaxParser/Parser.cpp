//
// Created by kugelblitz on 6/8/19.
//

#include "Parser.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json Parser::scriptTypeofRequestParser(std::string &script) {
    json jsonRequest;
    try {
        // Divide string por espacios y pone substrings en vector
        std::vector<std::string> strings;
        std::istringstream f(script);
        std::string s;
        while (getline(f, s, ' ')) {
            strings.push_back(s);
        }

        std::string typeOfRequest = strings[0];
        std::transform(typeOfRequest.begin(), typeOfRequest.end(), typeOfRequest.begin(), ::tolower);

        if (typeOfRequest == "insert") {
            jsonRequest = this->insertParser(strings);
        }

        else if (typeOfRequest == "select") {
            jsonRequest = this->selectParser(strings);
        }

        else if (typeOfRequest == "update") {
            jsonRequest = this->updateParser(strings);
        }

        else if (typeOfRequest == "delete") {
            jsonRequest = this->deleteParser(strings);
        }
    }

    catch (const std::exception& e) {
        e.what();
    }

    return jsonRequest;

}

json Parser::insertParser(std::vector<std::string> strings) {
    json jsonRequest;
    std::string table;
    std::string cols;
    std::string values;
    if (strings.size() >= 6) {
        std::transform(strings[1].begin(), strings[1].end(), strings[1].begin(), ::tolower);
        if (strings[1] == "into") {
            table = strings[2];
            if (strings[3][0] == '(' && strings[3][strings[3].length()-1] == ')') {
                cols = strings[3].substr(1, strings[3].length()-2);
                std::transform(strings[4].begin(), strings[4].end(), strings[4].begin(), ::tolower);
                if (strings[4] == "values") {
                    if (strings[5][0] == '(' && strings[5][strings[5].length()-1] == ')') {
                        values = strings[5].substr(1, strings[5].length()-2);
                        jsonRequest["table"] = table;
                        jsonRequest["cols"] = cols;
                        jsonRequest["values"] = values;
                    }
                }
            }
        }
    }


    return jsonRequest;
}


json Parser::selectParser(std::vector<std::string> strings) {
    json jsonRequest;
    std::string table;
    std::string cols;
    if (strings.size() >= 4) {
        if (strings[1][0] == '(' && strings[1][strings[1].length()-1] == ')') {
            cols = strings[1].substr(1, strings[1].length()-2);
            std::transform(strings[2].begin(), strings[2].end(), strings[2].begin(), ::tolower);
            if(strings[2] == "from") {
                table = strings[3];
                jsonRequest["table"] = table;
                jsonRequest["cols"] = cols;
            }
        }
    }

    return jsonRequest;
}

json Parser::updateParser(std::vector<std::string> strings) {
    json jsonRequest;
    std::string table;
    std::string cols;
    std::string values;

    if (strings.size() >= 6) {
        table = strings[1];
        std::transform(strings[2].begin(), strings[2].end(), strings[2].begin(), ::tolower);
        if (strings[2] == "set") {
            std::vector<std::string> subs;
            std::istringstream f(strings[3]);
            std::string s;
            while (getline(f, s, ',')) {
                subs.push_back(s);
            }
            std::ostringstream osCols;
            std::ostringstream osValues;
            for (int i = 0; i < subs.size(); i++) {
                std::vector<std::string> temp;
                std::istringstream g(subs[i]);
                std::string ss;
                while (getline(g, ss, '=')) {
                    temp.push_back(ss);
                }
                if (i == subs.size()-1) {
                    osCols << temp[0];
                    osValues << temp[1];
                }
                else {
                    osCols << temp[0] << ",";
                    osValues << temp[1] << ",";
                }
            }
            cols = osCols.str();
            values = osValues.str();
            std::transform(strings[4].begin(), strings[4].end(), strings[4].begin(), ::tolower);
            if (strings[4] == "where") {
                std::vector<std::string> temp;
                std::istringstream g(strings[5]);
                std::string sss;
                while (getline(g, sss, '=')) {
                    temp.push_back(sss);
                }
                if (temp.size() == 2) {
                    json tempJson;
                    tempJson["col"] = temp[0];
                    tempJson["value"] = temp[1];
                    jsonRequest["where"] = tempJson;
                    jsonRequest["table"] = table;
                    jsonRequest["cols"] = cols;
                    jsonRequest["values"] = values;
                }
            }
        }

    }

    return jsonRequest;
}

json Parser::deleteParser(std::vector<std::string> strings) {
    json jsonRequest;
    std::string table;

    if (strings.size() >= 3) {
        std::transform(strings[1].begin(), strings[1].end(), strings[1].begin(), ::tolower);
        if (strings[1] == "from") {
            jsonRequest["table"] = strings[2];
            if (strings.size() > 3) {
                std::transform(strings[3].begin(), strings[3].end(), strings[3].begin(), ::tolower);
                if (strings[3] == "where") {
                    std::vector<std::string> subs;
                    std::istringstream f(strings[4]);
                    std::string s;
                    while (getline(f, s, '=')) {
                        subs.push_back(s);
                    }
                    if (subs.size() == 2) {
                        json temp;
                        temp["col"] = subs[0];
                        temp["value"] = subs[1];
                        jsonRequest["where"] = temp;
                    }
                }
            }
        }
    }

    return jsonRequest;
}
