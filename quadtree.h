#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <memory>
#include <functional>

#include "entitycontainer.h"

namespace evol {

class QuadTree : public EntityContainer {
public:
    QuadTree(const Rectangle& bounds_, unsigned int level_ = 0);
    void clear() override;
    bool emplace(std::shared_ptr<Entity>&& entity_) override;
    void update(std::function<void(std::shared_ptr<Entity>&& entity_)> emplaceToParent_ = nullptr) override;
    std::vector<std::shared_ptr<Entity> > entities(const Rectangle& bounds_ = Rectangle::INF) override;
private:
    void split();
    void entities(const Rectangle& bounds_, std::vector<std::shared_ptr<Entity> >& vector_);
    void updateLevel(std::function<void(std::shared_ptr<Entity>&& entity_)> emplaceToParent_ = nullptr);
    static constexpr size_t ENTITIES_PER_SPLIT = 1;
    std::unique_ptr<QuadTree> m_first{nullptr};
    std::unique_ptr<QuadTree> m_second{nullptr};
    std::vector<std::shared_ptr<Entity> > m_entities;
    Rectangle m_bounds;
    unsigned int m_level{0};
    double m_sum{0.0};
};

}

#endif // QUADTREE_H
