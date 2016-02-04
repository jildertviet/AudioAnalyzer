//
//  Visualizer.cpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#include "Visualizer.hpp"

Visualizer::Visualizer(){
    colors[0] = ofColor::gray; colors[1] = ofColor::white;
    numColors = 2;
    actionFunc = &Visualizer::displayRandomQuarter;
    startEvent = new Event();
    if(mask)
        circle.load("/Users/Jildert/Documents/of_v0.9.0_osx_release/addons/ofxAudioAnalyzer/Paul/bin/data/hoi.png");
    cout<<"Visualizer made"<<endl;
}

void Visualizer::display(){
    if(action){
        (*this.*actionFunc)();
    }
    startEvent->displayMain();
    if(mask)
        drawMask("circle");
}

void Visualizer::update(){
        startEvent->updateMain();
}

void Visualizer::setFunction(int name){
    switch(name){
            case 0:
            actionFunc = &Visualizer::displayRandomQuarter;
            break;
    }
}

void Visualizer::horizontalNoise(){
    startEvent->addEvent(new Noise(100));
}

void Visualizer::verticalNoise(){
    startEvent->addEvent(new Noise(100, "vertical"));
}

void Visualizer::displayRandomQuarter(){
    ofVec2f loc;
    switch ((int)ofRandom(0,4)) {
        case 0:
            loc = ofVec2f(0,0);
            break;
        case 1:
            loc = ofVec2f(ofGetWindowWidth()/2.,0);
            break;
        case 2:
            loc = ofVec2f(0,ofGetWindowHeight()/2.);
            break;
        case 3:
            loc = ofVec2f(ofGetWindowWidth()/2.,ofGetWindowHeight()/2.);
            break;
    }
    startEvent->addEvent(new Square(500+ofRandom(500), loc, ofVec2f(ofGetWindowWidth()/2.,ofGetWindowHeight()/2.), ofColor::red));
    startEvent->getLast()->colors[0] = startEvent->getLast()->randomColor();
    startEvent->getLast()->colors[0].a = 200;
}

void Visualizer::makeVerticalBar(){
    startEvent->addEvent(new Bar());
}

void Visualizer::drawMask(string type){
    ofSetColor(255);
    if(type=="circle")
        circle.draw(0,0,ofGetWindowWidth(),ofGetWindowHeight());
}


void Visualizer::displayVerticalBar(ofColor color){
    startEvent->addEvent(new Square(100, ofVec2f(ofRandomWidth(), 0), ofVec2f(80, ofGetWindowHeight()), ofColor::red));
    startEvent->getLast()->colors[0].a = 150 + ofRandom(50);
}




