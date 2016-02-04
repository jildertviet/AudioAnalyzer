//
//  Noise.hpp
//  voorPaul
//
//  Created by Jildert Viet on 27-01-16.
//
//

#ifndef Noise_hpp
#define Noise_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Event.hpp"

class Noise: public Event{
public:
    Noise(){ type = "Noise"; returnType();}
    Noise(float duration, string mode = "horizontal");
    void display();
    void horizontalNoise(int size); void verticalNoise(int size);
    void generateSeed();
    int lineWidth = 2;
private:
    void specificFunction(){
        float val = envelope->process();
        cout <<val<<endl;
        color.a = maxAlpha * val;
    };
};
#endif /* Noise_hpp */
