/*

Copyright (c) 2016, Rohan Agrawal
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
 * Neither the name of Aleopile nor the names of its contributors may be
   used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

 */

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

		try {
			std::string key = comp->get_field("Vendor") + comp->get_field("PN");
			if (vendor_pn2components->count(key)){
				vendor_pn2components->at(key).push_back(comp);
			}

			else {
				ComponentSet cs;
				cs.push_back(comp);
				vendor_pn2components->insert(std::make_pair(key, cs));
			}
		}
		catch (const std::invalid_argument& ia) {
		}

	}

	for(auto cs : *vendor_pn2components) {
		std::cout << cs.first << std::endl;
		for(auto c : cs.second){
			//c->printReferenceID();
		}
	}

	auto manufacturer_mpn2components = std::make_shared<std::unordered_map<std::string, ComponentSet>>();
	for(auto comp : comp_vector) {

		try {
			std::string key = comp->get_field("Manufacturer") + comp->get_field("MPN");

			if (manufacturer_mpn2components->count(key)){
				manufacturer_mpn2components->at(key).push_back(comp);
			}

			else {
				ComponentSet cs;
				cs.push_back(comp);
				manufacturer_mpn2components->insert(std::make_pair(key, cs));
			}
		}
		catch (const std::invalid_argument& ia) {
		}
	}

	for(auto cs : *manufacturer_mpn2components) {
		std::cout << cs.first << std::endl;
		for(auto c : cs.second){
			//c->printReferenceID();
		}
	}

	return 0;
}