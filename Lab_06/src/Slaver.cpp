#include "../headers/Slaver.hpp"

bool SlaverVisitor::visit(const std::shared_ptr<Slaver>& defender) const {
    return false;
}

bool SlaverVisitor::visit(const std::shared_ptr<Druid>& defender) const {
    return true;
}

bool SlaverVisitor::visit(const std::shared_ptr<Orc>& defender) const {
    return false;
}

Slaver::Slaver() : NPC(SlaverType, 0, 0) {}

Slaver::Slaver(int x, int y) : NPC(SlaverType, x, y) {}

Slaver::Slaver(std::istream& in) : NPC(SlaverType, in) {}

void Slaver::save(std::ostream& out) {
    out << SlaverType << std::endl;
    NPC::save(out);
}

bool Slaver::accept(const std::shared_ptr<FightVisitor>& attacker_visitor, const std::shared_ptr<NPC>& attacker) const {
    std::shared_ptr<const NPC> npc_const_ptr = shared_from_this();
    std::shared_ptr<NPC> npc_ptr = std::const_pointer_cast<NPC>(npc_const_ptr);
    std::shared_ptr<Slaver> defender = std::dynamic_pointer_cast<Slaver>(npc_ptr);

    bool result = attacker_visitor->visit(defender);

    attacker->fight_notify(defender, result);

    return result; 
}

std::ostream& operator << (std::ostream& out, Slaver& slaver) {
    out << "Slaver: " << *static_cast<NPC*>(&slaver) << std::endl;
    return out;
}

void Slaver::print() {
    std::cout << *this;
}