#include <iostream>
#include <chrono>

#include "world.h"
#include "creature.h"
#include "food.h"

int main(int /*argc*/, char */*argv*/[]) {
    using namespace evol;
    World world({{-100, -100}, {100, 100}}, World::MappingMode::CHUNK_MAP);
    for (double x = -80.0; x < 81.0; x += 10.0) {
        for (double y = -80.0; y < 81.0; y += 10.0) {
            world.addEntity(std::make_shared<Food>(Vector{x, y}, 5.0, 3.0));
            world.addEntity(std::make_shared<Creature>(Vector{x, y}, 1.0, 0.0, 1.0));
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
