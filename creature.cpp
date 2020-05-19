#include "creature.h"

#include <iostream>

#include "food.h"

namespace evol {

Creature::Creature(const Vector& position_, double radius_, double angle_, double velocity_)
                               : Entity(position_, radius_, angle_), m_velocity{velocity_} {
    m_movement_value = movement_const * velocity_ / (radius_ * radius_);
}

double Creature::m_nutritionsCollected = 0;
int Creature::chunks_eaten = 0;

void Creature::interact(Food& e_) {
    m_nutritionsCollected += e_.m_nutrition;
    ++chunks_eaten;
    std::cout << "Creature (" << position().x << ", " << position().y << ") with radius " << radius()
              << " ate food (" << e_.position().x << ", " << e_.position().y <<")\n";
    e_.remove();
}

//void Creature::find_matching() {
//
//}

double Creature::movement_value() const {
    return m_movement_value;
}

void Creature::process() {
    active_motion();
    brownian_motion();
}

double Creature::first_bound_cross() {                    // returns distance to nearest bound and changes boundary_flag to value on crossing that bound
    evol::Vector tl_b = m_bounds.topLeft;
    evol::Vector br_b = m_bounds.bottomRight;
    double a = angle();
    if (a < (M_PI / 2)) {
        if ((-(tl_b.y - m_position.y) / sin(a)) < ((br_b.x - m_position.x) / cos(a))) {
            boundary_flag = 1;
            return (-(tl_b.y - m_position.y) / sin(a));
        }
        else  {
            boundary_flag = -1;
            return ((br_b.x - m_position.x) / cos(a));
        }
    }
    else if (a < M_PI) {
        if ((-(tl_b.y - m_position.y) / sin(a)) < ((tl_b.x - m_position.x) / cos(a))) {
            boundary_flag = 1;
            return (-(tl_b.y - m_position.y) / sin(a));
        }
        else {
            boundary_flag = -1;
            return ((tl_b.x - m_position.x) /cos(a));
        }
    }
    else if (a < (3 * M_PI / 2)) {
        if ((-(br_b.y - m_position.y) / sin(a)) < ((tl_b.x - m_position.x) / cos(a))) {
            boundary_flag = 1;
            return (-(br_b.y - m_position.y) / sin(a));
        }
        else {
            boundary_flag = -1;
            return ((tl_b.x - m_position.x) / cos(a));
        }
    }
    else {
        if ((-(br_b.y - m_position.y) / sin(a)) < ((br_b.x - m_position.x) / cos(a))) {
            boundary_flag = 1;
            return (-(br_b.y - m_position.y) / sin(a));
        }
        else {
            boundary_flag = -1;
            return ((br_b.x - m_position.x) / cos(a));
        }
    }
}

void Creature::active_motion() {
    double a = angle();
    double dx = m_movement_value * cos(a);
    double dy = -m_movement_value * sin(a);
    evol::Vector dpos{dx, dy}; /** Сколько пройдёт бактерия без учета границ */
    setBoundaryFlag(m_position + dpos); /** Узнаём, не выходит ли при движении
                                                    * по прямой бактерия за границы среды
                                                    */
    while (boundary_flag != 0) { /** Если выходит: */
        double dmov;
        dmov = first_bound_cross(); /** Узнаём, сколько она пройдёт до ближайшей
                                                * границы по направлению
                                                */
        m_position.x += dmov * cos(a); /** Передвигаем частицу до этой границы */
        m_position.y += -dmov * sin(a);
        m_movement_value -= dmov; /** Уменьшаем длину оставшегося хода */
        reflect(boundary_flag); /** Отражаем направление движения частицы от границы */
        dx = m_movement_value * cos(a);
        dy = -m_movement_value * sin(a);
        dpos = {dx, dy}; /** Перерассчитываем продолжение ходя по прямой */
        setBoundaryFlag(m_position + dpos);
    }
    m_position = m_position + dpos; /** Передвигаемся в конечную точку */
}


}
