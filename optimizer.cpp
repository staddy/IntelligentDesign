#include "optimizer.h"
#include <iostream>

Optimizer::Optimizer(const evol::Rectangle& bounds_, MappingMode mappingMode_) :
    evol::World(bounds_, mappingMode_) {
}

void Optimizer::generate_food(int n) {
    int i = 0;
    double x, y;
    while (i < n) {
        y = rand() * m_bounds.height() / RAND_MAX;
        if ((rand() / RAND_MAX) < (y / m_bounds.height())) {
            y += m_bounds.topLeft.y;
            x = m_bounds.width() * rand() / RAND_MAX + m_bounds.topLeft.x;
            double angle = 2 * M_PI * rand() / RAND_MAX;
            double f_size = 1.0 + 3.0 * rand() / RAND_MAX;
            addEntity(std::make_shared<evol::Food>(evol::Vector{x, y}, f_size, angle));
            ++i;
            std::cout << "Food " << i << ": (" << x << ", " << y << ")\n";
        }
    }
}

void Optimizer::generate_ent(double radius_, double velocity_) {
    double x = m_bounds.width() * rand() / RAND_MAX + m_bounds.topLeft.x;
    double y = m_bounds.height() * rand() / RAND_MAX + m_bounds.topLeft.y;
    double angle = 2 * M_PI * rand() / RAND_MAX;
    addEntity(std::make_shared<evol::Creature>(evol::Vector{x, y}, radius_, angle, velocity_));
    std::cout << "Bacteria " << ": (" << x << ", " << y << ")\n";

}

void Optimizer::generateFirstPopulation() {
    for (int i = 0; i < colony_size; ++i) {
        population.push_back({radius_lo_lim + radius_range * i / colony_size,
                              velocity_lo_lim + velocity_range - i * velocity_range / colony_size, 0});
    }
}

void Optimizer::modelling() {
    int i;
    evol::Creature::chunks_eaten = 0;
    evol::Creature::m_nutritionsCollected = 0;

    for (auto& ent : population)
        generate_ent(ent.radius, ent.velocity);
    generate_food(f_chunks);
    std::cout << "\n";
    for (i = 0; i < steps; ++i) {
        process();
        generate_food(evol::Creature::chunks_eaten);
        std::cout << "Step " << i+1 << ", nutritions collected: "
                  << evol::Creature::m_nutritionsCollected << "\n\n";
        evol::Creature::chunks_eaten = 0;
    }
    std::cout << "End of life\n";
}

void Optimizer::selection() {
    for (auto& ent : population) {

    }
}
