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
