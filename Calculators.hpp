#ifndef _ACADEMY_CALCULATOR_HPP_
#define _ACADEMY_CALCULATOR_HPP_

#include "Data.hpp"

// Path calculator abstract interface class
class AbstractPathCalculator {
    public:
        // Disable default constructor because no data setters are implemented
        AbstractPathCalculator()=delete;

        // Construct from input data aggregate
        AbstractPathCalculator(const Data& data): _data{data} {}

        // Virtual destructor avoids double free
        virtual ~AbstractPathCalculator() {}

        // Evaluate points
        virtual Type::Path eval(const Type::PathSpec&) const = 0;

    protected:
        Data _data;

        Type::Path&& _initOutput(const Type::PathSpec&) const;
};

// Path calculator according to flat earth model
class FlatEarthPathCalculator final
: public AbstractPathCalculator {
    public:

        // Override evaluation method
        Type::Path eval(const Type::PathSpec&) const override;
};


// Path calculator according to spherical earth model
class SphericalEarthPathCalculator final
: public AbstractPathCalculator {
    public:

        // Override evaluation method
        Type::Path eval(const Type::PathSpec&) const override;
};

// Path calculator according to WGS84 model
class WGS84PathCalculator final
: public AbstractPathCalculator {
    public:

        // Override evaluation method
        Type::Path eval(const Type::PathSpec&) const override;
};

#endif  // _ACADEMY_CALCULATOR_HPP_