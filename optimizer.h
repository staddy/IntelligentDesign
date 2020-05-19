#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "world.h"
#include <map>


class Optimizer : public evol::World {
private:
    double radius_lo_lim{1.0};
    double velocity_lo_lim{1.0};
    double radius_range{10.0};
    double velocity_range{10.0};
public:
    Optimizer(const evol::Rectangle& bounds_ = {{-100.0, -100.0}, {100.0, 100.0}},
              MappingMode mappingMode_ = MappingMode::KD_TREE);
    void selection_rad();
    void selection_vel();
    void generateFirstPopulation();
    void generate_food(int n);
    void generate_ent(double radius_, double velocity_);
    void modelling();
    void selection();
    static std::vector<evol::Creature::Params> population;
};

#endif // OPTIMIZER_H
