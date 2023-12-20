#ifndef VECTOR_UTILITIES_H
#define VECTOR_UTILITIES_H

#include<vector>
#include<algorithm>

using namespace std;

// Function to find the intersection of two vectors
template <typename T>
void vector_union(vector<T>& v1, vector<T>& v2, vector<T>& result){
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
}

// Function to find the intersection of two vectors
template <typename T>
void vector_intersection(vector<T>& v1, vector<T>& v2, vector<T>& result){
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
}

#endif // VECTOR_UTILITIES_H
