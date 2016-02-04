//
//  Visualizer.hpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#ifndef Visualizer_hpp
#define Visualizer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Square.hpp"
#include "Bar.hpp"
#include "Noise.hpp"
#include "Event.hpp"


class Visualizer{
public:
    Visualizer();
    void update();
    void display();
    void (Visualizer::*actionFunc)(void);
    bool action = false;
    void setFunction(int name);
    void doAction(){action=true;};
    
    void setColors();
    ofColor colors[10];
    int numColors=0;
    
    
    void displayRandomQuarter();
    void makeVerticalBar();
    void horizontalNoise(); void verticalNoise();
    void drawMask(string type);
    void displayVerticalBar(ofColor color = ofColor::red);
    
    void testFunc(){cout<<"TestFunc"<<endl;}
    
    Event* startEvent;
    Event* events[100];
    int numEvents=0;
    
    ofImage circle; bool mask=false;
};

#endif /* Visualizer_hpp */
