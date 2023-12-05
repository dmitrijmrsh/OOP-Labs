#include "../headers/NPC.hpp"
#include "../headers/Slaver.hpp"
#include "../headers/Orc.hpp"
#include "../headers/Druid.hpp"
#include "../headers/Factory.hpp"
#include "../headers/Observers.hpp"

#include <gtest/gtest.h>

TEST(NPC_class_tests, getters) {
    std::shared_ptr<NPC> ptr = std::make_shared<Slaver>(2,2);
    ASSERT_TRUE(ptr->gettype() == 0 && ptr->get_x_value() == 2 && ptr->get_y_value() == 2);
}

TEST(NPC_class_tests, is_close_method_1) {
    std::shared_ptr<NPC> ptr1 = std::make_shared<Orc>(0,0);
    std::shared_ptr<NPC> ptr2 = std::make_shared<Druid>(10,10);
    ASSERT_TRUE(ptr1->is_close(ptr2, 20));
}

TEST(NPC_class_tests, is_close_method_2) {
    std::shared_ptr<NPC> ptr1 = std::make_shared<Orc>(0,0);
    std::shared_ptr<NPC> ptr2 = std::make_shared<Druid>(10,10);
    ASSERT_FALSE(ptr1->is_close(ptr2, 2));
}

TEST(Slaver_tests, slaver_visitor_test_1) {
    SlaverVisitor visitor;
    std::shared_ptr<Slaver> ptr = std::make_shared<Slaver>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Slaver_tests, slaver_visitor_test_2) {
    SlaverVisitor visitor;
    std::shared_ptr<Druid> ptr = std::make_shared<Druid>();
    ASSERT_TRUE(visitor.visit(ptr));
}

TEST(Slaver_tests, slaver_visitor_test_3) {
    SlaverVisitor visitor;
    std::shared_ptr<Orc> ptr = std::make_shared<Orc>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Slaver_class_tests, default_constructor_and_destructor) {
    Slaver s;
    s.~Slaver();
}

TEST(Slaver_class_tests, int_constructor) {
    Slaver s(2,2);
    ASSERT_TRUE(s.gettype() == 0 && s.get_x_value() == 2 && s.get_y_value() == 2);
}

TEST(Slaver_class_tests, accept_method_1) {
    std::shared_ptr<NPC> defender = std::make_shared<Slaver>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Orc>(3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<OrcVisitor>();
    ASSERT_TRUE(defender->accept(visitor_ptr, attacker));
}

TEST(Slaver_class_tests, accept_method_2) {
    std::shared_ptr<NPC> defender = std::make_shared<Slaver>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Slaver>(3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<SlaverVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Slaver_class_tests, accept_method_3) {
    std::shared_ptr<NPC> defender = std::make_shared<Slaver>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Druid>(3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<DruidVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Druid_tests, druid_visitor_test_1) {
    DruidVisitor visitor;
    std::shared_ptr<Slaver> ptr = std::make_shared<Slaver>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Druid_tests, druid_visitor_test_2) {
    DruidVisitor visitor;
    std::shared_ptr<Druid> ptr = std::make_shared<Druid>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Druid_tests, druid_visitor_test_3) {
    DruidVisitor visitor;
    std::shared_ptr<Orc> ptr = std::make_shared<Orc>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Druid_class_tests, default_constructor_and_destructor) {
    Druid d;
    d.~Druid();
}

TEST(Druid_class_tests, int_constructor) {
    Druid d(2,2);
    ASSERT_TRUE(d.gettype() == 1 && d.get_x_value() == 2 && d.get_y_value() == 2);
}

TEST(Druid_class_tests, accept_method_1) {
    std::shared_ptr<NPC> defender = std::make_shared<Druid>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Orc>(3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<OrcVisitor>();
    ASSERT_TRUE(defender->accept(visitor_ptr, attacker));
}

TEST(Druid_class_tests, accept_method_2) {
    std::shared_ptr<NPC> defender = std::make_shared<Druid>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Slaver>(3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<SlaverVisitor>();
    ASSERT_TRUE(defender->accept(visitor_ptr, attacker));
}

TEST(Druid_class_tests, accept_method_3) {
    std::shared_ptr<NPC> defender = std::make_shared<Druid>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Druid>(3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<DruidVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Orc_tests, orc_visitor_test_1) {
    OrcVisitor visitor;
    std::shared_ptr<Slaver> ptr = std::make_shared<Slaver>();
    ASSERT_TRUE(visitor.visit(ptr));
}

TEST(Orc_tests, orc_visitor_test_2) {
    OrcVisitor visitor;
    std::shared_ptr<Druid> ptr = std::make_shared<Druid>();
    ASSERT_TRUE(visitor.visit(ptr));
}

TEST(Orc_tests, orc_visitor_test_3) {
    OrcVisitor visitor;
    std::shared_ptr<Orc> ptr = std::make_shared<Orc>();
    ASSERT_TRUE(visitor.visit(ptr));
}

TEST(Orc_class_tests, default_constructor_and_destructor) {
    Orc o;
    o.~Orc();
}

TEST(Orc_class_tests, int_constructor) {
    Orc o(2,2);
    ASSERT_TRUE(o.gettype() == 2 && o.get_x_value() == 2 && o.get_y_value() == 2); 
}

TEST(Orc_class_tests, accept_method_1) {
    std::shared_ptr<NPC> defender = std::make_shared<Orc>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Slaver>(3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<SlaverVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Orc_class_tests, accept_method_2) {
    std::shared_ptr<NPC> defender = std::make_shared<Orc>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Druid>(3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<DruidVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Orc_class_tests, accept_method_3) {
    std::shared_ptr<NPC> defender = std::make_shared<Orc>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Orc>(3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<OrcVisitor>();
    ASSERT_TRUE(defender->accept(visitor_ptr, attacker));
}

TEST(Factory_tests, create_1) {
    std::shared_ptr<NPC> ptr = Factory::Create(SlaverType, 1, 1);
    ASSERT_TRUE(ptr->gettype() == 0 && ptr->get_x_value() == 1 && ptr->get_y_value() == 1);
}

TEST(Factory_tests, create_2) {
    std::shared_ptr<NPC> ptr = Factory::Create(OrcType, 1, 1);
    ASSERT_TRUE(ptr->gettype() == 2 && ptr->get_x_value() == 1 && ptr->get_y_value() == 1);
}

TEST(Factory_tests, create_3) {
    std::shared_ptr<NPC> ptr = Factory::Create(DruidType, 1, 1);
    ASSERT_TRUE(ptr->gettype() == 1 && ptr->get_x_value() == 1 && ptr->get_y_value() == 1);
}

TEST(Factory_tests, create_throw) {
    std::shared_ptr<NPC> ptr;
    ASSERT_ANY_THROW(ptr = Factory::Create(NpcType(534), 2, 2));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}