#ifndef CREATURE_H
#define CREATURE_H

#include "entity.h"

namespace evol {

class Creature : public Entity {
public:
    Creature(const Vector& position_, double radius_);
    void interact(Food& e_) override;
    void process() override;
};

}

#endif // CREATURE_H
