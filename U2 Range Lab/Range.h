//
// Created by doge on 1/15/25.
//

#ifndef RANGE_H
#define RANGE_H
#include <iostream>

template <class Type>
class Range;

template <class Type>
std::ostream& operator<<(std::ostream &, const Range<Type> &r);

template <class Type>
class Range {
public:
    Range(Type min, Type max) : start(min), end(max), step(1) {};
    Range(Type min, Type max, Type step) : start(min), step(step), end(max) {};

    int length() const;
    Type sum();
    Type average();
    Type min();
    Type max();

    friend std::ostream& operator << <> (std::ostream &out, const Range<Type> &r);

private:
    Type start;
    Type end;
    Type step;
};


template<class Type>
int Range<Type>::length() const {
    int length = 0;

    for (Type i = start; step > 0 ? i <= end : i >= end; i+=step) {
        length++;
    }

    return length;
}

template <class Type>
Type Range<Type>::sum() {
    Type sum = 0;

    for (Type i = start; step > 0 ? i <= end : i >= end; i+=step) {
        sum+=i;
    }

    return sum;
}

template<class Type>
Type Range<Type>::average() {
    return sum() / length();
}

template<class Type>
Type Range<Type>::min() {
    Type min;
    if (start < end) {
        min = end;
    } else {
        min = start;
    }

    for (Type i = start; step > 0 ? i <= end : i >= end; i+=step) {
        if (min > i) {
            min = i;
        }
    }

    return min;
}

template<class Type>
Type Range<Type>::max() {
    Type max;
    if (start > end) {
        max = end;
    } else {
        max = start;
    }

    for (Type i = start; step > 0 ? i <= end : i >= end; i+=step) {
        if (max < i) {
            max = i;
        }
    }

    return max;
}

template<class Type>
std::ostream& operator << (std::ostream &out, const Range<Type> &r) {
    Type current = r.start;
    out << current;

    for (Type i = current; r.step > 0 ? i <= r.end : i >= r.end; i+=r.step) {
        out << i;
    }

    return out;
}

#endif //RANGE_H