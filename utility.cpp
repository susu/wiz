#include "drawinterface.hpp"

#include <cmath>

Coordinate operator-(const Coordinate& op)
{
  return Coordinate(-op.x, -op.y);
}

Coordinate operator+(const Coordinate& lhs, const Coordinate& rhs)
{
  return Coordinate(lhs.x + rhs.x, lhs.y + rhs.y);
}

Coordinate operator-(const Coordinate& lhs, const Coordinate& rhs)
{
  return lhs + -rhs;
}

Coordinate operator*(const Coordinate& lhs, const Coordinate::CoordType rhs)
{
  return Coordinate(lhs.x * rhs, lhs.y * rhs);
}

Coordinate operator/(const Coordinate& lhs, const Coordinate::CoordType rhs)
{
  return Coordinate(lhs.x / rhs, lhs.y / rhs);
}

Coordinate& Coordinate::operator+=(const Coordinate& rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}

inline Coordinate::CoordType Sqr(Coordinate::CoordType x)
{
  return x*x;
}

Coordinate::CoordType Length(const Coordinate& vektor)
{
  return std::sqrt(Sqr(vektor.x) + Sqr(vektor.y));
}

Coordinate::CoordType Distance(const Coordinate& lhs, const Coordinate& rhs)
{
  return Length(lhs - rhs);
}

