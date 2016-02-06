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

TEST(component, component_field_conflict_exact_Test) {
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

TEST(component, component_field_conflict_other_more_Test) {
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

TEST(component, component_field_conflict_main_more_Test) {
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

TEST(component, component_field_conflict_main_empty_Test) {
    auto c = Component("R11", "480");

    std::map<std::string,std::string> f2;
    f2["Vendor"] = "DigiKey";
    f2["PN"] = "1080-889-HSD";
    f2["MPN"] = "4903-4DF-FD43S";


    auto conflict = c.fields_conflict(f2);
    ASSERT_EQ(0, conflict);
}


TEST(component, component_2_argument_constrcutor_equivilance_exact_Test) {
    auto c1 = Component("R11", "480");
    auto c2 = Component("R11", "480");
    auto equiv = (c1==c2);

    ASSERT_EQ(1, equiv);
}