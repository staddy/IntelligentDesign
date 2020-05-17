#ifndef CREATURE_H
#define CREATURE_H

#include "entity.h"

namespace evol {

class Creature : public Entity {
private:
    double m_velocity;
    double m_movement_value; /** Длина шага */

public:
    static double m_nutritionsCollected;
    static int chunks_eaten;
    Creature(const Vector& position_, double radius_, double angle_, double velocity_);
    void interact(Food& e_) override;
    void process() override;
    double movement_value() const;
    void active_motion(); /** Осуществляет активное движение в заданном направлении */
    double first_bound_cross(); /** Определяет, какая граница была преодолена первой */

};

}

#endif // CREATURE_H
