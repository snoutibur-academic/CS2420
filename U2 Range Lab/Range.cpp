//
// Created by doge on 1/15/25.
//

// #include "Range.h"
//
// template<class Type>
// int Range<Type>::length() {
//     int current = start;
//     int length = 0;
//
//     while (current < end) {
//         if (current+=step > end) {
//             break;
//         } else {
//             current += step;
//             length++;
//         }
//     }
//     return length;
// }
//
// template <class Type>
// Type Range<Type>::sum() {
//     Type sum = 0;
//     int legnth = this.length();
//
//     for (int i = 0; i <= legnth; i++) {
//         sum+=step;
//     }
//     return sum;
// }
//
// template<class Type>
// Type Range<Type>::average() {
//     return sum() / length();
// }
//
// template<class Type>
// Type Range<Type>::min() {
//     return start;
// }
//
// template<class Type>
// Type Range<Type>::max() {
//     return end;
// }
//
// template<class Type>
// std::ostream& operator << (std::ostream &out, const Range<Type> &r) {
//     Type current = r.start;
//     out << current;
//
//     int length = r.length();
//
//     for (int i = 0; i <= length; i++) {
//         current+= r.step;
//         out << current;
//     }
//     return out;
// }