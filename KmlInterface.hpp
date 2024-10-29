#ifndef _ACADEMY_KMLINTERFACE_HPP_
#define _ACADEMY_KMLINTERFACE_HPP_

#include <ostream>
#include <sstream>
#include <iomanip>
#include "TypeTraits.hpp"

class KmlInterface {
    public:
        #ifndef COORDPRECISION
        static constexpr unsigned int CP = 13u;
        #else
        static constexpr unsigned int CP = COORDPRECISION;
        #endif

        static void printPath(std::ostream& os, const Type::Path& path) {
            // Print header
            for (const auto& hline: _headerLines())
                os << hline << std::endl;

            // Print point placemarks
            _addPoints(os, path);

            // Print line path placemark
            _addLines(os, path);

            // End of file
            for (const auto& eline: _endOfFile())
                os << eline << std::endl;
        }

    private:
        static std::array<Type::String, 3> _headerLines() {
            return {
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
                "<kml xmlns=\"http://www.opengis.net/kml/2.2\">",
                "  <Document>"
            };
        }

        static std::array<Type::String, 2> _endOfFile() {
            return {
                "  </Document>",
                "</kml>"
            };
        }

        static Type::String _pointCoordinates(const Type::Point& point) {
            // String stream coordinate to set precision
            std::stringstream coordStream;
            coordStream << std::fixed << std::setprecision(CP) 
                        << point.longi << ", " << point.lati << ", " << point.alti;

            return coordStream.str();
        }

        static void _addPoints(std::ostream& os, const Type::Path& path) {
            static char name{'A'};
            for (const auto& point: path) {

                // Set point placemark
                os << "    <Placemark>" << std::endl;
                os << "      <name> " << name++ << " </name>" << std::endl;
                os << "      <Point>" << std::endl;
                os << "        <coordinates> " << _pointCoordinates(point) 
                   << " </coordinates>" << std::endl;
                os << "      </Point>" << std::endl;
                os << "    </Placemark>" << std::endl;
            }
        }

        static void _addLines(std::ostream& os, const Type::Path& path) {
            os << "    <Placemark>" << std::endl;
            os << "      <name> Computed Path </name>" << std::endl;
            os << "        <coordinates> " << std::endl;
            for (const auto& point: path)
                os << _pointCoordinates(point) << std::endl;
            os << "        </coordinates> " << std::endl;
            os << "    </Placemark>" << std::endl;
        }
};

#endif // _ACADEMY_KMLINTERFACE_HPP_