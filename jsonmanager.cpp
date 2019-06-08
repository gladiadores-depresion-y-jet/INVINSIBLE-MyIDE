#include "jsonmanager.h"


ptree jsonmanager::stringToPtree(QString s)
{
    std::istringstream iss(s);
    ptree document;
    read_json(iss, document);
    return document;
}

QString jsonmanager::ptreeToString(ptree pt) {
    std::ostringstream oss;
    write_json(oss, pt);
    return oss.str();
}

