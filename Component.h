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

    ~Component();

    // Copy and Move Constructors
    Component(const Component &other);
    Component &operator=(Component &&other);

    std::string getReferenceID();
    std::string getValue();
    std::map<std::string, std::string> getFields();

	// Check equality between this Component and another
	bool operator==(Component& other);

	// Print Component Ref ID to cout
    void printReferenceID();

	// Check for conflict between fields for components
    bool fields_conflict(std::map<std::string, std::string> &other_fields);

	// Check if this Component has a field
    bool has_field(std::string field);

    std::mutex *component_mutex_ = nullptr;

private:
    std::string referenceID_;
    std::string value_;
    std::string footprint_;
    std::map<std::string, std::string> fields_;

    bool _fields_conflict(std::map<std::string, std::string> &other_fields);
    bool _has_field(std::string field);
};


#endif //KICAD_BOM_COMPONENT_H
