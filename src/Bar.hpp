//
//  Bar.hpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 25-01-16.
//
//

#ifndef Bar_hpp
#define Bar_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Event.hpp"

class Bar: public Event{
public:
    Bar(){
        type="Bar";
        returnType();
        colors[0] = ofColor::white;
        loc = ofVec2f(ofGetWindowWidth()*ofNoise(ofGetElapsedTimeMillis()), 0);
        size = ofVec2f(100, ofGetWindowHeight());
    };
    Bar(int *numEvents, Event* *array);
    void display();
    void update();
};
#endif /* Bar_hpp */
