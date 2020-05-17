#include "food.h"

namespace evol {

Food::Food(const Vector& position_, double radius_, double angle_)
                 : Entity(position_, radius_, angle_) {
    m_nutrition = nutr_const * radius_ * radius_;
}

void Food::requestInteract(Entity& e_) {
    e_.interact(*this);
}

void Food::process() {
    brownian_motion();
}

}
