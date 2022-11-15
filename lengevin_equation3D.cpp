// Markus Buchholz

//// g++ 3D_line_for_RRT.cpp -o t -I/usr/include/python3.8 -lpython3.8
#include <iostream>
#include <tuple>
#include <vector>
#include <math.h>
#include <random>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

//----------- system dynamic parameters --------------------

float m = 1.0f;
float G = 1.0f;
float r = 1.0f;
float dt = 0.01f;
float R = 100.0f;

float noise()
{

    std::default_random_engine generator;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> distribution(0.0, 1.0);

    return distribution(gen);
}

//-----------------------------------------------------------
// vx
float function1(float x, float y, float z, float vx, float vy, float vz)
{

    return vx;
}

//-----------------------------------------------------------
// vy
float function2(float x, float y, float z, float vx, float vy, float vz)
{

    return vy;
}


//-----------------------------------------------------------
// vy
float function3(float x, float y, float z, float vx, float vy, float vz)
{

    return vz;
}


//-----------------------------------------------------------
// vx_dot
float function4(float x, float y, float z, float vx, float vy, float vz)
{


    return -(G / m) * vx + R * noise();
}

//-----------------------------------------------------------
// vy_dot
float function5(float x, float y, float z, float vx, float vy, float vz)
{


    return -(G / m) * vy + R * noise();
}

//-----------------------------------------------------------
// vy_dot
float function6(float x, float y, float z, float vx, float vy, float vz)
{

    return -(G / m) * vz + R * noise();
}

//-----------------------------------------------------------




