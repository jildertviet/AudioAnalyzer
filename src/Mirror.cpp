//
//  Mirror.cpp
//  Batobe_met_MIDI
//
//  Created by Jildert Viet on 27-05-15.
//
//

#include "Mirror.h"

Mirror::Mirror(){
    
}

Mirror::Mirror(ofVec2f size_, ofVec2f loc_){
    type = "Mirror"; returnType();
    size = size_;
    location = loc_;
    image.allocate(size.x, size.y, OF_IMAGE_GRAYSCALE);
    texture.clear();
    texture.allocate(size.x, size.y, GL_RGBA);

//    Yspeed = ofRandom(-2.5,2.5)+5.0;
//    Yspeed = ofRandom(360);
    ySpeed = ofRandom(1.0);
    angle = 0;
    view = ofVec2f(100+ofRandom(ofGetWindowWidth()-size.x-100), 100+ofRandom(ofGetWindowHeight()-size.y-100));
    speed = 0.3;
    move_up = false;
}

Mirror::~Mirror(){
//    if(texture.bAllocated())
//        texture.clear();
}

void Mirror::specificFunction(){
//    image.grabScreen(0,0,size.x, size.y);
    if(ofGetFrameNum() > 1)
        texture.loadScreenData(view.x,view.y,size.x, size.y);
    moveTriangle();
    moveUp();
}

void Mirror::display(){    
    ofPushMatrix();
    ofTranslate(location.x+(size.x/2.),0);
    ofRotateY(angle);
    ofTranslate(-(location.x+(size.x/2.)),0);

    ofSetColor(255);
    if(bDisplayMirror)
        texture.draw(location);
    if(draw_sides){
        ofSetColor(255,100);
        ofNoFill();
        ofSetLineWidth(2);
        ofDrawRectangle(location.x, location.y, size.x, size.y);
    }
    ofFill();
    ofPopMatrix();
    if(draw_view)
        displayView();
}

void Mirror::moveTriangle(){
    if(moveBackwards){
        angle -= ySpeed;
    } else{
        angle += ySpeed;
    }
    if(angle > 45)
        moveBackwards = true;
    if(angle < -45)
        moveBackwards = false;
}

void Mirror::reSpawn(){
    location = ofVec2f(ofGetWindowWidth(), ofRandom(ofGetWindowHeight()));
}

void Mirror::displayView(){
    ofSetColor(255,0,0,100);
    ofNoFill();
    ofDrawRectangle(view.x, view.y, size.x, size.y);
    ofFill();
}

void Mirror::moveUp(){
    if(move_up){
        location += ofVec2f(0,speed);
        if(location.y+size.y > ofGetWindowHeight() || location.y < 0){
            speed *= -1;
        }
    }
}