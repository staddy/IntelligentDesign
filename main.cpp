#include <iostream>
#include <chrono>

#include "world.h"
#include "creature.h"
#include "food.h"

int main(int /*argc*/, char */*argv*/[]) {
    using namespace evol;
    World world({{-1000, -1000}, {1000, 1000}}, World::MappingMode::CHUNK_MAP);
    world.addEntity(std::make_shared<Creature>(Vector{10.0, 10.0}, 10.0));
    world.addEntity(std::make_shared<Food>(Vector{10.0, 10.0}, 10.0));
    for (double x = -800.0; x < 800.0; x += 5.0) {
        for (double y = -800.0; y < 800.0; y += 75) {
            world.addEntity(std::make_shared<Food>(Vector{x, y}, 5.0));
            world.addEntity(std::make_shared<Creature>(Vector{x, y}, 1.0));
        }
        std::cout << "INIT " << x << std::endl;
    }
    auto begin = std::chrono::steady_clock::now();
    std::cout << "1st" << std::endl;
    world.process();
    std::cout << "1st done" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::steady_clock::now() - begin).count() << std::endl;
    begin = std::chrono::steady_clock::now();
    std::cout << "2nd" << std::endl;
    world.process();
    std::cout << "2nd done" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::steady_clock::now() - begin).count() << std::endl;
    return 0;
}
