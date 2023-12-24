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

std::pair<int, int> NPC::get_position() {
    std::lock_guard<std::mutex> lck(mu);
    return {x, y};
}

bool NPC::is_close(const std::shared_ptr<NPC>& other) {
    auto [otherX, otherY] = other->get_position();

    std::lock_guard<std::mutex> lck(mu);
    if (std::pow(x - otherX, 2) + std::pow(y - otherY, 2) <= std::pow(killDistance, 2)) {
        return true;
    } 
    return false;
}

NpcType& NPC::gettype() {
    std::lock_guard<std::mutex> lck(mu);
    return type;
}

void NPC::save(std::ostream& os) {
    os << x << std::endl;
    os << y << std::endl;
}

int NPC::getMoveDistance() {
    std::lock_guard<std::mutex> lck(mu);
    return moveDistance;
}

void NPC::move(int deltaX, int deltaY, int maxX, int maxY) {
    std::lock_guard<std::mutex> lck(mu);

    if (deltaX > moveDistance || deltaY > moveDistance) {
        throw std::invalid_argument("Max move distance is " + std::to_string(moveDistance));
    }

    if ((x + deltaX >= 0) && (x + deltaX <= maxX)) {
        x += deltaX;
    }
    
    if ((y + deltaY >= 0) && (y + deltaY <= maxY)) {
        y += deltaY;
    }
}

bool NPC::isAlive() {
    std::lock_guard<std::mutex> lck(mu);
    return alive;
}

void NPC::mustDie() {
    std::lock_guard<std::mutex> lck(mu);
    alive = false;
}

int NPC::throwDice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 500);

    return dis(gen) % 6 + 1;
}

std::ostream& operator << (std::ostream& os, NPC& npc) {
    os << "{x:" << npc.x << ", y:" << npc.y << "}";
    return os;
}