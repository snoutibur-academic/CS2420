#pragma once
#include <iostream>
using namespace std;

template <class Type>
class Point;

template <class Type>
ostream& operator << (ostream &, const Point<Type> &p);

template <class Type>
istream& operator >> (istream &, Point<Type> &p);


template <class Type>
class Point {
private:
    Type x;
    Type y;

public:
    Point(){x=0; y=0;}
    Point(Type x, Type y): x(x), y(y){}

    Point operator + (const Point<Type> &toAdd);
    Point operator += (const Point<Type> &p);

    friend ostream& operator << <> (ostream &, const Point<Type> &p);
    friend istream& operator >> <> (istream &, Point<Type> &p);
};

template <class Type>
inline Point<Type> Point<Type>::operator + (const Point &toAdd) {
    Point<Type> thirdPoint(x + toAdd.x, y + toAdd.y);
    return thirdPoint;
}

template <class Type>
inline Point<Type> Point<Type>::operator += (const Point &toAdd) {
    x += toAdd.x;
    y += toAdd.y;

    return *this;
}

template <class Type>
inline ostream& operator << (ostream &out, const Point<Type> &p) {
    // Displays [4,2]
    out << "[" << p.x << "," << p.y << "]";
    return out;
}

template <class Type>
inline istream& operator >> (istream & in, Point<Type> &p) {
    cout << "Enter x and y coordinates: " << endl;
    in >> p.x >> p.y;
    return in;
}
