#ifndef _ACADEMY_KMLINTERFACE_HPP_
#define _ACADEMY_KMLINTERFACE_HPP_

#include <array>
#include <ostream>
#include <sstream>
#include <iomanip>
#include "TypeTraits.hpp"

/*! @class KmlInterface
    @brief Static class for KML file output, the public interface provides a class method for printing a Type::Path into a KML files.
*/
class KmlInterface {
    public:

        #ifndef COORDPRECISION
        //! @brief Coordinate Precision, can be changed at compile time
        static constexpr unsigned int CP = 8u;
        #else
        static constexpr unsigned int CP = COORDPRECISION;
        #endif

        /*! @brief Function to save a point path (a vector of points) into an output stream.
            @param os Output stream
            @param path Vector of points describing a trajectory (see Type::Point)
        */
        static void printPath(
            std::ostream& os, const Type::Path& path,
            const Type::String& docName="Path Name"
        ) {
            // Print header
            for (const auto& hline: _headerLines(docName))
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

        /*! @brief Private method to get KML document header lines
            @return An array of four line strings of type Type::String
        */
        static std::array<Type::String, 5> _headerLines(const Type::String& docName) {
            return {
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
                "<kml xmlns=\"http://www.opengis.net/kml/2.2\"",
                "     xmlns:gx=\"http://www.google.com/kml/ext/2.2\">",
                "  <Document>",
                Type::String("  <name>") + docName + " </name>"
            };
        }

        /*! @brief Private method to get KML document missing lines at the end of file
            @return An array of two line strings of type Type::String
        */
        static std::array<Type::String, 2> _endOfFile() {
            return {
                "  </Document>",
                "</kml>"
            };
        }

        /*! @brief Private method to format a Type::Point into a string suitable for KML point format.
            @return A formatted string for KML point coordinates
        */
        static Type::String _pointCoordinates(const Type::Point& point) {
            // String stream coordinate to set precision
            std::stringstream coordStream;
            coordStream << std::fixed << std::setprecision(CP) 
                        << point.longi << "," << point.lati << "," << point.alti;

            return coordStream.str();
        }

        /*! @brief Private method to print a KML Point list into an output stream
            @param os Output stream
            @param path Vector of points (see Type::Point) describing a trajectory
        */
        static void _addPoints(std::ostream& os, const Type::Path& path) {
            char name{'A'};
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

        /*! @brief Private method to print a KML LineString into an output stream
            @param os Output stream
            @param path Vector of points (see Type::Point) describing a trajectory
        */
        static void _addLines(std::ostream& os, const Type::Path& path) {
            os << "    <Style id=\"redline\">" << std::endl;
            os << "      <PolyStyle>" << std::endl;
            os << "        <color>7f00ff00</color>" << std::endl;
            os << "        <outline>1</outline>" << std::endl;
            os << "      </PolyStyle>" << std::endl;
            os << "      <LineStyle>" << std::endl;
            os << "        <color>ff0000ff</color>" << std::endl;
            os << "        <width>3</width>" << std::endl;
            os << "      </LineStyle>" << std::endl;
            os << "    </Style>" << std::endl;
            os << "    <Placemark>" << std::endl;
            os << "      <name> Computed Path </name>" << std::endl;
            os << "      <styleUrl>#redline</styleUrl>" << std::endl;
            os << "      <Polygon> " << std::endl;
            os << "        <altitudeMode> absolute </altitudeMode>" << std::endl;
            os << "        <extrude> 1 </extrude>" << std::endl;
            os << "        <tassellate> 1 </tassellate>" << std::endl;
            os << "        <outerBoundaryIs>" << std::endl;
            os << "          <LinearRing>" << std::endl;
            os << "            <coordinates> " << std::endl;
            for (const auto& point: path)
                os << "              " << _pointCoordinates(point) << std::endl;
            os << "              " << _pointCoordinates(path.front()) << std::endl;
            os << "            </coordinates> " << std::endl;
            os << "          </LinearRing>" << std::endl;
            os << "        </outerBoundaryIs>" << std::endl;
            os << "      </Polygon> " << std::endl;
            os << "    </Placemark>" << std::endl;
        }
};

#endif // _ACADEMY_KMLINTERFACE_HPP_
