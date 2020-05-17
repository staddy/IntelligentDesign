#ifndef ENTITY_H
#define ENTITY_H

#include <cstddef>
#include <memory>
#include <cmath>

#include "utils.h"

namespace evol {

class Food;

class Entity {
public:
    Entity(const Vector& position_, double radius_, double angle_);
    virtual ~Entity() = default;

    double movement_const{0.1}; /** Постоянная для расчёта продвижения за один шаг */
    size_t id() const;
    const Vector& position() const;
    double radius() const;
    double angle() const;
    Rectangle bounds() const;
    Rectangle rectangle() const;

    bool intersectsWith(const Entity& e_) const;
    void reflect(int b_f); /** Изменяет направление движения при отражении от границ */

    bool removed() const;
    void remove();

    virtual void requestInteract(Entity& /*e_*/) { }
    virtual void interact(Food& /*e_*/) { }
    virtual void process() = 0;

    void setBounds(const Rectangle& bounds_);
    void setBoundaryFlag(evol::Vector curr_pos);

    void brownian_motion(); /** Осуществляет броуновское движение объекта */

protected:
    Vector m_position{};
    double m_radius{1.0};
    Rectangle m_bounds{Rectangle::INF};
    int boundary_flag{0};
private:
    double m_angle{0.0};
    size_t m_id{0};
    bool m_removed{false};
};

}

#endif // ENTITY_H
