#ifndef FOOD_H
#define FOOD_H

#include "entity.h"

namespace evol {

class Food : public Entity {
private:
    class FoodInteraction : public VoidInteraction<Food> {
    public:
        FoodInteraction(Food& food_);
    };
public:
    Food(const Vector& position_, double radius_);
    void interact(Interaction& e_) override;
    std::unique_ptr<Interaction> getInteraction() override;
    void process() override;
};

}

#endif // FOOD_H
