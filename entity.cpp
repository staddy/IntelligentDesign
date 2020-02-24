#include "entity.h"

namespace evol {

Entity::Entity(const Vector& position_, double radius_) : m_position(position_), m_radius(radius_) {
    static size_t s_id = 0;
    m_id = s_id++;
}

size_t Entity::id() const {
    return m_id;
}

const Vector& Entity::position() const {
    return m_position;
}

double Entity::radius() const {
    return m_radius;
}

bool Entity::intersectsWith(const Entity& e_) const {
    return (m_position - e_.m_position).length() < (m_radius + e_.m_radius);
}

bool Entity::removed() const {
    return m_removed;
}

Rectangle Entity::rectangle() const {
    auto r = Vector{m_radius, m_radius};
    return Rectangle{m_position - r, m_position + r};
}

void Entity::remove() {
    m_removed = true;
}

void Entity::setBounds(const Rectangle& bounds_) {
    m_bounds = bounds_;
}

}
