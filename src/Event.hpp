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
#include "Envelope.h"

class Event{
public:
    Event();
    ~Event();
    
    bool active=false;
    virtual void update();
    virtual void display(){};
    virtual void ownDtor(){};
    float startTime, endTime;
    float seed;
    
    int numEvents=1;
    int* numEventsPtr;
    void addNumEvents(){(this->numEvents)++;};
    void returnType(){cout<<type<<endl;};
    int id;
    Event* *array;
    string type;
    ofVec2f size, loc;
    ofColor *colors; int numColors; void setColors(int numColors); ofColor randomColor(){return colors[(int)ofRandom(numColors)];};
    float speed=1., maxAlpha=255;
    string mode;
    Envelope* envelope;
    
    Event* next; Event* previous;
    bool last, first;
    ofVec2f screencenter;
    
    Event* getNthEvent(int n){
        if(n>=0 && next){
            next->getNthEvent(n-1);
        } else{
            return this;
        }
    }
    
    virtual void specificFunction(){
        return;
    };
    
    string returnType(bool recursive, bool fromEnd=false){
        if(recursive && !fromEnd){
            if(next)
                returnType(true);
            return type;
        }
        if(recursive && fromEnd){
            if(getLast()->previous){
                getLast()->returnType(true, true);
            } else{
                return type;
            }
        }
    }
    void updateMain(){
        if(next)
            next->updateMain();
        specificFunction();
        update();
    }
    
    void displayMain(){
        if(next)
            next->displayMain();
        display();
    }
    
    void addEvent(Event* toAdd){
        numEvents++;
        toAdd->numEventsPtr = &numEvents;
        if(!next){
            next = toAdd;
            toAdd->previous = this;
        } else{
            next->addEvent(toAdd);
        }
        if(next)
            next->id = id+1;
    }
    
    void addEventAsFirst(Event* toAdd){
        if(next)
            next->previous = toAdd;
        next = toAdd;
        return;
    }
    
    Event* getLast(){
        // Als een Event geen 'next' heeft, returned ie zichzelf, omdat ie de laatste is
        if(next){
            return next->getLast();
        } else{
            return this;
        }
    }
    
    void setEndTime(float duration){
        endTime = startTime + duration;
    }
    
    void setEnvelope(int attack, int sustain, int release);
    ofVec2f direction;
    
    void checkBorders();
    
};
#endif /* Event_hpp */
