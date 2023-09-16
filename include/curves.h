/// curves.h - contains declarations of curves class and functions

#ifndef CURVE_H
#define CURVE_H

#include "constants.h"

#include <cassert>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <memory>
#include <ctime>
#include <iostream>
#include <typeinfo>

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Different structs for data storage
////////////////////////////////////////////////////////////////////////////////////////////////////////

/// The struct for storing a table of values of trigonometric functions from 0 to 2PI
struct Trigonometry
{
    std::map <double,double> sins;
    std::map <double,double> coss;
    Trigonometry();
};

/// The struct for storing a point
struct Point
{
    double x;
    double y;
    double z;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition of the base Curves class
////////////////////////////////////////////////////////////////////////////////////////////////////////

class ICurves
{    
public:
    //Search for the approximate value of the "double" key in the map container
    static Point findElements(std::map<double, Point> &mapp, double pos = constants::PI/4);

    /// accessors

    // return a 3D points for t parameter
    virtual Point getPoint(double t = constants::PI/4) = 0;
    //return first derivative for t parameter
    virtual Point getDerivative(double t = constants::PI/4) = 0;
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

class Circles: public ICurves
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
    Point getPoint(double t = constants::PI/4) override;
    std::vector<double> getRadius() override   { return std::vector<double> {m_rad1};  }
    Point getDerivative(double t = constants::PI/4) override;
    void getName() override;
    virtual ~Circles() {};
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition of the Ellipse class
////////////////////////////////////////////////////////////////////////////////////////////////////////

class Ellipse: public Circles
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

class Helixes: public Circles
{
//private
    double m_step; // spiral step in 2*PI
    double h = m_step / (2*constants::PI); // discrete value of the variable step
public:
    Helixes(Trigonometry &trigon, double rad, double step);
    void getName() override;
    virtual ~Helixes() {};
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Other of the program functions
////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Printing coordinate of point and derivative at t=PI/4 by default
void printPoint(ICurves &cur, double pos = constants::PI/4);

/// Printing coordinates of points and derivatives of all curves in the container at  t=PI/4 by default
void printMassObject(std::vector<std::shared_ptr<ICurves>> *vec, double pos = constants::PI/4);

/// Creating container of random objects with random parameters
void massRandObject(std::vector<std::shared_ptr<ICurves>> &vec, Trigonometry &trigon);

///Populating container only circles from the first container
//(firstContainer, secondContainer)
void massOnlyCircles(std::vector<std::shared_ptr<ICurves>> &first,std::vector<std::shared_ptr<ICurves>> &second );

/// Sorting container with only сircles in the ascending of circles’ radii
void AscendSortOnlyCircles(std::vector<std::shared_ptr<ICurves>> &second);

/// Computation of  the total sum of radii of all circles
void  totalRadiiSum(std::vector<std::shared_ptr<ICurves>> &circ);


#endif
