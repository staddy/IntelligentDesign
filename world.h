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
    World(const Rectangle& bounds_ = {{-100.0, -100.0}, {100.0, 100.0}},
          MappingMode mappingMode_ = MappingMode::KD_TREE);
    void process();
    void addEntity(std::shared_ptr<Entity>&& entity_);
    Rectangle bounds() const;
    void modelling(double velocity_, double radius_);
    void generate_food(int n);
    void generate_ent(int n, double radius_, double velocity_);
private:
    Rectangle m_bounds;
    MappingMode m_mappingMode;
    std::unique_ptr<EntityContainer> m_entities;
    const int steps{20};
    int f_chunks{100};
    int colony_size{30};
};

}

#endif // WORLD_H
