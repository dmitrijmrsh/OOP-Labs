#include "../headers/NPC.hpp"
#include "../headers/Slaver.hpp"
#include "../headers/Orc.hpp"
#include "../headers/Druid.hpp"
#include "../headers/Factory.hpp"
#include "../headers/Observers.hpp"

#include <gtest/gtest.h>

TEST(NPC_class_tests, getters) {
    std::shared_ptr<NPC> ptr = std::make_shared<Slaver>(2,2);
    auto [Xvalue, Yvalue] = ptr->get_position();
    ASSERT_TRUE(ptr->gettype() == 0 && Xvalue == 2 && Yvalue == 2);
}

TEST(NPC_class_tests, is_close_method_1) {
    std::shared_ptr<NPC> ptr1 = std::make_shared<Orc>(0,0);
    std::shared_ptr<NPC> ptr2 = std::make_shared<Druid>(2,2);
    ASSERT_TRUE(ptr1->is_close(ptr2));
}

TEST(NPC_class_tests, is_close_method_2) {
    std::shared_ptr<NPC> ptr1 = std::make_shared<Orc>(0,0);
    std::shared_ptr<NPC> ptr2 = std::make_shared<Druid>(10,10);
    ASSERT_FALSE(ptr1->is_close(ptr2));
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
    auto [Xvalue, Yvalue] = s.get_position();
    ASSERT_TRUE(s.gettype() == 0 && Xvalue == 2 && Yvalue == 2);
}

TEST(Slaver_class_tests, accept_method_1) {
    std::shared_ptr<NPC> defender = std::make_shared<Slaver>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Orc>(3,3);
    ASSERT_TRUE(defender->accept(attacker));
}

TEST(Slaver_class_tests, accept_method_2) {
    std::shared_ptr<NPC> defender = std::make_shared<Slaver>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Slaver>(3,3);
    ASSERT_FALSE(defender->accept(attacker));
}

TEST(Slaver_class_tests, accept_method_3) {
    std::shared_ptr<NPC> defender = std::make_shared<Slaver>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Druid>(3,3);
    ASSERT_FALSE(defender->accept(attacker));
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
    auto [Xvalue, Yvalue] = d.get_position();
    ASSERT_TRUE(d.gettype() == 1 && Xvalue == 2 && Yvalue == 2);
}

TEST(Druid_class_tests, accept_method_1) {
    std::shared_ptr<NPC> defender = std::make_shared<Druid>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Orc>(3,3);;
    ASSERT_TRUE(defender->accept(attacker));
}

TEST(Druid_class_tests, accept_method_2) {
    std::shared_ptr<NPC> defender = std::make_shared<Druid>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Slaver>(3,3);
    ASSERT_TRUE(defender->accept(attacker));
}

TEST(Druid_class_tests, accept_method_3) {
    std::shared_ptr<NPC> defender = std::make_shared<Druid>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Druid>(3,3);
    ASSERT_FALSE(defender->accept(attacker));
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
    auto [Xvalue, Yvalue] = o.get_position();
    ASSERT_TRUE(o.gettype() == 2 && Xvalue == 2 && Yvalue == 2); 
}

TEST(Orc_class_tests, accept_method_1) {
    std::shared_ptr<NPC> defender = std::make_shared<Orc>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Slaver>(3,3);
    ASSERT_FALSE(defender->accept(attacker));
}

TEST(Orc_class_tests, accept_method_2) {
    std::shared_ptr<NPC> defender = std::make_shared<Orc>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Druid>(3,3);
    ASSERT_FALSE(defender->accept(attacker));
}

TEST(Orc_class_tests, accept_method_3) {
    std::shared_ptr<NPC> defender = std::make_shared<Orc>(2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Orc>(3,3);
    ASSERT_TRUE(defender->accept(attacker));
}

TEST(Factory_tests, create_1) {
    std::shared_ptr<NPC> ptr = Factory::Create(SlaverType, 1, 1);
    auto [Xvalue, Yvalue] = ptr->get_position();
    ASSERT_TRUE(ptr->gettype() == 0 && Xvalue == 1 && Yvalue == 1);
}

TEST(Factory_tests, create_2) {
    std::shared_ptr<NPC> ptr = Factory::Create(OrcType, 1, 1);
    auto [Xvalue, Yvalue] = ptr->get_position();
    ASSERT_TRUE(ptr->gettype() == 2 && Xvalue == 1 && Yvalue == 1);
}

TEST(Factory_tests, create_3) {
    std::shared_ptr<NPC> ptr = Factory::Create(DruidType, 1, 1);
    auto [Xvalue, Yvalue] = ptr->get_position();
    ASSERT_TRUE(ptr->gettype() == 1 && Xvalue == 1 && Yvalue == 1);
}

TEST(Factory_tests, create_throw) {
    std::shared_ptr<NPC> ptr;
    ASSERT_ANY_THROW(ptr = Factory::Create(NpcType(534), 2, 2));
}

TEST(Fight_test, Fight_test_1) {
    set_t array;

    array.insert(Factory::Create(DruidType, 10, 10));
    array.insert(Factory::Create(OrcType, 11, 11));
    array.insert(Factory::Create(SlaverType, 11, 12));
    array.insert(Factory::Create(DruidType, 11, 13));
    array.insert(Factory::Create(OrcType, 11, 14));
    array.insert(Factory::Create(SlaverType, 11, 15));
    
    bool win = false;
    int countD = 0;
    while (!win) {
        if (countD == 4) {
            win = true;
        }
        for (std::shared_ptr<NPC> attacker : array) {
            for (std::shared_ptr<NPC> defender : array) {
                if (attacker != defender && attacker->isAlive() &&
                defender->isAlive() && (attacker->throwDice() > defender->throwDice()) &&
                defender->accept(attacker)) {
                    defender->mustDie();
                    ++countD;
                }
            }
        }
    }

    ASSERT_TRUE(win);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}