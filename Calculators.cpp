#include <cmath>
#include "Calculators.hpp"
#include "utilities.hpp"


// Common output initializer
Type::Path&& AbstractPathCalculator::_initOutput(const Type::PathSpec& pathSpec) const {
    Type::Path out;
    out.reserve(pathSpec.size()+1);
    out.emplace_back(_data.p0);

    return std::move(out);
}

// Flat earth model path calculator implementation
Type::Path FlatEarthPathCalculator::eval(const Type::PathSpec& pathSpec) const {
    Type::Path out{this->_initOutput(pathSpec)};

    static const Type::Scalar NM_TO_LL = 0.01662976;

    for (size_t i = 1; i < pathSpec.size(); ++i) {
        Type::Point p_next = { 
            _data.p0.lati  + (_data.d * pathSpec[i].first) * cos(math::degreeToRadian(_data.th + pathSpec[i].second))*NM_TO_LL, 
            _data.p0.longi + (_data.d * pathSpec[i].first) * sin(math::degreeToRadian(_data.th + pathSpec[i].second))*NM_TO_LL / cos(math::degreeToRadian(_data.p0.lati))
        }; 
        out.emplace_back(p_next);  
    }

    return out;
}

// Spherical earth model path calculator implementation
Type::Path SphericalEarthPathCalculator::eval(const Type::PathSpec& pathSpec) const {
    Type::Path out{this->_initOutput(pathSpec)};

    for (size_t i = 1; i < pathSpec.size(); ++i) {
        double hav_rad = _data.d * pathSpec[i].first / physics::EARTH_RADIUS_NM;
        double theta_rad = math::degreeToRadian((_data.th + pathSpec[i].second));
        double lat_rad = math::degreeToRadian(_data.p0.lati) ;

        Type::Point nextPonit;

        nextPonit.lati = math::radianToDegree((sin(lat_rad) * cos(hav_rad) + cos(lat_rad) * sin(hav_rad) * cos(theta_rad))) ;
        nextPonit.longi = _data.p0.lati + math::radianToDegree((sin(theta_rad) * sin(hav_rad) * cos(lat_rad),
                                            cos(hav_rad) - sin(lat_rad) * sin(math::degreeToRadian(nextPonit.lati))));
        out.emplace_back(nextPonit);
    }

    return out;
}

// WGS84 model path calculator implementation
Type::Path WGS84PathCalculator::eval(const Type::PathSpec& pathSpec) const {
    Type::Path out{this->_initOutput(pathSpec)};

    Type::Point p_current = _data.p0;

    for (const auto& step : pathSpec) {
        double distance = _data.d * step.first; // Distance in nautical miles
        double bearing = math::degreeToRadian(_data.th + step.second); // Convert bearing to radians

        // Vincenty's formulae constants
        const double a = 6378137.0; // Semi-major axis of the Earth (meters)
        const double f = 1 / 298.257223563; // Flattening
        const double b = (1 - f) * a; // Semi-minor axis

        // 	reduced latitude (latitude on the auxiliary sphere)
        const double U1 = atan((1 - f) * tan(math::degreeToRadian(p_current.lati)));
        const double U2 = atan((1 - f) * tan(math::degreeToRadian(p_current.lati))); // Note: should be the new latitude after calculation
        const double L = math::degreeToRadian(p_current.longi) - bearing; // Difference in longitude

        double sinU1 = sin(U1);
        double cosU1 = cos(U1);
        double sinU2 = sin(U2);
        double cosU2 = cos(U2);

        double lambda = L; // Initialize
        double lambdaP;
        double sinLambda, cosLambda, sinSigma, cosSigma, cosSqAlpha, cos2SigmaM, C, sigma;

        // Iteration to solve for lambda
        do {
            sinLambda = sin(lambda);
            cosLambda = cos(lambda);
            sinSigma = sqrt((cosU2 * sinLambda) * (cosU2 * sinLambda) +
                            (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda) *
                            (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda));

            if (sinSigma == 0) return out; // co-incident points

            cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda;
            sigma = atan2(sinSigma, cosSigma);

            double sinAlpha = cosU1 * cosU2 * sinLambda;
            cosSqAlpha = 1 - sinAlpha * sinAlpha;
            cos2SigmaM = cosU2 * cosU1 - 2 * sinU1 * sinU2 * cosLambda;

            if (cos2SigmaM == 0) cos2SigmaM = 0; // Equatorial line

            C = f / 16 * cosSqAlpha * (4 + f * (4 - 3 * cosSqAlpha));

            lambdaP = lambda;
            lambda = L + (1 - C) * f * sinAlpha *
                     (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM)));

        } while (fabs(lambda - lambdaP) > 1e-12); // Convergence check

        // Calculate new latitude and longitude
        double uSq = cosSqAlpha * (a * a - b * b) / (b * b);
        double A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
        double B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));

        double deltaSigma = B * sinSigma * (cos2SigmaM + B / 4 * (cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM) -
                          B / 6 * cos2SigmaM * (-3 + 4 * sinSigma * sinSigma) *
                          (-3 + 4 * cos2SigmaM * cos2SigmaM)));

        double s = b * A * (sigma - deltaSigma); // Distance

        // Calculate new latitude and longitude
        double lat2 = U2 + (cosU2 * sinLambda) / (cosU1 * cosU2) * (distance / (a * (1 - f)));
        double lon2 = math::degreeToRadian(p_current.longi) + (1 / cosU1) * (distance / (a * (1 - f))) * sinLambda;

        // Update current point
        p_current.lati = math::radianToDegree(lat2);
        p_current.longi = math::radianToDegree(lon2);

        out.emplace_back(p_current); // Add the new point to the path
    }

    return out;
}
