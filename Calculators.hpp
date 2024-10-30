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
            @return The path evaluated according to a given computational model
        */
        virtual Type::Path eval(const Type::PathSpec& pathSpec) const = 0;

    protected:
        //! @brief Save computation algorithm input data aggregate  
        Data _data;

        /*! @brief Private method to initialize trajectory path for a given path specifier
            @param pathSpec Path specifier of type Type::PathSpec, defines the shape of the path to be computed
            @return The initialized path 
        */
        Type::Path _initOutput(const Type::PathSpec&) const;
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

        /*! @brief Flat earth model override of the path evaluation method
            @param pathSpec Path specifier of type Type::PathSpec, defines the shape of the path to be computed
            @return The path evaluated according to flat earth model
        */
        Type::Path eval(const Type::PathSpec&) const override;
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

        /*! @brief Spherical earth model override of the path evaluation method
            @param pathSpec Path specifier of type Type::PathSpec, defines the shape of the path to be computed
            @return The path evaluated according to flat spherical model
        */
        Type::Path eval(const Type::PathSpec&) const override;
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

        /*! @brief WGS84 earth model override of the path evaluation method
            @param pathSpec Path specifier of type Type::PathSpec, defines the shape of the path to be computed
            @return The path evaluated according to WGS84 earth model
        */
        Type::Path eval(const Type::PathSpec&) const override;
};

#endif  // _ACADEMY_CALCULATOR_HPP_
