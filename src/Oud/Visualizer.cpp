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
}

void Visualizer::display(){
    if(action){
        (*this.*actionFunc)();
    }
    for(int i=0; i<numEvents; i++){
        events[i]->display();
    }
}

void Visualizer::update(){
//    cout << "numEvents: " << numEvents << endl;
    for(int i=0; i<numEvents; i++){
        events[i]->update();
//        cout<<events[i]->type<<endl;
    }
//    cout << numEvents<<endl;
}

void Visualizer::setFunction(int name){
    switch(name){
            case 0:
            actionFunc = &Visualizer::displayRandomQuarter;
            break;
    }
}

void Visualizer::displayRandomQuarter(){
    events[numEvents-1] = new Square(100, ofVec2f(ofRandom(0,ofGetWindowWidth()),0), ofVec2f(100,ofGetWindowHeight()), ofColor::red, &numEvents, events);
    ((Square*)events[numEvents-1])->color.setBrightness(ofRandom(100,255));
}

void Visualizer::makeVerticalBar(){
    events[numEvents-1] = new Bar(&numEvents, events);
}



