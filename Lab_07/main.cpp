#include "headers/NPC.hpp"
#include "headers/Slaver.hpp"
#include "headers/Orc.hpp"
#include "headers/Druid.hpp"
#include "headers/Factory.hpp"
#include "headers/Observers.hpp"
#include "headers/DataMethods.hpp"
#include "headers/FightManager.hpp"

std::mutex print_mutex;

int main() {
    const int maxX{20};
    const int maxY{20};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 500);

    set_t array;

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 30; ++i) {
        array.insert(Factory::Create(NpcType(dis(gen) % 3), dis(gen) % maxX, dis(gen) % maxY));
    }

    std::cout << "Saving ..." << std::endl;
    DataMethods::save_array(array, "npc.txt");

    std::cout << "Loading..." << std::endl;
    array = DataMethods::load_array("npc.txt");

    std::cout << "Starting list:" << std::endl << array;

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&array, maxX, maxY, &dis, &gen]() {
        while(true) {
            if (timer == MAX_TIME) {
                break;
            }
            for (const std::shared_ptr<NPC>& npc : array) {
                if (npc->isAlive()) {
                    int deltaX = dis(gen) % (npc->getMoveDistance() * 2) - npc->getMoveDistance();
                    int deltaY = dis(gen) % (npc->getMoveDistance() * 2) - npc->getMoveDistance();
                    npc->move(deltaX, deltaY, maxX, maxY);
                }
            }
            for (const std::shared_ptr<NPC>& npc : array) {
                for (const std::shared_ptr<NPC>& other : array) {
                    if (other != npc && npc->isAlive() && other->isAlive() && npc->is_close(other)) {
                        FightManager::get().add_event({npc, other});
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });

    while(true) {
        if (timer == MAX_TIME) {
            break;
        }
        const int grid{20}, step_x{maxX / grid}, step_y{maxY / grid};
        {
            std::array<char, grid* grid> fields{0};
            for (const std::shared_ptr<NPC>& npc : array) {
                auto [x, y] = npc->get_position();
                int i = x / step_x;
                int j = y / step_y;

                if (npc->isAlive()) {
                    switch (npc->gettype()) {
                        case NpcType::DruidType:
                            fields[i + grid * j] = 'D';
                            break;
                        case NpcType::OrcType:
                            fields[i + grid * j] = 'O';
                            break;
                        case NpcType::SlaverType:
                            fields[i + grid * j] = 'S';
                            break;
                        
                        default:
                            break;
                    }
                } else {
                    fields[i + grid * j] = '.';
                }
            }

            std::lock_guard<std::mutex> lck(print_mutex);
            for (int j = 0; j < grid; ++j) {
                for (int i = 0; i < grid; ++i) {
                    char c = fields[i + j * grid];
                    if (c != 0) {
                        std::cout << "[" << c << "]";
                    } else {
                        std:: cout << "[ ]";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ++timer;
    }

    move_thread.join();
    fight_thread.join();

    std::cout << "Survivors:" << std::endl << array;

    return 0;
}