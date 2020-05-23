#include "optimizer.h"
#include <iostream>

std::vector<evol::Creature::Params> Optimizer::population;

Optimizer::Optimizer(const evol::Rectangle& bounds_) :
    evol::World(bounds_, MappingMode::KD_TREE) {
}

void Optimizer::generate_food(int n) {
    int i = 0;
    double x, y;
    while (i < n) {
        y = rand() * m_bounds.height() / RAND_MAX;
        if ((rand() / RAND_MAX) < (y / m_bounds.height())) {
            y += m_bounds.topLeft.y;
            x = m_bounds.width() * rand() / RAND_MAX + m_bounds.topLeft.x;
            double angle = 2 * M_PI * rand() / RAND_MAX;
            double f_size = 1.0 + 3.0 * rand() / RAND_MAX;
            addEntity(std::make_shared<evol::Food>(evol::Vector{x, y}, f_size, angle));
            ++i;
            //std::cout << "Food " << i << ": (" << x << ", " << y << ")\n";
        }
    }
}

void Optimizer::generate_ent(double radius_, double velocity_) {
    double x = m_bounds.width() * rand() / RAND_MAX + m_bounds.topLeft.x;
    double y = m_bounds.height() * rand() / RAND_MAX + m_bounds.topLeft.y;
    double angle = 2 * M_PI * rand() / RAND_MAX;
    addEntity(std::make_shared<evol::Creature>(evol::Vector{x, y}, radius_, angle, velocity_));
    //std::cout << "Bacteria " << ": (" << x << ", " << y << ")\n";

}

void Optimizer::generateFirstPopulation() {
    for (int i = 0; i < colony_size; ++i) {
        double vel, rad;
        vel = velocity_lo_lim + velocity_range * rand() / RAND_MAX;
        rad = radius_lo_lim + radius_range * rand() / RAND_MAX;
        population.push_back({rad, vel, 0});
    }
}

void Optimizer::modelling() {
    int i;
    evol::Creature::chunks_eaten = 0;
    evol::Creature::m_nutritionsCollected = 0;

    for (auto& ent : population) {
        generate_ent(ent.radius, ent.velocity);
        std::cout << "bact: r=" << ent.radius << ", v=" << ent.velocity << ", n=" << ent.nutr << "\n";
    }
    generate_food(f_chunks);
    //std::cout << "\n";
    for (i = 0; i < steps; ++i) {
        process();
        generate_food(evol::Creature::chunks_eaten);
        //std::cout << "Step " << i+1 << ", nutritions collected: " << evol::Creature::m_nutritionsCollected << "\n\n";
        evol::Creature::chunks_eaten = 0;
    }
    std::cout << "End of life\n";
}

void Optimizer::selection() {
    double max1, max2, min, vel1{1.0}, vel2{1.0}, rad1{1.0}, rad2{1.0};
    max1 = 0.0;
    max2 = 0.0;
    min = RAND_MAX;

    for (auto& ent : population) {
        std::cout << "AFTER bact: r=" << ent.radius << ", v=" << ent.velocity << ", n=" << ent.nutr << "\n";
        if (ent.nutr < min)
           min = ent.nutr;
       if ((max1 == 0.0) && (ent.nutr > 0)) {
           max1 = ent.nutr;
           vel1 = ent.velocity;
           rad1 = ent.radius;
       }
       if (ent.nutr > max2) {
           max1 = max2;
           vel1 = vel2;
           rad1 = rad2;
           max2 = ent.nutr;
           vel2 = ent.velocity;
           rad2 = ent.radius;
       }
       else if (ent.nutr > max1) {
           max1 = ent.nutr;
           vel1 = ent.velocity;
           rad1 = ent.radius;
       }
    }

    std::cout << "Nutritions collecting results: min=" << min << ", max1=" << max1 << ", max2=" << max2 <<"\n";
    //std::cout << "best vel: " << vel2 << ", best2 vel: " << vel1 << ";\nbest rad: " << rad2 << "best2 rad: " << rad1 <<"\n";

    double sel_vel, sel_rad;
    sel_vel = sel_best2 * vel1 + sel_best * vel2 + mutation * rand() / RAND_MAX;
    sel_rad = sel_best2 * rad1 + sel_best * rad2 + mutation * rand() / RAND_MAX;

    int i = 0;

    for (auto& ent : population) {
        if ((fabs(ent.nutr - min) < 0.001) && (i == 0)) {
            //std::cout << ++i << ". before: nutr=" << ent.nutr << ", rad=" << ent.radius << ", vel=" << ent.velocity << ";\n";
            ent.radius = sel_rad;
            ent.velocity = sel_vel;
            //std::cout << "after: rad=" << ent.radius << ", vel=" << ent.velocity << ";\n";
            ++i;
        }
        ent.nutr = 0.0;
    }
    std::cout << "A bacterium was replaced by one with radius=" << sel_rad << " and velocity=" << sel_vel << "\n";
}

void Optimizer::set_bounds(evol::Rectangle bounds_) {
    m_bounds = bounds_;
}

void Optimizer::show_bounds() {
    std::cout << "Now your world's boundaries are [(" << m_bounds.topLeft.x << ", "
                  << m_bounds.topLeft.y << "), (" << m_bounds.bottomRight.x <<
                  ", " << m_bounds.bottomRight.y << ")]\n";
}

void Optimizer::set_selection_modifiers(double b, double m) {
    sel_best = b;
    sel_best2 = 1 - b;
    mutation = m;
}

void Optimizer::show_selection_params() {
    std::cout << "Amplifiers of the best: " << sel_best << ", 2nd best: " <<
                 sel_best2 << ", mutation: " << mutation << "\n";

}
