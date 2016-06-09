//
//  Event.cpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#include "Event.hpp"

Event::Event(){
    cout<<"Made an event of type: ";
    startTime = ofGetElapsedTimeMillis();
    first = last = false;
    next = previous = nullptr;
    id = 0;
    setColors(5);
    envelope = new Envelope(0.001, 100, 100);
    envelope->gate = true;
    screencenter = ofVec2f(ofGetWindowWidth(), ofGetWindowHeight());
}

void Event::update(){
    if(active && ofGetElapsedTimeMillis() > endTime){
        cout << "Event (id:"<<id<<") has passed!" << endl;
        delete this;
    }
}

void Event::setColors(int numColors){
    colors = new ofColor[numColors];
    colors[0] = ofColor(231,71,72);
    colors[1] = ofColor(230,132,53);
    colors[2] = ofColor(243,207,34);
    colors[3] = ofColor(237,229,116);
    colors[4] = ofColor(225,245,196);
    this->numColors = numColors;
}

void Event::setEnvelope(int attack, int sustain, int release){
    int totalTime = attack + sustain + release;
    setEndTime(totalTime);
    
    envelope->attackTime = attack; envelope->sustainTime = sustain; envelope->releaseTime = release;
}