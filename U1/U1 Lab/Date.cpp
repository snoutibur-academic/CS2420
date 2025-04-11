#include "Date.h"

string Date::intToMonth(int input) {
    string monthStr;
    switch (input) {
        case 1:
            monthStr =  "Jan";
            break;
        case 2:
            monthStr =  "Feb";
            break;
        case 3:
            monthStr =  "Mar";
            break;
        case 4:
            monthStr =  "Apr";
            break;
        case 5:
            monthStr =  "May";
            break;
        case 6:
            monthStr =  "Jun";
            break;
        case 7:
            monthStr =  "Jul";
            break;
        case 8:
            monthStr = "Aug";
            break;
        case 9:
            monthStr =  "Sep";
            break;
        case 10:
            monthStr =  "Oct";
            break;
        case 11:
            monthStr =  "Nov";
            break;
        case 12:
            monthStr =  "Dec";
            break;
        default:
            monthStr =  "???";
            break;
    }

    return monthStr;
}

// GETTERS
int Date::getYear() {
    return year;
}
int Date::getMonth() {
    return month;
}
int Date::getDay() {
    return day;
}

// CONVERSIONS
string Date::toString() {
    stringstream ss;

    ss << intToMonth(month) << " " << day << ", " << year;
    return ss.str();
}

// Overloaded Operators
ostream& operator<<(ostream &out, Date &d) {
    out << d.toString();
    return out;
}

