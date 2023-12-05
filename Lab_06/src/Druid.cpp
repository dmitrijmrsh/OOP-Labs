#include "../headers/Druid.hpp"

bool DruidVisitor::visit(const std::shared_ptr<Slaver>& attacker) const {
    return false;
}

bool DruidVisitor::visit(const std::shared_ptr<Druid>& attacker) const {
    return false;
}

bool DruidVisitor::visit(const std::shared_ptr<Orc>& attacker) const {
    return false;
}

Druid::Druid() : NPC(DruidType, 0, 0) {}

Druid::Druid(int x, int y) : NPC(DruidType, x, y) {}

Druid::Druid(std::istream& in) : NPC(DruidType, in) {}

void Druid::save(std::ostream& out) {
    out << DruidType << std::endl;
    NPC::save(out);
}

bool Druid::accept(const std::shared_ptr<FightVisitor>& attacker_visitor, const std::shared_ptr<NPC>& attacker) const {
    std::shared_ptr<const NPC> npc_const_ptr = shared_from_this();
    std::shared_ptr<NPC> npc_ptr = std::const_pointer_cast<NPC>(npc_const_ptr);
    std::shared_ptr<Druid> defender = std::dynamic_pointer_cast<Druid>(npc_ptr);

    bool result = attacker_visitor->visit(defender);

    attacker->fight_notify(defender, result);

    return result;
}

std::ostream& operator << (std::ostream& out, Druid& druid) {
    out << "Druid: " << *static_cast<NPC*>(&druid) << std::endl;
    return out;
}

void Druid::print() {
    std::cout << *this;
}