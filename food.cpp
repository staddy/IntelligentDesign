#include "food.h"

namespace evol {

Food::Food(const Vector& position_, double radius_) : Entity(position_, radius_) {

}

void Food::requestInteract(Entity& e_) {
    e_.interact(*this);
}

void Food::process() {

}

}
