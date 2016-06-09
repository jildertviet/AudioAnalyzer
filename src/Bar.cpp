//
//  Bar.cpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 25-01-16.
//
//

#include "Bar.hpp"
//
//Bar::Bar(){
//    this->numEvents = numEvents; this->array = array; type = "Bar"; returnType();
//    
//    colors[0] = ofColor::white;
//    loc = ofVec2f(ofGetWindowWidth()*ofNoise(ofGetElapsedTimeMillis()), 0);
//    size = ofVec2f(100, ofGetWindowHeight());
//    seed = ofGetElapsedTimef();
//}

void Bar::display(){
    ofSetColor(colors[0]);
    ofDrawRectangle(loc.x, loc.y, size.x/2., size.y);
    ofDrawRectangle(loc.x-size.x/2., loc.y, size.x/2., size.y);
}

void Bar::update(){
    speed = 0.5;
    float noiseValue = ofNoise(ofGetElapsedTimef()/ofMap(speed, 0., 1., 30, 1));
    loc.x = ofGetWindowWidth()*noiseValue;
}