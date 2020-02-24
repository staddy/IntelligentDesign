#ifndef CHUNKMAP_H
#define CHUNKMAP_H

#include <unordered_set>

#include "entitycontainer.h"

namespace evol {

class ChunkMap : public EntityContainer {
private:
    static constexpr int DEFAULT_CHUNK_SIZE = 20;
    int m_chunkSize{DEFAULT_CHUNK_SIZE};
    struct Chunk {
        int x{0};
        int y{0};
        bool operator==(const Chunk& ck_) const;
    };
    struct ChunkHasher {
      size_t operator()(const Chunk& ck_) const;
    };
    [[nodiscard]] Chunk chunk(const Vector& v_) const;
    [[nodiscard]] std::unordered_set<Chunk, ChunkHasher> chunks(const Rectangle& rectangle_) const;
    std::unordered_multimap<Chunk, std::shared_ptr<Entity>, ChunkHasher> m_entities;
public:
    ChunkMap();
    void clear() override;
    bool emplace(std::shared_ptr<Entity>&& entity_) override;
    void update(std::function<void (std::shared_ptr<Entity>&&)> emplaceToParent_) override;
    std::vector<std::shared_ptr<Entity> > entities(const Rectangle& bounds_ = Rectangle::INF) override;
};

}

#endif // CHUNKMAP_H
