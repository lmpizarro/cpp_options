#include "signals.h"
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

Signal::Signal(const float a, const int s) {
    size = s;
    data = std::make_unique<float[]>(size);
    for (int i=0; i < size; i++ ){
        data[i] = a;
    }
}

Signal::Signal(const Signal& s){
    size = s.size;
    data = std::make_unique<float[]>(size);
    for (int i=0; i < size; i++ ){
        data[i] = s.data[i];
    }
}

Signal Signal::operator+ (const Signal& s){
    Signal sum(s);
    for (int i=0; i < s.size; i++){
        sum.data[i] = this->data[i] + s.data[i];
    }
    return sum;
}

float & Signal::operator[](int i){
    if (i >= size){
        cout << "Index out of bounds " << size <<endl;
        return data[0];
    }
    return data[i];
}


Uniform Uniform::operator+ (const Uniform& s){
    Uniform sum(s);
    for (int i=0; i < s.size; i++){
        sum.data[i] = this->data[i] + s.data[i];
    }
    return sum;
}

Sin::Sin(const float cc, const float amp, const float cycles, const int s):Signal(cc, s){
    for (int i = 0; i < size; i++){
        data[i] += amp*sin(2*M_PI*cycles*i/size);
    }
}

Normal::Normal(const float lo, const float sc, const int s):Signal(0, s){
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(lo, sc);
    for (int i = 0; i < size; i++){
        data[i] += distribution(generator);
    }
}

Uniform::Uniform(const float lo, const float up, const int s):Signal(0, s){
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(lo, up);
    for (int i = 0; i < size; i++){
        data[i] += distribution(generator);
    }
}


ostream & operator<<(ostream& os, Signal& s){
    os << "[ " ;
    for (int i = 0; i < s.size; i++ ){
        os << s.data[i] << " ";
    }
    os << "]" << endl;
    return os;
};

