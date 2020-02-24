#include "creature.h"

#include "food.h"

namespace evol {

Creature::CreatureInteraction::CreatureInteraction(Creature& creature_) :
    VoidInteraction<Creature>(creature_) { }

void Creature::CreatureInteraction::operator()(Food& food_) {
    food_.remove();
}

Creature::Creature(const Vector& position_, double radius_) : Entity(position_, radius_) {

}

void Creature::interact(Interaction& e_) {
    e_(*this);
}

std::unique_ptr<Interaction> Creature::getInteraction() {
    return std::make_unique<CreatureInteraction>(*this);
}

void Creature::process() {

}

}
