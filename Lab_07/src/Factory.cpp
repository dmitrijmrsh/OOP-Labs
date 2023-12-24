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

std::shared_ptr<FightVisitor> VisitorFactory::Create(const NpcType& type) {
    std::shared_ptr<FightVisitor> result;
    switch (type) {
        case NpcType::DruidType:
            result = std::static_pointer_cast<FightVisitor>(std::make_shared<DruidVisitor>());
            break;

        case NpcType::OrcType:
            result = std::static_pointer_cast<FightVisitor>(std::make_shared<OrcVisitor>());
            break;

        case NpcType::SlaverType:
            result = std::static_pointer_cast<FightVisitor>(std::make_shared<SlaverVisitor>());
            break;
        
        default:
            throw std::invalid_argument("Unknown type of Npc and Npc visitor");
    }

    return result;
}