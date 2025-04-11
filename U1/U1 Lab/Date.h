#pragma once

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Date {
public:
    // CONSTRUCTORS //
    // one argument constructor
    Date(int year) : year(year), month(1), day(1) {}

    // two argument constructor
    Date(int year, int month) : year(year), month(month), day(1) {}

    // 3 Argument constructor
    Date(int y, int m, int d): year(y), month(m), day(d){}

    // Getters
    string intToMonth(int input);
    int getYear();
    int getMonth();
    int getDay();

    // OPERATIONS
    Date& addMonths(int n){
        year  += (month + n) / 12;
        month = (month + n) % 12;
        return *this;
    }

    Date& addDays(int n) {
        int d = daysToDate() + n;
        int y = year, m = 1;
        while(d > daysInMonth(y, m)){
            d -= daysInMonth(y, m);
            m++;
            if(m > 12){
                m = 1;
                y++;
            }
        }

        day = d;
        month = m;
        year = y;

        return *this;
    }

    static bool isLeapYear(int y) {
        return (y % 4 || (y % 100 == 0 && y % 400)) ? false : true;
    }

    // CONVERSIONS
    // Spit out the date in format Jan 8, 2025
    string toString();

    int daysToDate(){
        int days_in_month[]{31, isLeapYear(year) ? 29 : 28, 31,
                            30, 31, 30, 31, 31, 30, 31, 30, 31};
        int days = 0;
        for(int m = 0; m < month - 1; m++){
            days += days_in_month[m];
        }
        days += day;
        return days;
    }

    // overload operator+
    Date operator+ (int days) {
        Date newDate(year, month, day);
        newDate.addDays(days);
        return newDate;
    }

    // overload operator<<
    friend ostream& operator<<(ostream &out, Date &d);


private:
    int year, month, day;

    static int daysInMonth(int y, int m){
        int days_in_month[]{31, isLeapYear(y) ? 29 : 28, 31,
                            30, 31, 30, 31, 31, 30, 31, 30, 31};
        return days_in_month[m - 1];
    }
};


