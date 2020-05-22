#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>

typedef float real;

namespace rn {

	class vector3f {
	private:

	public:
		real x;
		real y;
		real z;
		// For 4-word speed increase, most computers now-a-days use 4-word memory busses and, as such, just 3-words requires an offset
		real padding;

		// Getters/Setters
		real r() const
		{
			return x;
		}

		real g() const
		{
			return y;
		}

		real b() const
		{
			return z;
		}

		// Constructors
		vector3f(real iX = 0, real iY = 0, real iZ = 0) : x(iX), y(iY), z(iZ) {};

		// Deconstructor
		~vector3f() {}

		// Copy Constructor
		vector3f(const vector3f & v) : x(v.x), y(v.y), z(v.z) {};

		// Operator Overloads
		vector3f& operator=(const vector3f & v)
		{
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		// Add components to eachother and set equal
		void operator+=(const vector3f & v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		// Subtract components from eachother and set equal
		void operator-=(const vector3f & v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		// Multiply vector by scalar and set equal
		void operator*=(const real & s)
		{
			x *= s;
			y *= s;
			z *= s;
		}

		// Divide vector by scalar and set equal
		void operator/=(const real & s)
		{
			real mag = 1.f / s;
			x = x * mag;
			y = y * mag;
			z = z * mag;
		}

		// Vector cross product
		void operator%=(const vector3f & v)
		{
			*this = cross(v);
		}

		// Calculate scalar(dot) product and return result
		real operator*(const vector3f & v) const
		{
			return x*v.x + y*v.y + z*v.z;
		}

		// Divide by scalar and return result
		vector3f operator/(const real s) const
		{
			real mag = 1.f / s;
			return vector3f(x * mag, y * mag, z * mag);
		}

		// Cross vectors and return result
		vector3f operator%(const vector3f & v)
		{
			return cross(v);
		}

		// Returns scalar(dot) product
		vector3f operator*(const real s) const
		{
			return vector3f(s*x, s*y, x*z);
		}

		// Subtract component-wise and return result
		vector3f operator-(const vector3f & v) const
		{
			return vector3f(x - v.x, y - v.y, z - v.z);
		}

		// Add component-wise and return result
		vector3f operator+(const vector3f & v) const
		{
			return vector3f(x + v.x, y + v.y, z + v.z);
		}
		
		// Negate components and return result
		vector3f operator-() const
		{
			return vector3f(-x, -y, -z);
		}

		// Access components array-wise for modification
		real& operator[](int i)
		{
			switch (i)
			{
			case 2:
				return z;
				break;
			case 1:
				return y;
				break;
			case 0:
				return x;
				break;
			default:
				std::cout << "ERROR::VECTOR::OUT OF BOUNDS REQUEST" << std::endl;
			}
		}

		// Access components array-wise for reading
		real operator[](int i) const
		{
			switch (i)
			{
			case 2:
				return z;
				break;
			case 1:
				return y;
				break;
			case 0:
				return x;
				break;
			default:
				std::cout << "ERROR::VECTOR::OUT OF BOUNDS REQUEST" << std::endl;
			}
		}

		// Vector cross product
		vector3f cross(const vector3f & v) const
		{
			return vector3f(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x);
		}

		// Calculate component-wise product and return result
		vector3f componentProduct(const vector3f &v) const
		{
			return vector3f(x*v.x, y*v.y, z*v.z);
		}

		// Calculate the unit vector and return result
		vector3f unit() const
		{
			return vector3f(*this / this->magnitude());
		}

		// Invert components 
		void invert()
		{
			x *= -1;
			y *= -1;
			z *= -1;
		}

		// Normalize the vector and set equal
		void normalize()
		{
			(*this) = (*this).unit();
		}

		// Return magnitude of vector
		real magnitude() const
		{
			return std::sqrtf(x * x + y * y + z * z);
		}

		// Calculate squared magnitude and return result
		real squaredMagnitude()
		{
			return x * x + y * y + z * z;
		}
		
		// Borrowing this straight from Ian Millington
		// Add given vector scaled by float and set equal
		void addScaledVector(const vector3f &v, real t)
		{
			x += v.x * t;
			y += v.y * t;
			z += v.z * t;
		}

		real angleBetween(const vector3f& v) const
		{
			vector3f aU = this->unit();
			vector3f bU = v.unit();
			return acosf(aU*bU);
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const vector3f& v)
	{
		return os << v.x << " " << v.y << " " << v.z;
	}

	inline vector3f operator*(real s, const vector3f& v)
	{
		return vector3f(s*v.x, s*v.y, s*v.z);
	}

	// Or scalar product
	inline real dot(const vector3f& o, const vector3f& v)
	{
		return o.x * v.x + o.y * v.y + o.z * v.z;
	}

	inline vector3f unitVector(vector3f v)
	{
		return v / v.magnitude();
	}

	inline vector3f reflect(const vector3f v, const vector3f n)
	{
		return v - 2.0f * dot(v, n) * n;
	}

	// Returns a viable direction in a unit sphere
	inline vector3f randomInUnitSphere()
	{
		vector3f p;
		do {
			p = 2.0f * vector3f(rand() / (RAND_MAX + 1.0), rand() / (RAND_MAX + 1.0), rand() / (RAND_MAX + 1.0)) - vector3f(1,1,1);
		} while (p.squaredMagnitude() >= 1.0f);
		return p;
	}
}

#endif