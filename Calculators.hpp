#ifndef _ACADEMY_CALCULATOR_HPP_
#define _ACADEMY_CALCULATOR_HPP_

#include "Data.hpp"

/*! @class AbstractPathCalculator
    @brief Path calculator abstract interface class
*/
class AbstractPathCalculator {
    public:
        //! @brief Disable default constructor because no data setters are implemented
        AbstractPathCalculator()=delete;

        /*! @brief Construct from input data aggregate
            @param data An input data aggregate, see Data
        */
        AbstractPathCalculator(const Data& data): _data{data} {}

        //! @brief Virtual destructor avoids double free due to polymorphism
        virtual ~AbstractPathCalculator() {}

        /*! @brief Pure abstract method to evaluate trajectory path for a given path specifier, overridden in concrete classes
            @param pathSpec Path specifier of type Type::PathSpec, defines the shape of the path to be computed
            @param methods Sequence calculation methods selected, see Type::Methods
            @return The path evaluated according to a given computational model
        */
        Type::Path eval(const Type::PathSpec& pathSpec, bool fromOrigin) const;

        /*! @brief Pure abstract point calculator, starting from an origin point and a segment specifier
            @param prev Origin (previous) point
            @param spec Segment specifier
            @return The computed point
        */
        virtual Type::Point next(const Type::Point& prev, const Type::Spec& spec) const = 0;

    protected:
        //! @brief Save computation algorithm input data aggregate  
        Data _data;
};


/*! @class FlatEarthPathCalculator
    @brief Concrete path calculator class applying flat earth model
*/
class FlatEarthPathCalculator final
: public AbstractPathCalculator {
    public:
        //! @brief Disable default constructor 
        FlatEarthPathCalculator()=delete;

        //! @brief Construct from input data aggregate
        FlatEarthPathCalculator(const Data& data):
        AbstractPathCalculator(data) {}

        /*! @brief Evaluate point coordinates starting from an origin point and a specifier using flat earth model
            @param prev Origin (previous) point
            @param spec Segment specifier
            @return The computed point
        */
        Type::Point next(const Type::Point& prev, const Type::Spec& spec) const override;
};


/*! @class SphericalEarthPathCalculator
    @brief Concrete path calculator class applying spherical earth model
*/
class SphericalEarthPathCalculator final
: public AbstractPathCalculator {
    public:
        //! @brief Disable default constructor 
        SphericalEarthPathCalculator()=delete;

        //! @brief Construct from input data aggregate
        SphericalEarthPathCalculator(const Data& data):
        AbstractPathCalculator(data) {}

        /*! @brief Evaluate point coordinates starting from an origin point and a specifier using spherical earth model
            @param prev Origin (previous) point
            @param spec Segment specifier
            @return The computed point
        */
        Type::Point next(const Type::Point& prev, const Type::Spec& spec) const override;
};


/*! @class WGS84PathCalculator
    @brief Concrete path calculator class applying WGS84 earth model
*/
class WGS84PathCalculator final
: public AbstractPathCalculator {
    public:
        //! @brief Disable default constructor 
        WGS84PathCalculator()=delete;

        //! @brief Construct from input data aggregate
        WGS84PathCalculator(const Data& data):
        AbstractPathCalculator(data) {}

        /*! @brief Evaluate point coordinates starting from an origin point and a specifier using flat earth model
            @param prev Origin (previous) point
            @param spec Segment specifier
            @return The computed point
        */
        Type::Point next(const Type::Point& prev, const Type::Spec& spec) const override;
};

#endif  // _ACADEMY_CALCULATOR_HPP_
