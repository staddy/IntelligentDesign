#include "entitycontainer.h"

namespace evol {

std::vector<std::shared_ptr<Entity> > EntityContainer::entities(const Entity& entity_) {
    auto vector_ = entities(entity_.rectangle());
    for (auto it = vector_.begin(); it != vector_.end(); ) {
        if (!(*it)->intersectsWith(entity_) || (*it)->removed()) {
            it = vector_.erase(it);
        } else {
            ++it;
        }
    }
    return vector_;
}

}
