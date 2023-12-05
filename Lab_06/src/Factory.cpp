#include "../headers/Factory.hpp"

std::shared_ptr<NPC> Factory::Create(const NpcType& type, int x, int y) {
    std::shared_ptr<NPC> result;
    switch(type) {
        case NpcType::SlaverType:
            result = std::make_shared<Slaver>(x, y);
            break;
        case NpcType::DruidType:
            result = std::make_shared<Druid>(x, y);
            break;
        case NpcType::OrcType:
            result = std::make_shared<Orc>(x, y);
            break;
        default:
            throw std::invalid_argument("Unknown type of NPC:");
    }

    if (result) {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get());
    }

    return result;
}

std::shared_ptr<NPC> Factory::Create(std::istream& in) {
    std::shared_ptr<NPC> result;
    int type = NPC_COUNT + 1;
    if (in >> type) {
        switch(type) {
            case NpcType::SlaverType:
                result = std::make_shared<Slaver>(in);
                break;
            case NpcType::DruidType:
                result = std::make_shared<Druid>(in);
                break;
            case NpcType::OrcType:
                result = std::make_shared<Orc>(in);
                break;
            default:
                throw std::invalid_argument("Unknown type of NPC");
        }
    }

    if (result) {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get());
    }

    return result;
}