//
//  Particle.h
//  Shapes
//
//  Created by Jildert Viet on 18-02-15.
//
//

#ifndef __Shapes__Particle__
#define __Shapes__Particle__

#include <iostream>
#include "ofMain.h"

class Particle{
public:
    
    Particle(){};
    Particle(ofVec2f *pointer_, int index_, int vorm_index_);
    Particle(ofVec2f destination_, int vorm_index_);
    Particle(ofVec2f *pointer_, int index_, int vorm_index, Boolean start_loc);
    void Init(Boolean loc);
    
    virtual void display();
    virtual void update();
    int checkEdges();
    void changeMode();
    void test();
    void locationIsDestination();
    
    int index; // of the particle in the vorm
    int vorm_index; // the nth vorm, with which the particle is related
    
    float topspeed;
    ofVec2f *destination;
    ofVec2f destination2;
    ofVec2f direction;
    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    
    Boolean letter = false;
    int state;
    Boolean connectable = true;
    Boolean add_noise = false;
    float noise_max;
    int noise_modulo;
    
    ofColor color = ofColor::white;
private:
    Boolean bubbling = false;
    void bubble(int rad, float speed, int offset, ofColor color);
    float r = 1;
};
#endif /* defined(__Shapes__Particle__) */
