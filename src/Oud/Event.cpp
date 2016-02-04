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
}

void Event::update(){
    if(active && ofGetElapsedTimeMillis() > endTime){
        cout << "Event (id:"<<id<<") has passed!" << endl;
        delete this;
    }
}

Event::~Event(){
    for(int i=id; i<(*numEvents)-1; i++){
        array[i]=array[i+1];
        array[i]->id = array[i]->id - 1;
    }
    *numEvents -= 1;
    cout << "Event deleted!" << endl;
}

void Event::display(){
    
}