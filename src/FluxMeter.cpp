//
//  Flux.cpp
//  Audio_met_Osc
//
//  Created by Jildert Viet on 27-01-16.
//
//

#include "FluxMeter.hpp"

FluxMeter::FluxMeter(){
    
}

FluxMeter::FluxMeter(string name, ofVec2f loc, ofxFloatSlider *LP){
    buffer = new float[bufferSize];
    this->name = name; this->loc = loc; this->LP = LP;
    size = ofVec2f(50,200);
//    OSCToggleLoc = ofVec2f(loc.x, loc.y+size.y+15);
    loadXML();
    guiSetup();
    sender.setup("Sender", 8888);
}