#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

Vector2D::Vector2D() : x(0), y(0)
{
}
Vector2D::Vector2D(double init_x, double init_y) : x(init_x), y(init_y)
{
}

void Vector2D::initVector(double init_x, double init_y)
{
    this->x = init_x;
    this->y = init_y;
}

double Vector2D::getMagnitude() const
{
    double magnitude = std::sqrt(this->x * this->x + this->y * this->y);
    return magnitude;
}

Vector2D Vector2D::operator+(const Vector2D &rhs) const
{
    double added_x = this->x + rhs.x;
    double added_y = this->y + rhs.y;
    Vector2D added_vector;
    added_vector.initVector(added_x, added_y);
    return added_vector;
}

Vector2D &Vector2D::operator+=(const Vector2D &rhs)
{
    double added_x = this->x + rhs.x;
    double added_y = this->y + rhs.y;
    this->initVector(added_x, added_y);
    return *this;
}

double Vector2D::dot(const Vector2D &rhs) const
{
    return this->x * rhs.x + this->y * rhs.y;
}

void Vector2D::print() const
{
    printf("<%.2f, %.2f>", this->x, this->y);
}