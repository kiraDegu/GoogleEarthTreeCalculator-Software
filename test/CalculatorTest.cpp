#include "TypeTraits.hpp"
#include "Data.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include "Calculators.hpp"

// Initialize pathSpec with distance and bearing pairs
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

Data data {{0.0, 0.0, 5000.0}, 0.0, 0.0, 5000.0};


int main() {

    FlatEarthPathCalculator flatEarthCalculator(data);

    // Evaluate the path using the FlatEarthPathCalculator
    Type::Path result = flatEarthCalculator.eval(pathSpec);

    // Print the resulting path points
    for (const auto& point : result) {
        std::cout << "Latitude: " << point[0] << ", Longitude: " << point[1] << std::endl;
    }

    return 0;
}
