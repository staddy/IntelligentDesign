#ifndef ENTITYCONTAINER_H
#define ENTITYCONTAINER_H

#include <memory>
#include <functional>

#include "entity.h"

namespace evol {

class EntityContainer {
public:
    EntityContainer() = default;
    virtual ~EntityContainer() = default;
    virtual void clear() = 0;
    virtual bool emplace(std::shared_ptr<Entity>&& entity_) = 0;
    virtual void update(std::function<void(std::shared_ptr<Entity>&& entity_)> emplaceToParent_ = nullptr) = 0;
    virtual std::vector<std::shared_ptr<Entity> > entities(const Rectangle& bounds_ = Rectangle::INF) = 0;
    virtual std::vector<std::shared_ptr<Entity> > entities(const Entity& entity_);
};

}

#endif // ENTITYCONTAINER_H
