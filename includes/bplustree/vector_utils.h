#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>

using namespace std;

// Overload stream insertion operator for vector
template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list) {
    for (const auto& item : list) {
        outs << item << " ";
    }
    return outs;
}

// Overload += operator to add an element to a vector
template <typename T, typename U>
vector<T>& operator += (vector<T>& list, const U& addme) {
    list.push_back(addme);
    return list;
}

// Overload += operator to append another vector
template <typename T>
vector<T>& operator +=(vector<T>& list, const vector<T>& append_me) {
    list.insert(list.end(), append_me.begin(), append_me.end());
    return list;
}



#endif // VECTOR_UTILS_H
