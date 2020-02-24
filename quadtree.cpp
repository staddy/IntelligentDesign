#include "quadtree.h"

namespace evol {

QuadTree::QuadTree(const Rectangle& bounds_, unsigned int level_) :
    m_bounds(bounds_), m_level(level_) {

}

void QuadTree::clear() {
    m_first = nullptr;
    m_second = nullptr;
    m_entities.clear();
    m_sum = 0.0;
}

void QuadTree::split() {
    auto s = ((m_level % 2) ? m_bounds.width() : m_bounds.height()) / 2; //m_sum / m_entities.size();
    auto dv = ((m_level % 2) ? Vector{s, 0} : Vector{0, s});
    m_first = std::make_unique<QuadTree>(Rectangle{m_bounds.topLeft, m_bounds.bottomRight - dv}, m_level + 1);
    m_second = std::make_unique<QuadTree>(Rectangle{m_bounds.topLeft + dv, m_bounds.bottomRight}, m_level + 1);
}

bool QuadTree::emplace(std::shared_ptr<Entity>&& entity_) {
    if (!m_bounds.contains(entity_->rectangle())) {
        return false;
    }
    auto r = entity_->rectangle();
    if (m_first != nullptr) {
        if (m_first->m_bounds.contains(r)) {
            return m_first->emplace(std::move(entity_));
        } else if (m_second->m_bounds.contains(r)) {
            return m_second->emplace(std::move(entity_));
        }
    }
    m_entities.emplace_back(entity_);
    m_sum += ((m_level % 2) ? entity_->position().x : entity_->position().y);
    if ((m_entities.size() >= ENTITIES_PER_SPLIT) &&
            (m_first == nullptr)) {
        split();
    }
    return true;
}

void QuadTree::update(std::function<void(std::shared_ptr<Entity>&& entity_)> emplaceToParent_) {
    updateLevel(emplaceToParent_);
    if (m_first != nullptr) {
        m_first->update([this](std::shared_ptr<Entity>&& entity_) { this->emplace(std::move(entity_)); });
        m_second->update([this](std::shared_ptr<Entity>&& entity_) { this->emplace(std::move(entity_)); });
    }
}

std::vector<std::shared_ptr<Entity> > QuadTree::entities(const Rectangle& bounds_) {
    std::vector<std::shared_ptr<Entity> > vector_;
    entities(bounds_, vector_);
    return vector_;
}

void QuadTree::entities(const Rectangle& bounds_, std::vector<std::shared_ptr<Entity> >& vector_) {
    if (bounds_.intersects(m_bounds)) {
        vector_.insert(vector_.end(), m_entities.begin(), m_entities.end());
    }
    if (m_first != nullptr) {
        m_first->entities(bounds_, vector_);
        m_second->entities(bounds_, vector_);
    }
}

void QuadTree::updateLevel(std::function<void(std::shared_ptr<Entity>&& entity_)> emplaceToParent_) {
    for (auto it = m_entities.begin(); it != m_entities.end(); ) {
        if ((*it)->removed()) {
            it = m_entities.erase(it);
        } else if (!m_bounds.contains((*it)->rectangle())) {
            if (emplaceToParent_ != nullptr) {
                emplaceToParent_(std::move(*it));
            }
            it = m_entities.erase(it);
        } else if (m_first != nullptr && m_first->m_bounds.contains((*it)->rectangle())) {
            m_sum -= ((m_level % 2) ? (*it)->position().x : (*it)->position().y);
            m_first->emplace(std::move(*it));
            it = m_entities.erase(it);
        } else if (m_second != nullptr && m_second->m_bounds.contains((*it)->rectangle())) {
            m_sum -= ((m_level % 2) ? (*it)->position().x : (*it)->position().y);
            m_second->emplace(std::move(*it));
            it = m_entities.erase(it);
        } else {
            ++it;
        }
    }
}

}
