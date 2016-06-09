//
//  Mirror.h
//  Batobe_met_MIDI
//
//  Created by Jildert Viet on 27-05-15.
//
//

#ifndef Mirror_h
#define Mirror_h

#include <iostream>
#include "ofMain.h"
#include "Event.hpp"

class Mirror: public Event{
public:
    Mirror();
    Mirror(ofVec2f size_, ofVec2f loc_);
    ~Mirror();
    ofVec2f size;
    ofVec2f location;
    ofVec2f view;
    
    void display();
    void specificFunction();
//    void update();
    ofImage image;
    ofTexture texture;
    float ySpeed;
    int angle;
    void moveTriangle();
    Boolean moveBackwards;
    
    void reSpawn();
    void displayView();
    
    bool bDisplayMirror = true;
    bool draw_view = false;
    bool draw_sides = false;
    
    void moveUp();
    Boolean move_up;
    float speed;
};
#endif /* defined(Mirror_h) */
