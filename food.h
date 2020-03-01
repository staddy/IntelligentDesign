#ifndef FOOD_H
#define FOOD_H

#include "entity.h"

namespace evol {

class Food : public Entity {
public:
    Food(const Vector& position_, double radius_);
    void requestInteract(Entity& e_) override;
    void process() override;
};

}

#endif // FOOD_H
