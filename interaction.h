#ifndef INTERACTION_H
#define INTERACTION_H

namespace evol {

class Food;
class Creature;

class Interaction {
public:
    virtual ~Interaction() = default;
    virtual void operator()(Food&) = 0;
    virtual void operator()(Creature&) = 0;
};

template<class T> class NoInteraction : public virtual Interaction {
public:
    void operator()(T&) override { }
};

template<class... T> class MultipleNoInteraction : public NoInteraction<T>... {
public:
    //using NoInteraction<T>::operator()...;
};

template<class T> class VoidInteraction : public MultipleNoInteraction<Food, Creature> {
public:
    VoidInteraction() = delete;
    VoidInteraction(T& interactor_) : m_interactor(interactor_) { }
protected:
    T& m_interactor;
};

}

#endif // INTERACTION_H
