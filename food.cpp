#include "food.h"

namespace evol {

Food::FoodInteraction::FoodInteraction(Food& food_) :
    VoidInteraction<Food>(food_) { }

Food::Food(const Vector& position_, double radius_) : Entity(position_, radius_) {

}

void Food::interact(Interaction& e_) {
    e_(*this);
}

std::unique_ptr<Interaction> Food::getInteraction() {
    return std::make_unique<FoodInteraction>(*this);
}

void Food::process() {

}

}
