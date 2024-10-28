#ifndef _ACADEMY_CALCULATOR_HPP_
#define _ACADEMY_CALCULATOR_HPP_

#include "Data.hpp"

// Path calculator abstract interface class
class AbstractPathCalculator {
    public:
        // Construct from input data aggregate
        AbstractPathCalculator(const Data& data, const Type::PathSpec& path)
        : _data{data}, _path{path} {}

        // Virtual destructor avoids double free
        virtual ~AbstractPathCalculator() {}

        // Evaluate points
        virtual Type::Path eval() const = 0;

    protected:
        Data           _data;
        Type::PathSpec _path;
};

// Path calculator according to flat earth model
class FlatEarthPathCalculator final
: public AbstractPathCalculator {
    public:

        // Override evaluation method
        Type::Path eval() const override;
};


// Path calculator according to flat earth model
class SphericalEarthPathCalculator final
: public AbstractPathCalculator {
    public:

        // Override evaluation method
        Type::Path eval() const override;
};

// Path calculator according to flat earth model
class WGS84PathCalculator final
: public AbstractPathCalculator {
    public:

        // Override evaluation method
        Type::Path eval() const override;
};

#endif  // _ACADEMY_CALCULATOR_HPP_