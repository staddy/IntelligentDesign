#ifndef CREATURE_H
#define CREATURE_H

#include "entity.h"

namespace evol {

class Creature : public Entity {
private:
    class CreatureInteraction : public VoidInteraction<Creature> {
    public:
        CreatureInteraction(Creature& creature_);
        void operator()(Food& food_);
    };
public:
    Creature(const Vector& position_, double radius_);
    void interact(Interaction& e_) override;
    std::unique_ptr<Interaction> getInteraction() override;
    void process() override;
};

}

#endif // CREATURE_H
