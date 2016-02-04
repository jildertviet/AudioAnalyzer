//
//  Meter.cpp
//  Audio_met_Osc
//
//  Created by Jildert Viet on 27-01-16.
//
//

#include "Meter.hpp"

Meter::Meter(){
//    sender.setup("sender", 5555);
}

void Meter::displayThresholdControl(){
    thresholdBarLoc = this->loc+ofVec2f(size.x,0);
    thresholdBarSize = size; thresholdBarSize.x = thresholdBarSize.x/5.;
    
    ofSetColor(thresholdBarColor);
    
    ofDrawRectangle(thresholdBarLoc.x, thresholdBarLoc.y, thresholdBarSize.x, thresholdBarSize.y);
    
    ofSetColor(ofColor::orangeRed);
    float y = loc.y+size.y-(size.y*threshold);
    float x = loc.x+size.x;
    ofDrawLine(x, y, x+(size.x/5.), y);
}

bool Meter::isMouseOnMeter(int x, int y){
    if(x<thresholdBarLoc.x+thresholdBarSize.x&&x>thresholdBarLoc.x&&y>thresholdBarLoc.y&&y<thresholdBarLoc.y+thresholdBarSize.y){
        cout<<"CLICK"<<endl;
        float value = 1.f-(y-thresholdBarLoc.y)/thresholdBarSize.y;
        cout << value<<endl;
        setThreshold(value);
    }
}

void Meter::setThreshold(float value){
    threshold = value;
}

void Meter::specificFunction(){

}

void Meter::sendOnsetMessage(){ // ofXOsc addon aan project :0
//    ofxOscMessage message;
//    message.addStringArg("/fromOF");
//    message.addInt32Arg(1);
//    sender.sendMessage(message);
}

void Meter::setThresholdBool(){
    if(checkIfAboveThreshold()){
        if(!aboveThreshold){
            // ONSET FUNCTION
            trigger = true;
            valueColor = ofColor(0,230);
        }
        trigger = false;
        aboveThreshold = true;
    } else{
        if(aboveThreshold){
            // OFFSET-func
            valueColor = ofColor(0,200);
        }
        aboveThreshold = false;
    }
}

bool Meter::checkIfAboveThreshold(){
    if(*value>threshold){
        return true;
    } else{
        return false;
    }
}

