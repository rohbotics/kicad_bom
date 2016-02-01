#include <iostream>
#include <thread>
#include <vector>
#include <unordered_map>
#include "Component.h"

#include <pugixml.hpp>

typedef std::vector<std::shared_ptr<Component>> ComponentSet;

int main() {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("/home/rohan/cplus/kicad_bom/QTC.xml");

	auto component_list = doc.child("export").child("components");

	ComponentSet comp_vector;

	auto i = 0;
	for (auto comp : component_list.children("comp")){
		i++;
	}
	comp_vector.reserve(i);
	std::cout << i << std::endl;

	for (auto comp : component_list.children("comp")){

		std::map<std::string,std::string> fields;
		for(auto f : comp.child("fields").children("field")){
			fields.insert(std::make_pair(f.attribute("name").value(),f.child_value()));
		}

		//auto c = new Component(comp.attribute("ref").value(),comp.child_value("value"), fields);
		auto c = std::make_shared<Component>(comp.attribute("ref").value(),comp.child_value("value"), fields );
		comp_vector.push_back(c);
	}

	auto vendor_pn2components = std::make_shared<std::unordered_map<std::string, ComponentSet>>();
	for(auto comp : comp_vector) {

		if (comp->has_field("Vendor") && comp->has_field("PN")){
			std::string key = comp->getFields().at("Vendor") + comp->getFields().at("PN");

			if (vendor_pn2components->count(key)){
				vendor_pn2components->at(key).push_back(comp);
			}

			else {
				ComponentSet cs;
				cs.push_back(comp);
				vendor_pn2components->insert(std::make_pair(key, cs));
			}
		}
	}

	for(auto cs : *vendor_pn2components) {
		std::cout << cs.first << std::endl;
		for(auto c : cs.second){
			//c->printReferenceID();
		}
	}

	return 0;
}