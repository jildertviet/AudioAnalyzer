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

Square::Square(float millisTime, ofVec2f loc, ofVec2f size, ofColor color = ofColor::gray){
    type = "Square"; returnType();
    setEndTime(millisTime);
    this->loc = loc; this->size = size; this->colors[0] = color; active=true;
}

void Square::display(){
    ofSetColor(colors[0]);
    ofDrawRectangle(loc.x, loc.y, size.x, size.y);
}