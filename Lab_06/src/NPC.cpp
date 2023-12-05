#include "../headers/NPC.hpp"

NPC::NPC(NpcType t, int _x, int _y) : type(t), x(_x), y(_y) {}

NPC::NPC(NpcType t, std::istream& in) : type(t) {
    in >> x;
    in >> y;
}

void NPC::subscribe(const std::shared_ptr<IFightObserver>& observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC>& defender, bool win) {
    for (auto& o : observers) {
        o->on_fight(shared_from_this(), defender, win);
    }
}

bool NPC::is_close(const std::shared_ptr<NPC>& other, size_t distance) const {
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2)) {
        return true;
    } 
    return false;
}

int NPC::get_x_value() {
    return x;
}

int NPC::get_y_value() {
    return y;
}

NpcType& NPC::gettype() {
    return type;
}

void NPC::save(std::ostream& os) {
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream& operator << (std::ostream& os, NPC& npc) {
    os << "{x:" << npc.x << ", y:" << npc.y << "}";
    return os;
}