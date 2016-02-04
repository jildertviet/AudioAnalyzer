//
//  Square.cpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#include "Square.hpp"

Square::Square(){
    
}

Square::Square(float millisTime, ofVec2f loc, ofVec2f size, ofColor color = ofColor::gray, int *numEvents = nullptr, Event* *array = nullptr){
    type = "Square"; returnType();
    endTime = startTime + millisTime;
    this->loc = loc; this->size = size; this->color = color; this->numEvents = numEvents; this->array = array; this->id = (*numEvents);
    addNumEvents();
    cout << "New numEvents: " << *(this->numEvents) << endl;
}

void Square::display(){
    ofSetColor(color);
    ofDrawRectangle(loc.x, loc.y, size.x, size.y);
}