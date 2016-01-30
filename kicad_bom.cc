#include <iostream>
#include <thread>
#include <vector>
#include "Component.h"

#include <pugixml.hpp>

int main() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("/home/rohan/cplus/kicad_bom/QTC.xml");

    auto component_list = doc.child("export").child("components");

    //auto comp_vector = std::vector<std::shared_ptr<Component>>;
    std::vector<std::shared_ptr<Component>> comp_vector;
    //std::vector<Component> comp_vector;

    auto i = 0;
    for (auto comp : component_list.children("comp")){
        i++;
        //std::cout << "Load result: " << comp.attribute("ref").value() << "      " << comp.child_value("value") << std::endl;
    }
    comp_vector.reserve(i);
    std::cout << i << std::endl;

    for (auto comp : component_list.children("comp")){

        std::map<std::string,std::string> fields;
        for(auto f : comp.child("fields").children("field")){
            fields.insert({f.attribute("name").value(),f.value()});
        }

        //auto c = new Component(comp.attribute("ref").value(),comp.child_value("value"), fields);
        auto c = std::make_shared<Component>(comp.attribute("ref").value(),comp.child_value("value"), fields );
        comp_vector.push_back(c);
    }




    //delete(comp_vector);
    return 0;
}