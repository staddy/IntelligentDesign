#ifndef WORLD_H
#define WORLD_H

#include <unordered_set>
#include <vector>
#include <memory>

#include "entitycontainer.h"

namespace evol {

class World {
public:
    enum class MappingMode {
        KD_TREE,
        CHUNK_MAP,
    };
    World(const Rectangle& bounds_ = {{-1000.0, -1000.0}, {1000.0, 1000.0}},
          MappingMode mappingMode_ = MappingMode::CHUNK_MAP);
    void process();
    void addEntity(std::shared_ptr<Entity>&& entity_);
private:
    Rectangle m_bounds;
    MappingMode m_mappingMode;
    std::unique_ptr<EntityContainer> m_entities;
};

}

#endif // WORLD_H
