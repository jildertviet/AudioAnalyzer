//
//  AlphaBlackScreen.cpp
//  Paul
//
//  Created by Jildert Viet on 14-02-16.
//
//

#include "AlphaBlackScreen.hpp"

AlphaBlackScreen::AlphaBlackScreen(){
    type = "AlphaBlackScreen"; returnType();
    colors[0] = ofColor(0,20);
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
}

AlphaBlackScreen::AlphaBlackScreen(bool hasAlphaBlending){
    type = "AlphaBlackScreen"; returnType();
    colors[0] = ofColor(0,20);
    if(hasAlphaBlending){
        ofSetBackgroundAuto(false);
        ofEnableAlphaBlending();
    } else{
        ofSetBackgroundAuto(true);
        ofDisableAlphaBlending();
        ofBackground(0);
    }
}

AlphaBlackScreen::~AlphaBlackScreen(){
    ofSetBackgroundAuto(true);
    ofDisableAlphaBlending();
    ofBackground(0);
}

void AlphaBlackScreen::display(){
    if(ofGetBackgroundAuto()){
        ofSetBackgroundAuto(false);
        ofEnableAlphaBlending();
    }
    ofSetColor(colors[0]);
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void AlphaBlackScreen::specificFunction(){
//    cout << "Alpha: " << colors[0].a << endl;
//    if(hasAlphaBlending){
//        if(!alphaIs255){
//            if(colors[0].a == 255){
//                alphaIs255 = true;
//                
//                ofSetBackgroundAuto(true);
//                ofDisableAlphaBlending();
//                ofBackground(0);
//            }
//        } else{
//            if(colors[0].a < 255){
//                alphaIs255 = false;
//                
//                ofSetBackgroundAuto(false);
//                ofEnableAlphaBlending();
//            }
//        }
//    } else{
//        return;
//    }
}

