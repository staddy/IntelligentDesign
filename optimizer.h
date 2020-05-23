#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)
#include "world.h"
#include <map>


class Optimizer : public evol::World {
private:
    double radius_lo_lim{1.0};
    double velocity_lo_lim{1.0};
    double radius_range{10.0};
    double velocity_range{10.0};
    double sel_best{0.6};
    double sel_best2{0.4};
    double mutation{1.0};
public:
    Optimizer(const evol::Rectangle& bounds_ = {{-100.0, -100.0}, {100.0, 100.0}});
    void generateFirstPopulation();
    void generate_food(int n);
    void generate_ent(double radius_, double velocity_);
    void modelling();
    void selection();
    void show_bounds();
    void show_selection_params();
    void set_bounds(evol::Rectangle bounds_);
    void set_selection_modifiers(double b, double m);
    static std::vector<evol::Creature::Params> population;
};

#endif // OPTIMIZER_H
