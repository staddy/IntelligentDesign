#include "chunkmap.h"

#include <cmath>

namespace evol {

bool ChunkMap::Chunk::operator==(const ChunkMap::Chunk& ck_) const {
    return std::tie(x, y) == std::tie(ck_.x, ck_.y);
}

size_t ChunkMap::ChunkHasher::operator()(const ChunkMap::Chunk& ck_) const {
    return std::hash<int>()(ck_.x) ^ std::hash<int>()(ck_.y);
}

ChunkMap::Chunk ChunkMap::chunk(const Vector& v_) const {
    return Chunk{static_cast<int>(v_.x) / m_chunkSize, static_cast<int>(v_.y) / m_chunkSize};
}

std::unordered_set<ChunkMap::Chunk, ChunkMap::ChunkHasher> ChunkMap::chunks(const Rectangle& rectangle_) const {
    std::unordered_set<Chunk, ChunkHasher> retVal;
    // TODO
    if (std::isinf(rectangle_.topLeft.x)) {
        for (const auto& e : m_entities) {
            retVal.insert(e.first);
        }
        return retVal;
    }
    auto topLeft = chunk(rectangle_.topLeft);
    auto bottomRight = chunk(rectangle_.bottomRight);
    for (int x = topLeft.x; x <= bottomRight.x; ++x) {
        for (int y = topLeft.y; y <= bottomRight.y; ++y) {
            retVal.insert({x, y});
        }
    }
    return retVal;
}

ChunkMap::ChunkMap() {

}

void ChunkMap::clear() {
    m_entities.clear();
}

bool ChunkMap::emplace(std::shared_ptr<Entity>&& entity_) {
    auto entityChunks = chunks(entity_->rectangle());
    for (const auto& c : entityChunks) {
        m_entities.insert({c, entity_});
    }
    return true;
}

void ChunkMap::update(std::function<void (std::shared_ptr<Entity>&&)> /*emplaceToParent_*/) {
    auto es = entities();
    clear();
    for (auto& e : es) {
        if (!e->removed()) {
            emplace(std::move(e));
        }
    }
}

std::vector<std::shared_ptr<Entity> > ChunkMap::entities(const Rectangle& bounds_) {
    std::vector<std::shared_ptr<Entity> > retVal;
    auto boundsChunks = chunks(bounds_);
    std::unordered_set<size_t> ids;
    for (const auto& c : boundsChunks) {
        auto entities = m_entities.equal_range(c);
        for (auto e = entities.first; e != entities.second; ++e) {
            if (ids.find(e->second->id()) == ids.end()) {
                ids.insert(e->second->id());
                retVal.push_back(e->second);
            }
        }
    }
    return retVal;
}

}
