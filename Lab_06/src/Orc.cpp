#include "../headers/Orc.hpp"

bool OrcVisitor::visit(const std::shared_ptr<Slaver>& defender) const {
    return true;
}

bool OrcVisitor::visit(const std::shared_ptr<Druid>& defender) const {
    return true;
}

bool OrcVisitor::visit(const std::shared_ptr<Orc>& defender) const {
    return true;
}

Orc::Orc() : NPC(OrcType, 0, 0) {}

Orc::Orc(int x, int y) : NPC(OrcType, x, y) {}

Orc::Orc(std::istream& in) : NPC(OrcType, in) {}

void Orc::save(std::ostream& out) {
    out  << OrcType << std::endl;
    NPC::save(out);
}

bool Orc::accept(const std::shared_ptr<FightVisitor>& attacker_visitor, const std::shared_ptr<NPC>& attacker) const {
    std::shared_ptr<const NPC> npc_const_ptr = shared_from_this();
    std::shared_ptr<NPC> npc_ptr = std::const_pointer_cast<NPC>(npc_const_ptr);
    std::shared_ptr<Orc> defender = std::dynamic_pointer_cast<Orc>(npc_ptr);

    bool result = attacker_visitor->visit(defender);

    attacker->fight_notify(defender, result);

    return result;
}

std::ostream& operator << (std::ostream& out, Orc& orc) {
    out << "Orc: " << *static_cast<NPC*>(&orc) << std::endl;
    return out;
}

void Orc::print() {
    std::cout << *this;
}