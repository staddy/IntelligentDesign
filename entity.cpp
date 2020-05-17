#include "entity.h"

namespace evol {

Entity::Entity(const Vector& position_, double radius_, double angle_)
    : m_position(position_), m_radius(radius_), m_angle(angle_) {
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

double Entity::angle() const {
    return m_angle;
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

void Entity::setBoundaryFlag(evol::Vector curr_pos) {
    evol::Vector tl_b = m_bounds.topLeft;
    evol::Vector br_b = m_bounds.bottomRight;
    if ((curr_pos.y > tl_b.y) || (curr_pos.y < br_b.y))
        boundary_flag = 1;
    else if ((curr_pos.x < tl_b.x) || (curr_pos.x > br_b.x))
        boundary_flag = -1;
    else boundary_flag = 0;
}

void Entity::reflect(int b_f) {
    if (b_f == 1)                          //reflect from horizontal boundaries
        m_angle = 2 * M_PI - m_angle;
    else {                                 //reflect from vertical boundaries
        if (m_angle <= M_PI)
            m_angle = M_PI - m_angle;
        else
            m_angle = 3 * M_PI - m_angle;
    }
}

void Entity::brownian_motion() {
    m_position.x += cos(m_angle) * movement_const / m_radius; /** Движение на соответственную величину в старом направлении */
    m_position.y += -sin(m_angle) * movement_const / m_radius;
    m_angle = 2 * M_PI * rand() / RAND_MAX; /** Случайное изменение угла на угол от 0 до 2 * M_PI */
    setBoundaryFlag(m_position); /** Вычисляем, не вышел ли объект за пределы среды */
    if (boundary_flag != 0) { /** Если да, смещаем до ближайшей границы */
        if (m_position.x < m_bounds.topLeft.x)
            m_position.x = m_bounds.topLeft.x;
        else if (m_position.x > m_bounds.bottomRight.x)
            m_position.x = m_bounds.bottomRight.x;
        if (m_position.y > m_bounds.topLeft.y)
            m_position.y = m_bounds.topLeft.y;
        else if (m_position.y < m_bounds.bottomRight.y)
            m_position.y = m_bounds.bottomRight.y;
    }
}

}
