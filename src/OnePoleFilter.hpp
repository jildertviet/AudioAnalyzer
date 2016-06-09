//
//  OnePoleFilter.hpp
//  Paul
//
//  Created by Jildert Viet on 11-02-16.
//
//

#ifndef OnePoleFilter_hpp
#define OnePoleFilter_hpp

#include <stdio.h>

#include <math.h>

class OnePole {
public:
    OnePole() {a0 = 1.0; b1 = 0.0; z1 = 0.0;};
    OnePole(double Fc) {z1 = 0.0; setFc(Fc);};
    ~OnePole();
    void setFc(double Fc);
    float process(float in);
    
protected:
    double a0, b1, z1;
};

inline void OnePole::setFc(double Fc) {
    b1 = exp(-2.0 * M_PI * Fc);
    a0 = 1.0 - b1;
}

inline float OnePole::process(float in) {
    return z1 = in * a0 + z1 * b1;
}

#endif /* OnePoleFilter_hpp */
