#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <QDebug>


using boost::property_tree::ptree;
using  namespace std;

class jsonmanager {


public:
    ptree stringToPtree(string json);
    string ptreeToString(ptree pt);
    void printJson(ptree const& pt);
};

#endif // JSONMANAGER_H
