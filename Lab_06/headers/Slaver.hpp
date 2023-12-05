#pragma once

#include "NPC.hpp"

struct SlaverVisitor : public FightVisitor {
    bool visit(const std::shared_ptr<Slaver>&) const override;
    bool visit(const std::shared_ptr<Druid>&) const override;
    bool visit(const std::shared_ptr<Orc>&) const override;
};

class Slaver : public NPC {
    public:
        Slaver();
        Slaver(int, int);
        Slaver(std::istream&);

        void save(std::ostream&) override;
        bool accept(const std::shared_ptr<FightVisitor>&, const std::shared_ptr<NPC>&) const override;
        friend std::ostream& operator << (std::ostream&, Slaver&);
        void print() override;

        ~Slaver() = default;
};