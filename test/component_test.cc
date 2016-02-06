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

#include "gtest/gtest.h"
#include "../Component.h"

/*
 * Basic Tests for Constructor and Get
 */

TEST(component_constructor, component_constructor_2_argument_Test) {
	auto c = Component("R11", "480");
	ASSERT_EQ("R11", c.getReferenceID());
	ASSERT_EQ("480", c.getValue());
}

TEST(component_constructor, component_constructor_3_argument_Test) {
	std::map<std::string,std::string> f;
	f["Vendor"] = "DigiKey";

	auto c = Component("R11", "480", f);

	ASSERT_EQ(f, c.getFields());
	ASSERT_EQ("R11", c.getReferenceID());
	ASSERT_EQ("480", c.getValue());
}

TEST(component_constructor, component_constructor_3_argument_large_Test) {
	std::map<std::string,std::string> f;

	for (int i = 0; i < 100000; ++i) {
		f.insert(std::make_pair("Vend"+ std::to_string(i), "Digi" + std::to_string(i)));
	}

	auto c = Component("R11", "480", f);

	ASSERT_EQ(f, c.getFields());
	ASSERT_EQ("R11", c.getReferenceID());
	ASSERT_EQ("480", c.getValue());
}


/*
 * Tests to see if overridden equivalence works
 */

TEST(component_equivalence, component_equivalence_2_argument_exact_Test) {
	auto c1 = Component("R11", "480");
	auto c2 = Component("R11", "480");
	auto equiv = (c1==c2);

	ASSERT_EQ(1, equiv);
}

TEST(component_equivalence, component_equivalence_3_argument_exact_Test) {
	std::map<std::string,std::string> f1;
	f1["Vendor"] = "DigiKey";
	f1["PN"] = "1080-889-HSD";
	f1["MPN"] = "4903-4DF-FD43S";

	auto c1 = Component("R11", "480", f1);
	auto c2 = Component("R11", "480", f1);
	auto equiv = (c1==c2);

	ASSERT_EQ(1, equiv);
}

/*
 * Tests to check if field related functions are working
 */

TEST(component_field, component_field_conflict_exact_Test) {
	std::map<std::string,std::string> f1;
	f1["Vendor"] = "DigiKey";
	f1["PN"] = "1080-889-HSD";
	f1["MPN"] = "4903-4DF-FD43S";

	auto c = Component("R11", "480", f1);
	ASSERT_EQ(f1,c.getFields());


	std::map<std::string,std::string> f2;
	f2["Vendor"] = "DigiKey";
	f2["PN"] = "1080-889-HSD";
	f2["MPN"] = "4903-4DF-FD43S";

	auto conflict = c.fields_conflict(f2);
	ASSERT_EQ(0, conflict);
}

TEST(component_field, component_field_conflict_other_more_Test) {
	std::map<std::string,std::string> f1;
	f1["Vendor"] = "DigiKey";
	f1["PN"] = "1080-889-HSD";
	f1["MPN"] = "4903-4DF-FD43S";

	auto c = Component("R11", "480", f1);
	ASSERT_EQ(f1,c.getFields());


	std::map<std::string,std::string> f2;
	f2["Vendor"] = "DigiKey";
	f2["PN"] = "1080-889-HSD";
	f2["MPN"] = "4903-4DF-FD43S";
	f2["vpn2"] = "34-JHKJ-24367";
	f2["FDK"] = "REUJDFHDS-FDFIJDS";

	auto conflict = c.fields_conflict(f2);
	ASSERT_EQ(0, conflict);
}

TEST(component_field, component_field_conflict_main_more_Test) {
	std::map<std::string,std::string> f1;
	f1["Vendor"] = "DigiKey";
	f1["PN"] = "1080-889-HSD";
	f1["MPN"] = "4903-4DF-FD43S";
	f1["vpn2"] = "34-JHKJ-24367";
	f1["FDK"] = "REUJDFHDS-FDFIJDS";

	auto c = Component("R11", "480", f1);
	ASSERT_EQ(f1,c.getFields());


	std::map<std::string,std::string> f2;
	f2["Vendor"] = "DigiKey";
	f2["PN"] = "1080-889-HSD";
	f2["MPN"] = "4903-4DF-FD43S";


	auto conflict = c.fields_conflict(f2);
	ASSERT_EQ(0, conflict);
}

TEST(component_field, component_field_conflict_main_empty_Test) {
	auto c = Component("R11", "480");

	std::map<std::string,std::string> f2;
	f2["Vendor"] = "DigiKey";
	f2["PN"] = "1080-889-HSD";
	f2["MPN"] = "4903-4DF-FD43S";


	auto conflict = c.fields_conflict(f2);
	ASSERT_EQ(0, conflict);
}
