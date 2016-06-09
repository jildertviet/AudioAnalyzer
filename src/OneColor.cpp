//
//  OneColor.cpp
//  Paul
//
//  Created by Jildert Viet on 08-02-16.
//
//

#include "OneColor.hpp"
//--------------------------------------------------------------
OneColor::OneColor(){
    
}
//--------------------------------------------------------------
OneColor::OneColor(ofColor color1, ofColor color2, ofColor color3){
    colors[0] = color1;
    colors[2] = color2;
    colors[1] = color3;
}
//--------------------------------------------------------------
void OneColor::display(){
    // Blend three colors
    ofSetColor(colors[0]);
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofSetColor(colors[1]);
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofSetColor(colors[2]);
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}
//--------------------------------------------------------------
//void OneColor::update(){
////    morph(0.1);
//}

//--------------------------------------------------------------
void OneColor::morph(float v1, float v2, float v3, float amount){
    // Find a way to morp this
    // newVale between 0. and 1.
    if(v1>1)    v1 = 1;
    if(v2>1)    v2 = 1;
    if(v3>1)    v3 = 1;
    alphas[0] = alphas[0]   -   ((alphas[0]-(ofMap(v1, 0.0, 1.0, 20, 127)))/amount);
    alphas[1] = alphas[1]   -   ((alphas[1]-(ofMap(v2, 0.0, 1.0, 20, 127)))/amount);
    alphas[2] = alphas[2]   -   ((alphas[2]-(ofMap(v3, 0.0, 1.0, 0, 200)))/amount);
    for(int i=0; i<3; i++){
        colors[i].a = alphas[i];
    }
}