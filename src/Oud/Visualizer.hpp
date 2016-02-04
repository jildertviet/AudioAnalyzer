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
    
    Event* events[100];
    int numEvents=0;
};

#endif /* Visualizer_hpp */
