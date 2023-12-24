#pragma once

#include "NPC.hpp"
#include "Druid.hpp"
#include "Orc.hpp"
#include "Slaver.hpp"

inline const int MAX_TIME = 20;

inline int timer = 0;

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
    private:
        std::queue<FightEvent> events;
        std::shared_mutex mtx;

        FightManager() = default;
    public:

        static FightManager& get();
        void add_event(FightEvent&& event);
        void operator()();

        ~FightManager() = default;
};