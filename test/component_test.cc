//
// Created by rohan on 12/17/15.
//

#include "gtest/gtest.h"
#include "../Component.h"

TEST(component, component_2_argument_constrcutor_Test) {
    auto c = Component("R11", "480");
    ASSERT_EQ("R11",c.getReferenceID());
    ASSERT_EQ("480", c.getValue());
}

TEST(component, component_3_argument_constrcutor_Test) {
    std::map<std::string,std::string> f;
    f["Vendor"] = "DigiKey";

    auto c = Component("R11", "480", f);

    ASSERT_EQ(f,c.getFields());
    ASSERT_EQ("R11",c.getReferenceID());
    ASSERT_EQ("480", c.getValue());
}