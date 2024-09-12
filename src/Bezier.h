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
#include "Math.h"

using namespace std;

class Bezier
{
public:
    float Z[4][4];
        float prepZ[4][4] = {
        {0, 0, 0, 0.0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
        };
    // int prepZ[4][4] = {
    //     {1, 0, 0, 1},
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {1, 0, 0, 1}
    //     };
    // float prepZ[4][4] = {
    //     {0, 0, 0, 0},
    //     {0, -1, 0, 0},
    //     {0, 1, 1, 0},
    //     {0, 0, 0, 0}
    //     };
    // int prepZ[4][4] = {
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0}
    //     };
    /*
        prepZ visualizes control points
        Z - control points:

        z03 z13 z23 z33
        z02 z12 z22 z32
        z01 z11 z21 z31
        z00 z10 z20 z30
    */

    void genZ()
    {
        for (int k = 0; k < 4; k++)
            Z[k][0] = prepZ[3][k];
        for (int k = 0; k < 4; k++)
            Z[k][1] = prepZ[2][k];
        for (int k = 0; k < 4; k++)
            Z[k][2] = prepZ[1][k];
        for (int k = 0; k < 4; k++)
            Z[k][3] = prepZ[0][k];
    }

    Bezier()
    {
        genZ();
    }

    float B(int i, int n, float argument) // bezierCoefficient
    {
        return Math::binomial(n, i) * Math::power(argument, i) * Math::power(1.0f - argument, n - i);
    }

    float z(float x, float y)
    {
        float value = 0;
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
            {
                value += (Z[i][j] * B(i, 3, x) * B(j, 3, y));
            }

        // cout << "x, y, value:" << x << " " << y << " " << value << endl;
        return value;
    }

    glm::vec3 tangentX(float u, float v)
    {
        bool debug = false;
        float debug_x = 0.75;
        float debug_y = 0.75;

        int n = 3, m = 3;

        float value = 0;

        for (int i = 0; i <= n - 1; i++)
            for (int j = 0; j <= m; j++)
            {
                //                                 B(0, 2, 0.75) 
                value += (Z[i + 1][j] - Z[i][j]) * B(i, n - 1, u) * B(j, m, v);
                if (debug && u == debug_x and v == debug_y)
                {
                    cout << endl << endl;
                    cout << "x, y, i, j, Z[i + 1][j], Z[i][j], B(i, n - 1, u), B(j, m, v) " << u << " " << v << " " << i << " " << j << " " << Z[i + 1][j] << " " << Z[i][j] << " " << B(i, n - 1, u) << " " << B(j, m, v)<< endl;
                }
            }

        value *= n;
        // return glm::vec3(1, 0, value);
        return glm::vec3(1, value, 0);
    }

    glm::vec3 tangentY(float u, float v)
    {
        int n = 3, m = 3;

        float value = 0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m - 1; j++)
                value += (Z[i][j + 1] - Z[i][j]) * B(i, n, u) * B(j, m - 1, v);

        value *= m;
        return glm::vec3(0, value, 1);
    }

    glm::vec3 normal(float u, float v)
    {
        return glm::cross(tangentX(u, v), tangentY(u, v));
    }
};