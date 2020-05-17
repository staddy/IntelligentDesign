#include "world.h"

#include <functional>
#include <cmath>
#include <iostream>
#include "quadtree.h"
#include "chunkmap.h"
#include "creature.h"
#include "food.h"

namespace evol {

World::World(const Rectangle& bounds_, MappingMode mappingMode_) :
    m_bounds(bounds_), m_mappingMode(mappingMode_) {
    switch (m_mappingMode) {
    case MappingMode::KD_TREE:
        m_entities = std::make_unique<QuadTree>(m_bounds);
        break;
    case MappingMode::CHUNK_MAP:
        m_entities = std::make_unique<ChunkMap>();
        break;
    }
}

void World::generate_food(int n) {
    int i = 0;
    double x, y;
    while (i < n) {
        y = rand() * m_bounds.height() / RAND_MAX;
        if ((rand() / RAND_MAX) < (y / m_bounds.height())) {
            y += m_bounds.topLeft.y;
            x = m_bounds.width() * rand() / RAND_MAX + m_bounds.topLeft.x;
            double angle = 2 * M_PI * rand() / RAND_MAX;
            double f_size = 1.0 + 4.0 * rand() / RAND_MAX;
            addEntity(std::make_shared<Food>(Vector{x, y}, f_size, angle));
            ++i;
            std::cout << "Food " << i << ": (" << x << ", " << y << ")\n";
        }
    }
}

void World::generate_ent(int n, double radius_, double velocity_) {
    for (int i = 0; i < n; ++i) {
        double x = m_bounds.width() * rand() / RAND_MAX + m_bounds.topLeft.x;
        double y = m_bounds.height() * rand() / RAND_MAX + m_bounds.topLeft.y;
        double angle = 2 * M_PI * rand() / RAND_MAX;
        addEntity(std::make_shared<Creature>(Vector{x, y}, radius_, angle, velocity_));
        std::cout << "Bacteria " << i+1 << ": (" << x << ", " << y << ")\n";
    }
}

void World::modelling(double velocity_, double radius_) {
    generate_food(f_chunks);
    generate_ent(colony_size, radius_, velocity_);
    for (int i = 0; i < steps; ++i) {
        process();
        generate_food(Creature::chunks_eaten);
        std::cout << "Step " << i+1 << ", nutritions collected:" << Creature::m_nutritionsCollected << "\n\n";
        Creature::chunks_eaten = 0;
        for (auto& entity : m_entities->entities()) {
            entity->step();
        }

    }
    std::cout << "End of life\n";
}

void World::process() {
    std::cout << "Start\n";
    auto entities = m_entities->entities();
    for (auto& entity : entities) {
        if (entity->removed()) {
            continue;
        }
        auto collisions = m_entities->entities(*entity);
        for (auto& collision : collisions) {
            collision->requestInteract(*entity);
        }
    }
    for (auto& entity : entities) {
        entity->process();
    }
    m_entities->update();
}

void World::addEntity(std::shared_ptr<Entity>&& entity_) {
    entity_->setBounds(m_bounds);
    m_entities->emplace(std::move(entity_));
}

Rectangle World::bounds() const {
    return m_bounds;
}

}
