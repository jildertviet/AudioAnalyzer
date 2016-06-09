//
//  Noise.cpp
//  voorPaul
//
//  Created by Jildert Viet on 27-01-16.
//
//

#include "Noise.hpp"

Noise::Noise(float duration, ofColor* colors, string mode){
    this->mode = mode; this->colors = colors;
    type="Noise"; returnType();
    setEndTime(duration);
    active = true;
    generateSeed();
    localColor = randomColor();
    maxAlpha = ofRandom(25,255);
    localColor.a = maxAlpha;
    float attack = 0.001; float release = 800;
    envelope->setShape(attack, duration-attack-release,release);
    envelope->trigger = true;
}

void Noise::display(){
    ofSetLineWidth(lineWidth);
    if(mode=="horizontal")
        horizontalNoise(linesAmount);
    if(mode=="vertical")
        verticalNoise(linesAmount);
}

void Noise::horizontalNoise(int size){
    ofSetColor(localColor);
    for(float i=seed; i<seed+size; i+=2){
        float noiseVal = ofNoise(i);
        ofDrawLine(0, noiseVal*ofGetWindowHeight(), ofGetWindowWidth(), noiseVal*ofGetWindowHeight());
    }
}

void Noise::verticalNoise(int size){
    ofSetColor(localColor);
    for(float i=seed; i<seed+size; i+=2){
        float noiseVal = ofNoise(i);
        ofDrawLine(ofGetWindowWidth()*noiseVal, 0, ofGetWindowWidth()*noiseVal, ofGetWindowHeight());
    }
}

void Noise::generateSeed(){
    seed = ofGetElapsedTimef();
}