std::tuple<std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>> methodRuneKuttaLangevin()
{

    std::vector<float> diffEq1;
    std::vector<float> diffEq2;
    std::vector<float> diffEq3;
    std::vector<float> diffEq4;
    std::vector<float> diffEq5;
    std::vector<float> diffEq6;

    std::vector<float> time;

    // init values
    float x1 = 0.0; // x0
    float x2 = 0.0; //y0
    float x3 = 0.0; //z0
    float x4 = 10.0; // vx
    float x5 = 10.0; // vy
    float x6 = 10.0; // vz
    float t = 0.0;   // init time

    diffEq1.push_back(x1);
    diffEq2.push_back(x2);
    diffEq3.push_back(x3);
    diffEq4.push_back(x4);
    diffEq5.push_back(x5);
    diffEq6.push_back(x6);
    time.push_back(t);

    for (int ii = 0; ii < 10000; ii++)
    {
        t = t + dt;
        float k11 = function1(x1, x2, x3, x4, x5, x6);
        float k12 = function2(x1, x2, x3, x4, x5, x6);
        float k13 = function3(x1, x2, x3, x4, x5, x6);
        float k14 = function4(x1, x2, x3, x4, x5, x6);
        float k15 = function5(x1, x2, x3, x4, x5, x6);
        float k16 = function6(x1, x2, x3, x4, x5, x6);

        float k21 = function1(x1 + dt / 2 * k11, x2 + dt / 2 * k12, x3 + dt / 2 * k13, x4 + dt / 2 * k14+ dt / 2, x5 + dt / 2 * k15+ dt / 2, x6 + dt / 2 * k16+ dt / 2 );
        float k22 = function2(x1 + dt / 2 * k11, x2 + dt / 2 * k12, x3 + dt / 2 * k13, x4 + dt / 2 * k14+ dt / 2, x5 + dt / 2 * k15+ dt / 2, x6 + dt / 2 * k16+ dt / 2 );
        float k23 = function3(x1 + dt / 2 * k11, x2 + dt / 2 * k12, x3 + dt / 2 * k13, x4 + dt / 2 * k14+ dt / 2, x5 + dt / 2 * k15+ dt / 2, x6 + dt / 2 * k16+ dt / 2 );
        float k24 = function4(x1 + dt / 2 * k11, x2 + dt / 2 * k12, x3 + dt / 2 * k13, x4 + dt / 2 * k14+ dt / 2, x5 + dt / 2 * k15+ dt / 2, x6 + dt / 2 * k16+ dt / 2 );
        float k25 = function4(x1 + dt / 2 * k11, x2 + dt / 2 * k12, x3 + dt / 2 * k13, x4 + dt / 2 * k14+ dt / 2, x5 + dt / 2 * k15+ dt / 2, x6 + dt / 2 * k16+ dt / 2 );
        float k26 = function4(x1 + dt / 2 * k11, x2 + dt / 2 * k12, x3 + dt / 2 * k13, x4 + dt / 2 * k14+ dt / 2, x5 + dt / 2 * k15+ dt / 2, x6 + dt / 2 * k16+ dt / 2 );

        float k31 = function1(x1 + dt / 2 * k21, x2 + dt / 2 * k22, x3 + dt / 2 * k23, x4 + dt / 2 * k24, x5 + dt / 2 * k25, x6 + dt / 2 * k26);
        float k32 = function2(x1 + dt / 2 * k21, x2 + dt / 2 * k22, x3 + dt / 2 * k23, x4 + dt / 2 * k24, x5 + dt / 2 * k25, x6 + dt / 2 * k26);
        float k33 = function3(x1 + dt / 2 * k21, x2 + dt / 2 * k22, x3 + dt / 2 * k23, x4 + dt / 2 * k24, x5 + dt / 2 * k25, x6 + dt / 2 * k26);
        float k34 = function4(x1 + dt / 2 * k21, x2 + dt / 2 * k22, x3 + dt / 2 * k23, x4 + dt / 2 * k24, x5 + dt / 2 * k25, x6 + dt / 2 * k26);
        float k35 = function4(x1 + dt / 2 * k21, x2 + dt / 2 * k22, x3 + dt / 2 * k23, x4 + dt / 2 * k24, x5 + dt / 2 * k25, x6 + dt / 2 * k26);
        float k36 = function4(x1 + dt / 2 * k21, x2 + dt / 2 * k22, x3 + dt / 2 * k23, x4 + dt / 2 * k24, x5 + dt / 2 * k25, x6 + dt / 2 * k26);

        float k41 = function1(x1 + dt * k31, x2 + dt * k32, x3 + dt * k33, x4 + dt * k34, x5 + dt * k35, x6 + dt * k36);
        float k42 = function2(x1 + dt * k31, x2 + dt * k32, x3 + dt * k33, x4 + dt * k34, x5 + dt * k35, x6 + dt * k36);
        float k43 = function3(x1 + dt * k31, x2 + dt * k32, x3 + dt * k33, x4 + dt * k34, x5 + dt * k35, x6 + dt * k36);
        float k44 = function4(x1 + dt * k31, x2 + dt * k32, x3 + dt * k33, x4 + dt * k34, x5 + dt * k35, x6 + dt * k36);
        float k45 = function4(x1 + dt * k31, x2 + dt * k32, x3 + dt * k33, x4 + dt * k34, x5 + dt * k35, x6 + dt * k36);
        float k46 = function4(x1 + dt * k31, x2 + dt * k32, x3 + dt * k33, x4 + dt * k34, x5 + dt * k35, x6 + dt * k36);


        x1 = x1 + dt / 6.0 * (k11 + 2 * k21 + 2 * k31 + k41);
        x2 = x2 + dt / 6.0 * (k12 + 2 * k22 + 2 * k32 + k42);
        x3 = x3 + dt / 6.0 * (k13 + 2 * k23 + 2 * k33 + k43);
        x4 = x4 + dt / 6.0 * (k14 + 2 * k24 + 2 * k34 + k44);
        x5 = x5 + dt / 6.0 * (k15 + 2 * k25 + 2 * k36 + k45);
        x6 = x6 + dt / 6.0 * (k16 + 2 * k26 + 2 * k36 + k46);

        diffEq1.push_back(x1);
        diffEq2.push_back(x2);
        diffEq3.push_back(x3);
        diffEq4.push_back(x4);
        diffEq5.push_back(x5);
        diffEq6.push_back(x6);
        time.push_back(t);
    }

    return std::make_tuple(diffEq1, diffEq2, diffEq3, diffEq4, diffEq5, diffEq6, time);
}

//---------------------------------------------------------------------------------------------------------

void plot2D(std::tuple<std::vector<float>, std::vector<float>> data1)
{

    std::vector<float> xX1 = std::get<0>(data1);
    std::vector<float> yY1 = std::get<1>(data1);

    plt::scatter(xX1, yY1);
    plt::xlabel("X");
    plt::ylabel("Y");
    plt::show();
}

void plot3D(std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> system)
{
    std::vector<float> xX = std::get<0>(system);
    std::vector<float> yY = std::get<1>(system);
    std::vector<float> zZ = std::get<2>(system);

    plt::plot3(xX, yY, zZ);
    plt::xlabel("x");
    plt::ylabel("y");
    plt::set_zlabel("z");
    plt::show();
}

//---------------------------------------------------------------
int main()
{

    std::tuple<std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>,std::vector<float>, std::vector<float>, std::vector<float>> particle = methodRuneKuttaLangevin();

    std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> XYZ = std::make_tuple(std::get<0>(particle), std::get<1>(particle), std::get<2>(particle));
    //std::tuple<std::vector<float>, std::vector<float>> vx = std::make_tuple(std::get<4>(particle), std::get<2>(particle));

    plot3D(XYZ);
   // plot2D(vx);
}
