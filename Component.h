//
// Created by rohan on 12/14/15.
//

#ifndef KICAD_BOM_COMPONENT_H
#define KICAD_BOM_COMPONENT_H


#include <string>
#include <vector>
#include <map>
#include <mutex>

class Component {
public:
    Component(std::string referenceID, std::string value);

    Component(std::string referenceID, std::string value,
              std::map<std::string, std::string> fields);

    Component(const Component& other);


    Component& operator=(Component&& other);

    ~Component();

    std::mutex* component_mutex_ = nullptr;

    std::string& getReferenceID();
    void printReferenceID();

    std::string& getValue();
    std::map<std::string, std::string>& getFields();

private:
    std::string referenceID_;
    std::string value_;
    std::map<std::string, std::string> fields_;
};


#endif //KICAD_BOM_COMPONENT_H
