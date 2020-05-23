#define BOOST_PYTHON_STATIC_LIB

#include <boost/python.hpp>

#include "optimizer.h"

using namespace boost::python;
using namespace evol;

class OptimizerWrapper {
    std::shared_ptr<Optimizer> m_optimizer = std::make_shared<Optimizer>();
public:
    void generateFirstPopulation() {
        m_optimizer->generateFirstPopulation();
    }
    void modelling() {
        m_optimizer->modelling();
    }
    void selection() {
        m_optimizer->selection();
    }
    void set_bounds(double tlx, double tly, double brx, double bry) {
        m_optimizer->set_bounds({{tlx, tly}, {brx, bry}});
    }
    void set_selection_modifiers(double b, double m) {
        m_optimizer->set_selection_modifiers(b, m);
    }
    void show_bounds() {
        m_optimizer->show_bounds();
    }
    void show_selection_params() {
        m_optimizer->show_selection_params();
    }

};


BOOST_PYTHON_MODULE(intelligentdesign) {
    class_<OptimizerWrapper>("Optimizer")
            .def("generateFirstPopulation", &OptimizerWrapper::generateFirstPopulation)
            .def("modelling", &OptimizerWrapper::modelling)
            .def("selection", &OptimizerWrapper::selection)
            .def("set_bounds", &OptimizerWrapper::set_bounds)
            .def("set_selection_modifiers", &OptimizerWrapper::set_selection_modifiers)
            .def("show_bounds", &OptimizerWrapper::show_bounds)
            .def("show_selection_params", &OptimizerWrapper::show_selection_params)
            ;
}
