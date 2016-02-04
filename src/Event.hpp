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
    ~Event(){
        if(!next){
            previous->next = nullptr;
        } else{
            previous->next = next;
            next->previous = previous;
        }
        cout << "Event deleted!" << endl;
        delete envelope;
    }
    
    bool active=false;
    virtual void update();
    virtual void display(){};
    float startTime, endTime;
    float seed;
    
    int *numEvents;
    void addNumEvents(){*(this->numEvents) += 1;};
    void returnType(){cout<<type<<endl;};
    int id;
    Event* *array;
    string type;
    ofVec2f size, loc;
    ofColor *colors; int numColors; void setColors(int numColors); ofColor randomColor(){return colors[(int)ofRandom(numColors)];};
    float speed=1., maxAlpha=255;
    ofColor color;
    string mode;
    Envelope* envelope;
    
    Event* next; Event* previous;
    bool last, first;
    
    virtual void specificFunction(){
        return;
    };
    
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
        if(!next){
            next = toAdd;
            toAdd->previous = this;
        } else{
            next->addEvent(toAdd);
        }
        if(next)
            next->id = id+1;
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
    

};
#endif /* Event_hpp */
