#define BOOST_PYTHON_STATIC_LIB
//#define BOOST_NUMPY_STATIC_LIB

#include <boost/python.hpp>
//#include <boost/python/numpy.hpp>
//#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "optimizer.h"

using namespace boost::python;
using namespace evol;

/*
class RecordDataWrap {
    ciam::RecordData m_recordData;
    numpy::dtype m_type;
    tuple m_xShape;
    tuple m_yShape;
    tuple m_strides;
public:
    RecordDataWrap(ciam::RecordData recordData_) :
        m_recordData(std::move(recordData_)),
        m_type(numpy::dtype::get_builtin<double>()),
        m_xShape(make_tuple(m_recordData.x->size())),
        m_yShape(make_tuple(m_recordData.y->size())),
        m_strides(make_tuple(sizeof(double))),
        x(numpy::from_data(static_cast<void*>(m_recordData.x->data()), m_type, m_xShape, m_strides, object(m_recordData.x))),
        y(numpy::from_data(static_cast<void*>(m_recordData.y->data()), m_type, m_yShape, m_strides, object(m_recordData.y))),
        start(m_recordData.start),
        hasX(m_recordData.hasX),
        error(m_recordData.error) { }
    numpy::ndarray x;
    numpy::ndarray y;
    double start;
    bool hasX;
    ciam::ReadError error;
};

class ChannelWrap {
    std::shared_ptr<ciam::Channel> m_channel;
public:
    ChannelWrap(const std::shared_ptr<ciam::Channel> channel_) : m_channel(channel_) { }
    std::string name() const {
        return m_channel->name();
    }
    std::string description() const {
        return m_channel->description();
    }
    double frequency() const {
        return m_channel->frequency();
    }
    double start() const {
        return m_channel->start();
    }
    unsigned long long length() const {
        return m_channel->length();
    }
    bool hasX() const {
        return m_channel->hasX();
    }
    std::string units() const {
        return m_channel->units();
    }
    ciam::ChannelType type() const {
        return m_channel->type();
    }
    RecordDataWrap readPP(unsigned long long start_, unsigned long long length_) const {
        return m_channel->read(start_, length_);
    }
    RecordDataWrap read(double startSeconds_, double lengthSeconds_) const {
        return m_channel->read(startSeconds_, lengthSeconds_);
    }
    RecordDataWrap readTP(double startSeconds_, unsigned long long length_) const {
        return m_channel->read(startSeconds_, length_);
    }
};

class RecordWrap {
    ciam::Record m_record;
public:
    RecordWrap(const std::string& fileName_) : m_record(fileName_) { }
    static RecordWrap create(const std::string& fileName_) {
        return RecordWrap(fileName_);
    }
    bool init() {
        return m_record->init();
    }
    std::string type() const {
        return m_record->type();
    }
    std::filesystem::path fileName() const {
        return m_record->fileName();
    }
    std::string directory() const {
        return m_record->directory();
    }
    std::vector<std::string> channels() const {
        return m_record->channels();
    }
    std::string subject() const {
        return m_record->subject();
    }
    std::string regime() const {
        return m_record->regime();
    }
    tm dateTime() const {
        return m_record->dateTime();
    }
    ChannelWrap getChannel(const std::string& channelName_) const {
        return m_record[channelName_];
    }
};
*/

class OptimizerWrapper {
    std::shared_ptr<Optimizer> m_optimizer = std::make_shared<Optimizer>();
public:
    void generateFirstPopulation() {
        m_optimizer->generateFirstPopulation();
    }
    void modelling() {
        m_optimizer->modelling();
    }
};


BOOST_PYTHON_MODULE(intelligentdesign) {
    class_<OptimizerWrapper>("Optimizer")
            .def("generateFirstPopulation", &OptimizerWrapper::generateFirstPopulation)
            .def("modelling", &OptimizerWrapper::modelling)
            ;
    /*
    numpy::initialize();
    class_<std::vector<std::string>>("StringList")
            .def(vector_indexing_suite<std::vector<std::string>>())
            .def("size", &std::vector<std::string>::size)
            ;
    class_<std::vector<double>>("Vector")
            .def(vector_indexing_suite<std::vector<double>>())
            .def("size", &std::vector<double>::size)
            ;
    class_<RecordDataWrap>("RecordData", no_init)
            .add_property("x", &RecordDataWrap::x)
            .add_property("y", &RecordDataWrap::y)
            .add_property("start", &RecordDataWrap::start)
            .add_property("hasX", &RecordDataWrap::hasX)
            .add_property("error", &RecordDataWrap::error)
            ;
    class_<ChannelWrap>("Channel", no_init)
            .add_property("name", &ChannelWrap::name)
            .add_property("description", &ChannelWrap::description)
            .add_property("frequency", &ChannelWrap::frequency)
            .add_property("start", &ChannelWrap::start)
            .add_property("length", &ChannelWrap::length)
            .add_property("hasX", &ChannelWrap::hasX)
            .add_property("units", &ChannelWrap::units)
            .add_property("type", &ChannelWrap::type)
            .def("readPP", &ChannelWrap::readPP)
            .def("readTP", &ChannelWrap::readTP)
            .def("read", &ChannelWrap::read)
            ;
    class_<RecordWrap>("Record", no_init)
            .def("create", &RecordWrap::create)
            .def("init", &RecordWrap::init)
            .add_property("type", &RecordWrap::type)
            .add_property("fileName", &RecordWrap::fileName)
            .add_property("directory", &RecordWrap::directory)
            .add_property("channels", &RecordWrap::channels)
            .add_property("subject", &RecordWrap::subject)
            .add_property("regime", &RecordWrap::regime)
            .add_property("dateTime", &RecordWrap::dateTime)
            .def("__getitem__", &RecordWrap::getChannel)
            ;
    register_ptr_to_python<std::shared_ptr<std::vector<double>>>();
    */
}
