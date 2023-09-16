// curves.cpp : realization of the curves class and functions

#include "curves.h"
#include "constants.h"
#include <omp.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Realization of the Circles class
////////////////////////////////////////////////////////////////////////////////////////////////////////

DLL_EXPORT Circles::Circles(Trigonometry &trigon, double rad) // Circles ctor
    {
        assert(rad >= 0 && "radius must be positive");
        m_rad1 = rad;
        for(auto it1 =  trigon.coss.cbegin(), it2 =  trigon.sins.cbegin(); it1 != trigon.coss.cend(); ++it1,++it2)
        {
            XYZ[it1->first].x = m_rad1*it1->second;
            XYZder[it1->first].x = -(m_rad1*it2->second);
            XYZ[it1->first].y = m_rad1*it2->second;
            XYZder[it1->first].y = m_rad1*it1->second;
            XYZ[it1->first].z = 0;
            XYZder[it1->first].z = 0;
        }
    }
Point DLL_EXPORT Circles::getPoint(double t )
{
    return findElements(XYZ,t);
}
Point DLL_EXPORT Circles::getDerivative(double t)
{
    return findElements(XYZder,t);
}
void DLL_EXPORT Circles::getName(){
    std::cout << "Circles: rad = " << m_rad1 << "\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Realization of the Ellipse class
////////////////////////////////////////////////////////////////////////////////////////////////////////

DLL_EXPORT Ellipse::Ellipse(Trigonometry &trigon, double rad1, double rad2)
    : Circles(trigon, rad1) // Ellipse ctor
    {
        assert(rad2  >= 0 && "radius must be positive");
        m_rad2 = rad2;
        for(auto it1 =  trigon.coss.cbegin(), it2 =  trigon.sins.cbegin(); it1 != trigon.coss.cend(); ++it1,++it2)
        {
            XYZ[it1->first].y = m_rad2*it2->second;
            XYZder[it1->first].y = m_rad2*it1->second;
            XYZ[it1->first].z = 0;
            XYZder[it1->first].z = 0;
        }
    }
void DLL_EXPORT Ellipse::getName(){
    std::cout << "Ellipse: rad_1 = "<< m_rad1 << "; rad_2 = " << m_rad2 <<"\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Realization of the Helixes class
////////////////////////////////////////////////////////////////////////////////////////////////////////

DLL_EXPORT Helixes::Helixes(Trigonometry &trigon, double rad, double step)
    : Circles(trigon, rad), m_step(step) // circles ctor
    {
        for(auto it1 =  trigon.coss.cbegin(), it2 =  trigon.sins.cbegin(); it1 != trigon.coss.cend(); ++it1,++it2)
        {
            XYZ[it1->first].z = it1->first*h;
            XYZder[it1->first].z = h;
        }
    }
void DLL_EXPORT Helixes::getName(){
    std::cout << "Helixes: rad = " << m_rad1 << "; step = " << m_step <<"\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Other of the program functions
////////////////////////////////////////////////////////////////////////////////////////////////////////

DLL_EXPORT Trigonometry::Trigonometry()
{
    for(size_t i = 0; i < constants::res; ++i)
    {
        sins[i*constants::d] = std::sin(i*constants::d);
        coss[i*constants::d] = std::cos(i*constants::d);
    }
}

Point DLL_EXPORT ICurves::findElements(std::map<double, Point> &mapp, double pos)
{
    std::map<double, Point>::iterator low, prev;
    low = mapp.lower_bound(pos);
    if (low == mapp.end())
        return std::prev(low)->second;
    if (low == mapp.begin())
        return low->second;
    prev = std::prev(low);
    if ((pos - prev->first) < (low->first - pos))
        return prev->second;
    else
        return low->second;
}

void DLL_EXPORT printPoint(ICurves &cur, double pos)
{
    Point point_a;
    Point deriv_a;
    point_a = cur.getPoint(pos);
    deriv_a = cur.getDerivative(pos);
    std::cout <<"\tPoint(t = "<<pos<<") ("<< point_a.x << ", " << point_a.y <<", "<<  point_a.z << ")\n";
    std::cout << "\tfirstDerivative(t = "<< pos <<") ("<< deriv_a.x << ", " << deriv_a.y <<", "<<  deriv_a.z << ")\n";
}

void DLL_EXPORT printMassObject(std::vector<std::shared_ptr<ICurves>> *vec, double pos)
{
    for(auto &item : *vec)
    {
        item->getName();
        printPoint(*item, pos);
    }
    std::cout << "===============================================================" <<'\n';
}

void DLL_EXPORT massRandObject(std::vector<std::shared_ptr<ICurves>> &vec, Trigonometry &trigon, long long sizeMR)
{
    vec.reserve(sizeMR);
    for(size_t i = 0; i < sizeMR; ++i)
    {
        double rad1 = static_cast<double>(rand()*(100-1)) / static_cast<double>(RAND_MAX + 1);// interval from 1 to 100 from rad1
        double num = static_cast<double>(rand()*(100-1)) / static_cast<double>(RAND_MAX + 1);// interval from 1 to 100 from rad2 or step

              switch(rand() % 3)
        {
            case 0:
            //using move semantics(converts lval to rval)
                vec.push_back(std::move(std::make_shared<Circles>(trigon, rad1)));
                break;
            case 1:
                vec.push_back(std::move(std::make_shared<Ellipse>(trigon, rad1, num)));
                break;
            case 2:
                vec.push_back(std::move(std::make_shared<Helixes>(trigon, rad1, num)));
                break;
        }
    }
}

void DLL_EXPORT massOnlyCircles(std::vector<std::shared_ptr<ICurves>> &first,std::vector<std::shared_ptr<ICurves>> &second)
{
    for(auto &item: first)
    {
        if(typeid(*item).name() == typeid(Circles).name())
            second.push_back(item);
    }
}

void DLL_EXPORT AscendSortOnlyCircles(std::vector<std::shared_ptr<ICurves>> &second)
{
    std::sort(second.begin(), second.end(),
        [](const auto &a, const auto &b)
        {
            return a->getRadius()[0] < b->getRadius()[0];
        }
    );
}

void DLL_EXPORT totalRadiiSum(std::vector<std::shared_ptr<ICurves>> &circ)
{
    double totalSum = 0;
    for(auto &item: circ)
    {
        totalSum += item->getRadius()[0];
    }
    std::cout << "Total sum of all circles radii with serial computations = " << totalSum <<"\n";
}

void DLL_EXPORT totalRadiiSumOpenMP(std::vector<std::shared_ptr<ICurves>> &circ, const long sizeCirc)
{
    double totalSum = 0;
   // running parallel threads; the container is declared shared;
   // each thread has its own local total Sum; reduction - sums of local sums
    #pragma omp parallel shared(circ) reduction (+: totalSum)
    {
        #pragma omp for //distribution of cycle indexes by threads
        for(long i = 0; i < sizeCirc; ++i)
        {
            totalSum += circ[i]->getRadius()[0];
        }
    }
    std::cout << "Total sum of all circles radii with parallel computations = " << totalSum <<"\n";
}

