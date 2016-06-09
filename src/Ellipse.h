//
//  Ellipse.h
//  Batobe_met_MIDI
//
//  Created by Jildert Viet on 07-06-15.
//
//

#ifndef __Batobe_met_MIDI__Ellipse__
#define __Batobe_met_MIDI__Ellipse__

#include <iostream>
#include "ofMain.h"
#include "Wavetable.h"
#include "Event.hpp"

class Ellipse: public Event{
public:
    Ellipse();
    
    float radius;
    float speed;
    ofVec2f size;
    ofVec2f originalSize;
    int alpha;
    int originalAlpha;
    
    float angle;
    void specificFunction();
    
    void display();
    
    Wavetable wavetable;
    Boolean LFO_alpha = false;
    
    void halfTime();
    Boolean oneFrameLarger = false;
    Boolean fill_oneFrame = false;
    
    Boolean smaller = false;
    int smaller_amount = 10;
    void makeSmaller();
    Boolean already_haftime = false;
    
};
#endif /* defined(__Batobe_met_MIDI__Ellipse__) */
