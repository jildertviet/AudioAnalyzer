//
//  Meter.hpp
//  Audio_met_Osc
//
//  Created by Jildert Viet on 27-01-16.
//
//

#ifndef Meter_hpp
#define Meter_hpp

#include <stdio.h>
#include "ofMain.h"
#include "OnsetDetector.hpp"
//#include "ofxOsc.h"

class Meter{
public:
    Meter();
    Meter(float *value, string name, ofVec2f loc){
        this->loc = loc;
        size = ofVec2f(50,200);
        this->value = value; this->name = name;
    }
    ofVec2f loc, size, thresholdBarLoc, thresholdBarSize;
    ofColor thresholdBarColor = ofColor::gray;
    ofColor meterColor = ofColor::white;
    ofColor valueColor = ofColor(0,200);
    float *value;
    string name;
    virtual void specificFunction();
    
    
    void displayThresholdControl();
    bool isMouseOnMeter(int x, int y);
    void setThreshold(float value);
    float threshold=0.5;
    
    //    ofxOscSender sender;
    void sendOnsetMessage();
    
    bool checkIfAboveThreshold(); bool aboveThreshold;
    void setThresholdBool();
    bool trigger;

    OnsetDetector onsetDetector;
    
    void display(){
        specificFunction();
        setThresholdBool();
        
        ofSetColor(255);
        ofDrawBitmapString(name, ofVec2f(loc.x, loc.y+size.y+10));
        displayMeter();
        displayThresholdControl();

//        cout << *value << endl;
    }
    void displayMeter(){
        ofSetColor(meterColor);
        
        ofDrawRectangle(loc.x, loc.y, size.x, size.y);
        ofVec2f newLoc = ofVec2f(loc.x, loc.y+size.y-(size.y * (*value)));
        
        ofVec2f newSize = ofVec2f(size.x, size.y * (*value));
        ofSetColor(valueColor);
        ofDrawRectangle(loc.x, newLoc.y, size.x, newSize.y);
        ofSetColor(ofColor::red);
        ofDrawLine(loc.x, newLoc.y, loc.x+size.x, newLoc.y);
    }
    
    float interpolate(float v1, float v2, float division){
        return v1   -   ((v1-v2)/division);
    }
};
#endif /* Meter_hpp */
