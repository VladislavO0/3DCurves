#include "../include/curves.h"

int main()
{
    std::srand(time(NULL));

    Trigonometry trigon;

    std::vector<std::shared_ptr<ICurves>> RandObj;
    massRandObject(RandObj, trigon);// Populating container of random objects with random parameters
    printMassObject(&RandObj); // Printing coordinates of points and derivatives of all curves in the container at  t=PI/4 by default
    std::vector<std::shared_ptr<ICurves>> OnlyCircles;
    massOnlyCircles(RandObj, OnlyCircles);// Populating container only circles from the first container
    //printMassObject(&OnlyCircles); // Printing coordinates container with only circles
    AscendSortOnlyCircles(OnlyCircles); // Sorting container with only circles
    printMassObject(&OnlyCircles); // Printing sorted container
    totalRadiiSum(OnlyCircles); // Calculating the total sum of radii of all curves
	std::cin.get();
    return 0;
}
