#include "../headers/DataMethods.hpp"

void DataMethods::save_array(const set_t& array, const std::string& filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto& elem : array) {
        elem->save(fs);
    }
    fs.flush();
    fs.close();
}

set_t DataMethods::load_array(const std::string& filename) {
    set_t result;
    int count, x, y;
    NpcType type;
    char temp;
    std::string x_numb, y_numb, npc_type, npc_count;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        while(1) {
            is.get(temp);
            if (is.eof()) {
                throw std::invalid_argument("Empty file");
            }
            if (temp == '\n') {
                break;
            }
            if (temp < '0' || temp > '9') {
                throw std::invalid_argument("Bad chars in load-file");
            }
            npc_count += temp;
        }
        if (npc_count.empty()) {
            throw std::invalid_argument("Bad load-file structure: no npc count");
        }
        count = std::stoi(npc_count);
        npc_count.clear();

        for (int i = 0; i < count; ++i) {
            if (is.eof()) {
                throw std::invalid_argument("Bad load-file structure:no type etc.");
            }
            while(1) {
                is.get(temp);
                if (is.eof()) {
                    throw std::invalid_argument("Bad load-file structure: bad npc_type");
                }
                if (temp == '\n') {
                    break;
                }
                if (temp < '0' || temp > '9') {
                    throw std::invalid_argument("Bad chars in load-file");
                }
                npc_type += temp;
            }
            if (npc_type.empty()) {
                throw std::invalid_argument("Bad load-file structure: no npc-type");
            }
            type = NpcType(std::stoi(npc_type));
            npc_type.clear();
            if (is.eof()) {
                throw std::invalid_argument("Bad load-file structure: no x,y etc.");
            }

            while(1) {
                is.get(temp);
                if (is.eof()) {
                    throw std::invalid_argument("Bad load-file structure: bad x number");
                }
                if (temp == '\n') {
                    break;
                }
                if (temp < '0' || temp > '9') {
                    throw std::invalid_argument("Bad chars in load-file");
                }
                x_numb += temp;    
            }
            if (x_numb.empty()) {
                throw std::invalid_argument("Bad load-file structure: no x number");
            }
            x = std::stoi(x_numb);
            x_numb.clear();
            if (is.eof()) {
                throw std::invalid_argument("Bad load-file structure: no y");
            }

            while(1) {
                is.get(temp);
                if (temp == '\n' || is.eof()) {
                    break;
                }
                if (temp < '0' || temp > '9') {
                    throw std::invalid_argument("Bad chars in load-file");
                }
                y_numb += temp;    
            }
            if (y_numb.empty()) {
                throw std::invalid_argument("Bad load-file structure: no y number");
            }
            y = std::stoi(y_numb);
            y_numb.clear();

            result.insert(Factory::Create(type, x, y));
        }
        is.close();
    } else {
        throw std::invalid_argument("Error opening file");
    }
    return result;
}