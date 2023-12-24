#pragma once

#include "NPC.hpp"
#include "Slaver.hpp"
#include "Orc.hpp"
#include "Druid.hpp"
#include "Factory.hpp"

class DataMethods {
    public:
        static void save_array(const set_t& array, const std::string& filename);
        static set_t load_array(const std::string& filename);
};

std::ostream& operator << (std::ostream& os, const set_t& array);