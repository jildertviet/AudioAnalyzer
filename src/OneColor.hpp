//
//  OneColor.hpp
//  Paul
//
//  Created by Jildert Viet on 08-02-16.
//
//  Colors setten met different alpha, zodat ze blenden. 

#ifndef OneColor_hpp
#define OneColor_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Event.hpp"

class OneColor: public Event{
public:
    OneColor();
    OneColor(ofColor color1=ofColor::red, ofColor color2=ofColor::yellow, ofColor color3=ofColor::orange);
//    void update();
    void display();
    void morph(float v1, float v2, float v3, float amount);
    float alphas[3] = {255, 255, 255};
};
#endif /* OneColor_hpp */
