#include "creature.h"

#include <iostream>

#include "food.h"

namespace evol {

Creature::Creature(const Vector& position_, double radius_) : Entity(position_, radius_) {

}

void Creature::interact(Food& e_) {
    //m_collected += e_.value();
    static size_t c = 0;
    std::cout << "creature " << ++c << "\n";
    e_.remove();
}

void Creature::process() {

}

}
