//
//  Event.hpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 24-01-16.
//
//

#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include "ofMain.h"

class Event{
public:
    Event();
    ~Event();
    
    bool active=true;
    virtual void update();
    virtual void display();
    float startTime, endTime;
    
    int *numEvents;
    void addNumEvents(){*(this->numEvents) += 1;};
    string returnType(){cout<<type<<endl;};
    
    Event* *array;
    string type;
    int id;
    ofVec2f size, loc;
    ofColor color;
    float speed=1;
};
#endif /* Event_hpp */
