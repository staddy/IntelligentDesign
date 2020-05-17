#ifndef FOOD_H
#define FOOD_H

#include "entity.h"

namespace evol {

class Food : public Entity {
public:
    Food(const Vector& position_, double radius_, double angle_);
    void requestInteract(Entity& e_) override;
    void process() override;
    double m_nutrition{};

private:
    double nutr_const{5.0}; /** Константа, участвующая в формуле расчета питательной ценности частицы */
};

}

#endif // FOOD_H
