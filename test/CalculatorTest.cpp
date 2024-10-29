#include "TypeTraits.hpp"
#include "Data.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include "Calculators.hpp"


// Dati per FlatEarthPathCalculator::eval()
Type::PathSpec pathSpec = {
    {1.0, 0.0},
    {1.0, 90.0},
    {std::sqrt(2.0), 45.0},
    {std::sqrt(5.0), 63.435},
    {std::sqrt(5.0), 26.565},
    {2.0 * std::sqrt(2.0), 45.0},
    {std::sqrt(12.5), 8.13},
    {std::sqrt(5.0), -26.565},
    {2.0, 0.0},
    {std::sqrt(2.0), -45.0},
    {1.0, 0.0},
    {0.0, 0.0}
};
Data data {{45.0, 9.0, 5000.0}, 20.0, 0.0, 5000.0};

// Dati per computeFlat()
const double PI = 3.141592653589793;
const double NM_TO_LL = 0.01662976;
struct Data2 {
    std::array<double, 2> origin; // Latitudine e longitudine dell'origine
    double dist;
    double heading;
    int model; // Modello di Terra: 1 = Flat, 2 = Spherical, 3 = WGS84
    std::array<std::array<double, 12>, 2> points; // Punti calcolati (Lat e Long)
    double heightMSL = 5000.0; // Altezza media sul livello del mare
};


// funzione di Marco Torelli per il confronto
void computeFlat(Data2 &data, const std::array<double, 12> &thetaPlus, const std::array<double, 12> &distPlus) {
    data.points[0][0] = data.origin[0];
    data.points[1][0] = data.origin[1];
    for (int i = 1; i < 12; ++i) {
        data.points[0][i] = data.dist * distPlus[i] * std::cos((data.heading + thetaPlus[i]) * PI / 180.0) * NM_TO_LL + data.points[0][0];
        data.points[1][i] = data.dist * distPlus[i] * std::sin((data.heading + thetaPlus[i]) * PI / 180.0) * NM_TO_LL / std::cos(data.points[0][0] * PI / 180.0) + data.points[1][0];
    }
}


int main() {

    FlatEarthPathCalculator flatEarthCalculator(data);
    Type::Path result = flatEarthCalculator.eval(pathSpec);

    for (const auto& point : result) {
        std::cout << "Latitude: " << point.lati << ", Longitude: " << point.longi << std::endl;
    }


    std::cout << "Marco torelli's implementation" << std::endl;

    std::array<double, 12> thetaPlus = {0.0, 90.0, 45.0, 63.435, 26.565, 45.0, 8.13, -26.565, 0.0, -45.0, 0.0, 0.0};
    std::array<double, 12> distPlus = {1.0, 1.0, std::sqrt(2.0), std::sqrt(5.0), std::sqrt(5.0), 2.0 * std::sqrt(2.0), std::sqrt(12.5), std::sqrt(5.0), 2.0, std::sqrt(2.0), 1.0, 0.0};
    std::array<std::array<double, 12>, 2> points;
    Data2 data2 {{45.0, 9.0}, 20.0, 0.0, 1, points, 5000.0};
    computeFlat(data2, thetaPlus, distPlus);

  
    std::array<double, 12> lat2 = data2.points[0];
    std::array<double, 12> lon2 = data2.points[1];

    for (size_t i = 0; i < 12; i++)
    {
        std::cout << "Latitude: " << lat2[i] << ", Longitude: " << lon2[i] << std::endl;
    }

    return 0;
}
