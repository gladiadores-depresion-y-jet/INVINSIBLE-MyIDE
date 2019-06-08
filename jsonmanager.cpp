#include "jsonmanager.h"


ptree jsonmanager::stringToPtree(string s)
{
    std::istringstream iss(s);
    ptree document;
    read_json(iss, document);
    return document;
}

string jsonmanager::ptreeToString(ptree pt) {

    std::ostringstream oss;
    write_json(oss, pt);
    return oss.str();
}

