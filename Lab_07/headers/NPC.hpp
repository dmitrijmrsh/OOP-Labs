#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <random>
#include <fstream>
#include <set>
#include <unordered_map>
#include <math.h>
#include <vector>
#include <time.h>
#include <shared_mutex>
#include <queue>
#include <optional>
#include <thread>

struct NPC;
struct Slaver;
struct Druid;
struct Orc;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType {
    SlaverType = 0,
    DruidType = 1,
    OrcType = 2
};

const int NPC_COUNT = 3;

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC>&, const std::shared_ptr<NPC>&, bool) = 0;
};

struct FightVisitor {
    virtual bool visit(const std::shared_ptr<Slaver>&) const = 0;
    virtual bool visit(const std::shared_ptr<Druid>&) const = 0;
    virtual bool visit(const std::shared_ptr<Orc>&) const = 0;
};

class NPC : public std::enable_shared_from_this<NPC> {
    protected:
        std::mutex mu;

        NpcType type;
        int x{0};
        int y{0};

        bool alive{true};
        int moveDistance{0};
        int killDistance{0};

        std::vector<std::shared_ptr<IFightObserver>> observers;
    public:
        NPC(NpcType, int, int);
        NPC(NpcType, std::istream&);

        NpcType& gettype();
        std::pair<int, int> get_position();

        void subscribe(const std::shared_ptr<IFightObserver>&);
        void fight_notify(const std::shared_ptr<NPC>&, bool);
        bool is_close(const std::shared_ptr<NPC>&);
        
        virtual bool accept(const std::shared_ptr<NPC>&) const = 0;
        virtual void save(std::ostream&);
        virtual void print() = 0;

        friend std::ostream& operator << (std::ostream&, NPC&);

        int getMoveDistance();
        void move(int, int, int, int);

        bool isAlive();
        void mustDie();
        
        static int throwDice();

        ~NPC() = default;
};