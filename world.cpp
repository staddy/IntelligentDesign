#include "world.h"

#include <functional>
#include <cmath>
#include <iostream>
#include "quadtree.h"
#include "chunkmap.h"

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

void World::process() {
    std::cout << "Start\n";
    auto entities = m_entities->entities();
    std::cout << "Entities entities entities\n";
    int c=0;
    for (auto& entity : entities) {
        std::cout << "for " << ++c << "\n";
        if (entity->removed()) {
            continue;
        }
        std::cout << "Collisions\n";
        auto collisions = m_entities->entities(*entity);
        for (auto& collision : collisions) {
            std::cout << "request\n\n";
            collision->requestInteract(*entity);
        }
    }
    for (auto& entity : entities) {
        std::cout << "Step\n";
        entity->process();
    }
    std::cout << "upd\n";
    m_entities->update();
}

void World::addEntity(std::shared_ptr<Entity>&& entity_) {
    entity_->setBounds(m_bounds);
    m_entities->emplace(std::move(entity_));
}

}
