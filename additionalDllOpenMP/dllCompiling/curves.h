/// curves.h - contains declarations of curves class and functions

#ifndef CURVE_H
#define CURVE_H

#include <cassert>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <memory>
#include <ctime>
#include <iostream>
#include <typeinfo>
#include <omp.h>

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

namespace
{
    const double PI = 3.14159265;
    const double d = PI / 360; //step for T value
    const double T = 2*PI; // max value t parameter
    const size_t res = static_cast<size_t> (T / d); // for reserve values in vector
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Different structs for data storage
////////////////////////////////////////////////////////////////////////////////////////////////////////

/// The struct for storing a table of values of trigonometric functions from 0 to 2PI
struct DLL_EXPORT Trigonometry
{
    std::map <double,double> sins;
    std::map <double,double> coss;
    Trigonometry();
};

/// The struct for storing a point
struct DLL_EXPORT Point
{
    double x;
    double y;
    double z;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition of the base Curves class
////////////////////////////////////////////////////////////////////////////////////////////////////////

class DLL_EXPORT ICurves
{
public:
    //Search for the approximate value of the "double" key in the map container
    static Point findElements(std::map<double, Point> &mapp, double pos = PI/4);

    /// accessors

    // return a 3D points for t parameter
    virtual Point getPoint(double t = PI/4) = 0;
    //return first derivative for t parameter
    virtual Point getDerivative(double t = PI/4) = 0;
    //return the name of the curve and the defined parameter
    virtual void getName() = 0;
    //returns the radius of the curve
    virtual std::vector<double> getRadius() = 0;
    // virtual dtor for using dtor of derived classes
    virtual ~ICurves() {};
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition of the Circles class
////////////////////////////////////////////////////////////////////////////////////////////////////////

class DLL_EXPORT Circles: public ICurves
{
//private
protected:
    double m_rad1;
    //map containers for x,y,z points for t parameters
    std::map<double, Point> XYZ;
    //map containers for x,y,z first derivative for t parameters
    std::map<double, Point>  XYZder;
public:
    Circles(Trigonometry &trigon, double rad);
    Point getPoint(double t = PI/4) override;
    std::vector<double> getRadius() override   { return std::vector<double> {m_rad1};  }
    Point getDerivative(double t = PI/4) override;
    void getName() override;
    virtual ~Circles() {};
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition of the Ellipse class
////////////////////////////////////////////////////////////////////////////////////////////////////////

class DLL_EXPORT Ellipse: public Circles
{
//private
    double m_rad2;
public:
    Ellipse(Trigonometry &trigon, double rad1, double rad2);
    void getName() override;
    std::vector<double> getRadius() override   { return std::vector<double> {m_rad1, m_rad2};  }
    virtual ~Ellipse() {};
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition of the Helixes class
////////////////////////////////////////////////////////////////////////////////////////////////////////

class DLL_EXPORT Helixes: public Circles
{
//private
    double m_step; // spiral step in 2*PI
    double h = m_step / (2*PI); // discrete value of the variable step
public:
    Helixes(Trigonometry &trigon, double rad, double step);
    void getName() override;
    virtual ~Helixes() {};
};

#ifdef __cplusplus
extern "C"
{
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Other of the program functions
////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Printing coordinate of point and derivative at t=PI/4 by default
void DLL_EXPORT printPoint(ICurves &cur, double pos = PI/4);

/// Printing coordinates of points and derivatives of all curves in the container at  t=PI/4 by default
void DLL_EXPORT printMassObject(std::vector<std::shared_ptr<ICurves>> *vec, double pos = PI/4);

/// Creating container of random objects with random parameters
/// (container, trigonometric table, container size random from 3 to 20 by default )
void DLL_EXPORT massRandObject(std::vector<std::shared_ptr<ICurves>> &vec, Trigonometry &trigon, long long sizeMR = 3 + (rand() % (20)) );

///Populating container only circles from the first container
//(firstContainer, secondContainer)
void DLL_EXPORT massOnlyCircles(std::vector<std::shared_ptr<ICurves>> &first,std::vector<std::shared_ptr<ICurves>> &second );

/// Sorting container with only сircles in the ascending of circles’ radii
void DLL_EXPORT AscendSortOnlyCircles(std::vector<std::shared_ptr<ICurves>> &second);

/// Computation of  the total sum of radii of all circles
void DLL_EXPORT totalRadiiSum(std::vector<std::shared_ptr<ICurves>> &circ);

/// Computation of the total sum of radii of all circles with using OpenMP library
void DLL_EXPORT totalRadiiSumOpenMP(std::vector<std::shared_ptr<ICurves>> &circ, const long sizeCirc);

#ifdef __cplusplus
}
#endif

#endif // CURVE_H
