#include "world.h"

#include <functional>
#include <cmath>

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
    auto entities = m_entities->entities();
    for (auto& entity : entities) {
        if (entity->removed()) {
            continue;
        }
        auto collisions = m_entities->entities(*entity);
        for (auto& collision : collisions) {
            entity->interact(*collision->getInteraction());
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

}
