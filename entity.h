#ifndef ENTITY_H
#define ENTITY_H

#include <cstddef>
#include <memory>

#include "utils.h"
#include "interaction.h"

namespace evol {

class Interaction;

class Entity {
public:
    Entity(const Vector& position_, double radius_);
    virtual ~Entity() = default;
    [[nodiscard]] size_t id() const;
    [[nodiscard]] const Vector& position() const;
    [[nodiscard]] double radius() const;
    [[nodiscard]] bool intersectsWith(const Entity& e_) const;
    [[nodiscard]] bool removed() const;
    [[nodiscard]] Rectangle rectangle() const;
    void remove();
    virtual void interact(Interaction& e_) = 0;
    virtual std::unique_ptr<Interaction> getInteraction() = 0;
    virtual void process() = 0;
    void setBounds(const Rectangle& bounds_);
protected:
    Vector m_position{};
    double m_radius{0.0};
    Rectangle m_bounds{Rectangle::INF};
private:
    size_t m_id{0};
    bool m_removed{false};
};

}

#endif // ENTITY_H
