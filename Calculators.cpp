#include <cmath>
#include "Calculators.hpp"
#include "Utilities.hpp"

Type::Path AbstractPathCalculator::eval(const Type::PathSpec& pathSpec, bool fromOrigin) const {
    // Initialize output
    Type::Path out;
    out.reserve(pathSpec.size()+1);
    out.emplace_back(_data.p0);

    // Evaluate path according to a path method
    if (fromOrigin) { // Point by Point
        Type::Point prev = _data.p0;
        for (const auto& spec: pathSpec) {
            prev = this->next(prev, spec);
            out.emplace_back(prev);
        }

    } else {          // From Origin
        for (const auto& spec: pathSpec)
            out.emplace_back(this->next(_data.p0, spec));
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


Type::Point WGS84PathCalculator::next(const Type::Point& prevPoint, const Type::Spec& spec) const {
    return {0.,0.,0.};
}

/*
Type::Path WGS84PathCalculator::eval(const Type::PathSpec& pathSpec, const Type::Methods& methods) const {
    const Type::Scalar a = 6378.137 * 0.5399568; // Raggio equatoriale in NM
    const Type::Scalar f = 1.0 / 298.257223563;  // Appiattimento dell'ellissoide
    const Type::Scalar b = (1.0 - f) * a;        // Raggio polare in NM
    const Type::Scalar SigThreshold = 1.0E-9;    // Soglia per la convergenza

    Type::Path out{this->_initOutput(pathSpec)};

    for (size_t i = 1; i < pathSpec.size(); ++i) {
        Type::Scalar lat_rad = math::degreeToRadian(_data.p0.lati);

        Type::Scalar Azm1 = math::degreeToRadian(_data.th + pathSpec[i].second);

        Type::Scalar U1 = atan((1.0 - f) * tan(lat_rad));

        Type::Scalar Sigma1 = atan2(tan(U1), cos(Azm1));

        Type::Scalar Sin_Azm = cos(U1) * sin(Azm1);  

        Type::Scalar u_sqr = (1.0 - Sin_Azm * Sin_Azm) * ((a * a - b * b) / (b * b));

        // Calcolo delle serie di espansione A e B
        Type::Scalar AA = 1.0 + u_sqr / 16384.0 * (4096.0 + u_sqr * (-768.0 + u_sqr * (320.0 - 175.0 * u_sqr)));
        Type::Scalar BB = u_sqr / 1024.0 * (256.0 + u_sqr * (-128.0 + u_sqr * (74.0 - 47.0 * u_sqr)));

        // Iterazione su Sigma per trovare la distanza lungo il percorso
        Type::Scalar Sigma = _data.d * pathSpec[i].first / (b * AA);
        Type::Scalar DeltaSig;
        Type::Scalar SigM2;
        int Iter = 0;
        do {
            SigM2 = 2.0 * Sigma1 + Sigma;
            DeltaSig = BB * sin(Sigma) * (cos(SigM2) + 0.25 * BB * (cos(Sigma) * (-1.0 + 2.0 * cos(SigM2) * cos(SigM2))
                                                                              - (1.0 / 6.0) * BB * cos(SigM2) * (-3.0 + 4.0 * sin(Sigma) * sin(Sigma)) * (-3.0 + 4.0 * cos(SigM2) * cos(SigM2))));
            Sigma += DeltaSig;
            Iter++;
        } while (std::abs(DeltaSig) > SigThreshold && Iter < 1000);

        Type::Point nextPonit;

        // Calcolo della latitudine del punto finale
        nextPonit.lati = math::radianToDegree( atan2(sin(U1) * cos(Sigma) + cos(U1) * sin(Sigma) * cos(Azm1),
                                       (1.0 - f) * sqrt(Sin_Azm * Sin_Azm + pow(sin(U1) * sin(Sigma) - cos(U1) * cos(Sigma) * cos(Azm1), 2))));

        // Calcolo della longitudine del punto finale
        Type::Scalar Lambda = atan2(sin(Sigma) * sin(Azm1),
                                   cos(U1) * cos(Sigma) - sin(U1) * sin(Sigma) * cos(Azm1));

        // Correzione per la longitudine utilizzando la serie di espansione C
        Type::Scalar C = f / 16.0 * (1.0 - Sin_Azm * Sin_Azm) * (4.0 + f * (4.0 - 3.0 * (1.0 - Sin_Azm * Sin_Azm)));
        Type::Scalar L = Lambda - (1.0 - C) * f * Sin_Azm * (Sigma + C * sin(Sigma) * (cos(SigM2) + C * cos(Sigma) * (-1.0 + 2.0 * cos(SigM2) * cos(SigM2))));

        nextPonit.longi = _data.p0.longi + math::radianToDegree(L);

        nextPonit.alti = _data.msl;

        out.emplace_back(nextPonit);
    }
    
    return out;
}
*/
