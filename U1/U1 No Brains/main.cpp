#include <iostream>
#include "Point.h"

using namespace std;

int main()
{
    Point<double> p1;
    cout << "Point 1" << endl;
    cin >> p1;

    Point<double> p2;
    cout << "Point 2" << endl;
    cin >> p2;

    Point<double> p3 = p1 + p2;
    cout << p1 << " + " << p2 << " = " << p3 << endl;


    p1 += p2;
    cout << "Increment p1 by p2 to get " << p1 << endl;
    return 0;
}
