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

Event::~Event(){
    *numEventsPtr--;
    if(!next){
        previous->next = nullptr;
    } else{
        previous->next = next;
        next->previous = previous;
    }
    cout << "Event deleted!" << endl;
    delete envelope;
}

void Event::update(){
    if(active && ofGetElapsedTimeMillis() > endTime){
        cout << "Event (id:"<<id<<") has passed!" << endl;
        ownDtor();
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

void Event::checkBorders(){
    if(loc.x < 0){
        loc.x = 0;
        direction.x *= -1;
    }
    if((loc.x+size.x) > ofGetWindowWidth()){
        loc.x = ofGetWindowWidth()-size.x;
        direction.x *= -1;
    }
    if((loc.y+size.y) > ofGetWindowHeight()){
        loc.y = ofGetWindowHeight()-size.y;
        direction.y *= -1;

    }
    if(loc.y < 0){
        loc.y = 0;
        direction.y *= -1;
    }
}

