/******************************************************************************

Author: Estela Ramirez
Date: 10/17/20
Class: 10C

*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;


vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

//The function returns the index of the min value starting from "index" to the end of the "vector"
template<typename T>
unsigned int min_index(const vector<T> &vals, unsigned int index){
    unsigned int min_index = index;
    T min_value = vals.at(index);
    unsigned int index_copy = index+1;
    
    for (auto it = vals.begin() + index + 1; it != vals.end(); it++){
        if (*it < min_value){
            min_value = *it;
            min_index = index_copy;
        }
        index_copy++;
    }
    return min_index;
}


// comparing stringg . compare()?
template<typename T>
void selection_sort(vector<T> &vals){
    unsigned int index;
   
    for (unsigned int i = 0; i < vals.size()-1; i++){
       
        index = min_index(vals, i+1);
        
        if (vals.at(index) < vals.at(i)){
            T temp = vals.at(i);
            vals.at(i) = vals.at(index);
            vals.at(index) = temp;
        }
    }
}

//The function returns the element located at the index of the vals
template<typename T>
T getElement(vector<T> vals, int index){
    return vals.at(index);
}


int main(){

    vector<int> vec;
    vec.push_back(4);
    vec.push_back(1);
    vec.push_back(-1);
    
    selection_sort(vec);
    return 0;
}