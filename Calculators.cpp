#include <cmath>
#include "Calculators.hpp"
#include "Utilities.hpp"

Type::Path AbstractPathCalculator::eval(const Type::PathSpec& pathSpec, bool fromOrigin) const {
    // Initialize output
    Type::Path out;
    out.reserve(pathSpec.size()+1);
    out.emplace_back(_data.p0);

    // Evaluate path according to a path method
    if (fromOrigin) { // From Origin
        for (const auto& spec: pathSpec)
            out.emplace_back(this->next(_data.p0, spec));
    } else {          // Point to point
        Type::Point prev = _data.p0;
        for (const auto& spec: pathSpec) {
            prev = this->next(prev, spec);
            out.emplace_back(prev);
        }

    }

    return out;
}

// Flat earth model point calculator implementation
Type::Point FlatEarthPathCalculator::next(const Type::Point& prevPoint, const Type::Spec& spec) const {

    return { 
        prevPoint.lati  + (_data.d * spec.first) * cos(math::degreeToRadian(_data.th + spec.second))*math::NM_TO_LL,
        prevPoint.longi + (_data.d * spec.first) * sin(math::degreeToRadian(_data.th + spec.second))*math::NM_TO_LL / cos(math::degreeToRadian(prevPoint.lati)),
        _data.msl
    }; 
}

// Spherical earth model path calculator implementation
Type::Point SphericalEarthPathCalculator::next(const Type::Point& prevPoint, const Type::Spec& spec) const {

    const Type::Scalar hav_rad{_data.d*spec.first/physics::EARTH_RADIUS_NM};
    const Type::Scalar theta_rad{math::degreeToRadian((_data.th + spec.second))};
    const Type::Scalar lat_rad{math::degreeToRadian(prevPoint.lati)};

    const Type::Scalar newLati{math::radianToDegree(asin(sin(lat_rad)*cos(hav_rad) + cos(lat_rad)*sin(hav_rad)*cos(theta_rad)))};
    Type::Point nextPoint{newLati, 0.0, _data.msl};

    nextPoint.longi = prevPoint.longi + math::radianToDegree(atan2(sin(theta_rad)*sin(hav_rad)*cos(lat_rad) ,
                                                                        cos(hav_rad) - sin(lat_rad)*sin(math::degreeToRadian(newLati))));

    return nextPoint;
}

// WGS84 Wikipedia model path calculator implementation (https://en.wikipedia.org/wiki/Vincenty%27s_formulae)
Type::Point WGS84PathCalculator::next(const Type::Point& prevPoint, const Type::Spec& spec) const {
 
    // Vincenty's formulae constants
    static constexpr Type::Scalar a = 6378137.0; // Semi-major axis of the Earth (meters)
    static constexpr Type::Scalar f = 1 / 298.257223563; // Flattening
    static constexpr Type::Scalar b = (1 - f) * a; // Semi-minor axis
    Type::Point nextPoint;
 
    const Type::Scalar distance = _data.d * spec.first * 1852; // Distance in nautical meters
    const Type::Scalar azimuth = math::degreeToRadian(_data.th + spec.second); // azimuth

    //  reduced latitude (latitude on the auxiliary sphere)
    const Type::Scalar U1 = atan((1 - f) * tan(math::degreeToRadian(prevPoint.lati)));
    const Type::Scalar sigma1 = atan2(tan(U1),cos(azimuth));

    const Type::Scalar sinAlpha = cos(U1)*sin(azimuth);
    const Type::Scalar cos2Alpha = (1-sinAlpha)*(1+sinAlpha);
    const Type::Scalar u2 = cos2Alpha*((a*a - b*b)/(b*b));
    const Type::Scalar A = 1. + ((u2)/16384.) * (4096. + u2*(-768.+u2*(320.-175.*u2)));
    const Type::Scalar B = ((u2)/1024.) * (256. + u2*(-128.+u2*(74.-47.*u2)));
 
    Type::Scalar sigmaNew = distance/(b*A);
    Type::Scalar sigma;
    Type::Scalar twoSigma_m;
    do {
        sigma = sigmaNew;
        twoSigma_m = 2*sigma1 + sigma;
        Type::Scalar deltaSigma = B*sin(sigma)*(cos(twoSigma_m)+(0.25)*B*(cos(sigma)*(-1+2*cos(twoSigma_m)*cos(twoSigma_m))-(1./6.)*B*cos(twoSigma_m)*(-3.+4.*sin(sigma)*sin(sigma))*(-3.+4.*cos(twoSigma_m)*cos(twoSigma_m))));
        sigmaNew = (distance/(b*A)) + deltaSigma;
    } while (std::abs(sigmaNew - sigma) > 1e-13); // Convergence check
 
    nextPoint.lati = math::radianToDegree( atan2(sin(U1)*cos(sigma)+cos(U1)*sin(sigma)*cos(azimuth), (1-f)*sqrt(sin(azimuth)*sin(azimuth)+pow(sin(U1)*sin(sigma)-cos(U1)*cos(sigma)*cos(azimuth),2))) );
    const Type::Scalar lambda = atan2(sin(sigma)*sin(azimuth), cos(U1)*cos(sigma)-sin(U1)*sin(sigma)*cos(azimuth));
    const Type::Scalar C = (f/16.)*cos2Alpha*(4.+f*(4.-3.*cos2Alpha));
    const Type::Scalar L = lambda - (1.-C)*f*sinAlpha*(sigma+C*sin(sigma)*(cos(twoSigma_m)+C*cos(sigma)*(-1.+2.*twoSigma_m*twoSigma_m)));
    nextPoint.longi = math::radianToDegree( _data.p0.longi + L );
    nextPoint.alti = _data.msl;

    return nextPoint;
}