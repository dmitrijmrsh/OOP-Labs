#pragma once

#include <iostream>
#include <fstream>

#include "NPC.hpp"

class TextObserver : public IFightObserver {
    private:
        TextObserver() {};
    public:
        static std::shared_ptr<IFightObserver> get();
        void on_fight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) override;
};

class FileObserver : public IFightObserver {
    private:
        FileObserver() {};
        std::string NPCname(const NpcType& type);
        std::ofstream fs;
    public:
        static std::shared_ptr<IFightObserver> get();
        void on_fight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) override;
};