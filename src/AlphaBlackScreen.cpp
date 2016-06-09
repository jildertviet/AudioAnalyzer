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
    colors[0] = ofColor(0,255);
    switchActiveness(true);
}

AlphaBlackScreen::~AlphaBlackScreen(){
    ofSetBackgroundAuto(true);
    ofDisableAlphaBlending();
    ofBackground(0);
}

void AlphaBlackScreen::display(){
    if(bDoAlphaBlend){
        if(bGradient){
            ofColor edgeColor(0, 0, 0, gradientAlpha);
            ofColor center = gradientColor;
            center.a = gradientAlpha;
            ofBackgroundGradient(center, edgeColor, OF_GRADIENT_CIRCULAR);
        } else{
            ofSetColor(colors[0]);
            ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        }
    } else{
        return;
    }
}

void AlphaBlackScreen::switchActiveness(bool state){
    bDoAlphaBlend = state;
    if(bDoAlphaBlend){
        ofSetBackgroundAuto(false);
        ofEnableAlphaBlending();
    } else{
        ofSetBackgroundAuto(true);
        ofDisableAlphaBlending();
        ofBackground(0);
    }
}

void AlphaBlackScreen::setAlpha(int alpha){
    gradientAlpha = alpha;
    colors[0] = ofColor(0,alpha);
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

