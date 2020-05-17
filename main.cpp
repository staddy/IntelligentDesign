#include <iostream>
#include <chrono>

#include "world.h"
#include "creature.h"
#include "food.h"

int main(int /*argc*/, char */*argv*/[]) {
    using namespace evol;
    World world({{-100, -100}, {100, 100}}, World::MappingMode::KD_TREE);
    std::cout << "world created\n";
    Creature b1({10.0, 10.0}, 2.0, 0.0, 2.0);
    Creature b2({-10.0, 10.0}, 2.0, M_PI/2, 2.0);
    std::cout << "creatures created\n";
    b1.setBounds(world.bounds());
    b2.setBounds(world.bounds());
    std::cout << "creature 1: (" << b1.position().x << ", " << b1.position().y << ");\n";
    std::cout << "creature 2: (" << b2.position().x << ", " << b2.position().y << ");\n";
    std::cout << "bounds: (" << b1.bounds().topLeft.x << "; " << b1.bounds().topLeft.y << "), ("
              << b1.bounds().bottomRight.x << "; " << b1.bounds().bottomRight.y << ")\n";
    b1.active_motion();
    std::cout << "act1\n";
    b2.active_motion();

/*    for (double x = -80.0; x < 81.0; x += 10.0) {
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
*/
    return 0;
}
