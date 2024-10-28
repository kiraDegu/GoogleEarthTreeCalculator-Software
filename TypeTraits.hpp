#ifndef _ACADEMY_TYPETRAITS_HPP
#define _ACADEMY_TYPETRAITS_HPP

#include <array>
#include <vector>

struct Type {
    using Scalar   = double;
    using Point    = std::array<Scalar, 2>;
    using PathSpec = std::vector<std::pair<Scalar, Scalar>>;
    using Path     = std::vector<Point>;
};

#endif // _ACADEMY_TYPETRAITS_HPP