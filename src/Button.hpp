//
//  Button.hpp
//  Paul
//
//  Created by Jildert Viet on 17-02-16.
//
//

#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include "ofMain.h"

class Button{
public:
    Button();
    Button(ofVec2f size, ofVec2f loc, string name){
        this->size = size; this->loc = loc; this->name = name;
    }
    ofVec2f size, loc;
    string name;
    void display(){
        if(state){
            color.a = 255;
        } else{
            color.a = 200;
        }
        ofSetColor(color);
        ofDrawRectangle(loc.x, loc.y, size.x, size.y);
        ofSetColor(ofColor::white);
        ofDrawBitmapString(name, loc+ofVec2f(0,10));
    };
    
    void checkIfMouseIsOnButton(int x, int y){
        if(x<loc.x+size.x&&x>loc.x&&y>loc.y&&y<loc.y+size.y){
            state = !state;
//            cout << "Click" << endl;
        }
    };
    
    bool state=false;
    ofColor color = ofColor::lightSkyBlue;
};
#endif /* Button_hpp */
