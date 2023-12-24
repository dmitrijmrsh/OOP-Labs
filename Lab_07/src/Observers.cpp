#include "../headers/Observers.hpp"

std::shared_ptr<IFightObserver> TextObserver::get() {
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void TextObserver::on_fight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) {
    if (win) { 
        std::cout << std::endl << "Murder ------" << std::endl;
        attacker->print();
        defender->print();
    }
}

std::string FileObserver::NPCname(const NpcType& type) {
    std::string ans;
    switch (type) {
        case NpcType::SlaverType:
            ans = "Slaver";
            return ans;
        case NpcType::DruidType:
            ans = "Druid";
            return ans;
        case NpcType::OrcType:
            ans = "Orc";
            return ans;
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}

std::shared_ptr<IFightObserver> FileObserver::get() {
    static FileObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void FileObserver::on_fight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) {
    if (win) {
        if (!fs.is_open()) {
            fs.open("log.txt");
        }
        auto [attackerX, attackerY] = attacker->get_position();
        auto [defenderX, defenderY] = defender->get_position();
        fs << std::endl << "Murder ------" << std::endl;
        fs << NPCname(attacker->gettype()) << ": ";
        fs << "{x:" << attackerX << ", y:" << attackerY << "}" << std::endl;
        fs << NPCname(defender->gettype()) << ": ";
        fs << "{x:" << defenderX << ", y:" << defenderY << "}" << std::endl;
    }
}