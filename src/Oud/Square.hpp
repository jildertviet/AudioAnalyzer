//
//  Square.hpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#ifndef Square_hpp
#define Square_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Event.hpp"

class Square: public Event{
public:
    Square();
    Square(float millisTime, ofVec2f loc, ofVec2f size, ofColor color, int *numEvents, Event* *array);
    void display();
};
#endif /* Square_hpp */
