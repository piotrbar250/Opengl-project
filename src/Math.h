#pragma once
#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "stb_image.h"

using namespace std;

namespace Math
{
    class Point3d
    {
        public:
        float x, y, z;
        Point3d() {}
        Point3d(float x, float y, float z) : x(x), y(y), z(z) {}

        friend Point3d cross(const Point3d& a, const Point3d&b)
        {
            return Point3d(
                a.y*b.z - a.z*b.y,
                a.z*b.x - a.x*b.z,
                a.x*b.y - a.y*b.x
            );
        }
        friend float dot(const Point3d& a, const Point3d&b)
        {
            return a.x* b.x + a.y*b.y + a.z*b.z;
        }

        Point3d operator*(const Point3d&b) const
        {
            return Point3d(
                x * b.x,
                y * b.y,
                z * b.z
            );
        }
        Point3d operator *(float k) const
        {
            return Point3d(
                k*x,
                k*y,
                k*z
            );
        }
        Point3d operator +(const Point3d&b) const
        {
            return Point3d(
                x + b.x,
                y + b.y,
                z + b.z
            );
        }
        Point3d operator -(const Point3d&b) const
        {
            return Point3d(
                x - b.x,
                y - b.y,
                z - b.z
            );
        }

        bool operator ==(const Point3d& b) const
        {
            return x == b.x && y == b.y && z == b.z;
        }

        float norm() const
        {
            return sqrt(x*x + y*y + z*z);
        }
        Point3d normalized() const
        {
            float _norm = norm();
            return Point3d(
                x / _norm,
                y / _norm,
                z / _norm
            );
        }
        
        Point3d operator *(const float m[3][3]) const
        {
            return Point3d(m[0][0], m[1][0], m[2][0]) * x + 
                   Point3d(m[0][1], m[1][1], m[2][1]) * y +
                   Point3d(m[0][2], m[1][2], m[2][2]) * z;
        }

        friend ostream& operator <<(ostream& os, const Point3d p)
        {
            return os << p.x << " " << p.y << " " << p.z << endl;
        }
    };

    int binomialCoeff(int n, int k)
    {
        int res = 1;

        if (k > n - k)
            k = n - k;

        for (int i = 0; i < k; ++i)
        {
            res *= (n - i);
            res /= (i + 1);
        }
        return res;
    }

    int binomial_2[3] = {1, 2, 1}; 
    int binomial_3[4] = {1, 3, 3, 1};

    int binomial(int n, int k)
    {
        if (n == 2 && k >= 0 && k < 3)
            return binomial_2[k];
        else if (n == 3 && k >= 0 && k < 4)
            return binomial_3[k];
        else
            return 0;
    }

    float power(float a, int b)
    {
        // 0 <= b <= 3
        if (b < 0 || b > 3)
        {
            cout << "Exponent out of allowed range (0-3)." << endl;
            exit(1);
            return -1;
        }

        switch (b)
        {
        case 0:
            return 1;
        case 1:
            return a;
        case 2:
            return a * a;
        case 3:
            return a * a * a;
        default:
        {
            cout << "error" << endl;
            return -1;
        }
        }
    }

};