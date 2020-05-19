#ifndef WORLD_H
#define WORLD_H

#include <unordered_set>
#include <vector>
#include <memory>

#include "creature.h"
#include "food.h"
#include "quadtree.h"
#include "chunkmap.h"

namespace evol {

class World {
public:
    enum class MappingMode {
        KD_TREE,
        CHUNK_MAP,
    };
    World(const Rectangle& bounds_ = {{-100.0, -100.0}, {100.0, 100.0}},
          MappingMode mappingMode_ = MappingMode::KD_TREE);

    void process();
    void addEntity(std::shared_ptr<Entity>&& entity_);
    Rectangle bounds() const;

    const int colony_size{40};
    Rectangle m_bounds;
    const int steps{20};
    const int f_chunks{100};

private:
    MappingMode m_mappingMode;
    std::unique_ptr<EntityContainer> m_entities;
};

}

#endif // WORLD_H
