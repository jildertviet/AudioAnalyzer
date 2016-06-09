//
//  Ghost.cpp
//  Bas
//
//  Created by Jildert Viet on 24-04-16.
//
//

#include "Ghost.hpp"

Ghost::Ghost(Visualizer* visualizer){
    songName = "Ghost";
    cout << songName << endl;
    this->visualizer = visualizer;
    this->visualizer->makeAlphaBlackScreen();
    visualizer->setAlpha(255);
    bpm = 85;
    makeNewSpaceCube(5);
    visualizer->fadeScreen->size = ofGetWindowSize();
}

void Ghost::stop(){
    for(int i=0; i<spacecubes.size(); i++){
        spacecubes[i]->active = true;
        spacecubes[i]->setEnvelope(1,1,1000); spacecubes[i]->envelope->triggerEnv();
    }
}

void Ghost::keys(int key){
    switch (key) {
case '1':
    switchRotation();
    break;
case '2':
     addAndRemoveVertices();
    break;
case '3':
     drawOneLine();
    break;
case '4':
    slow();
    break;
case '5':
    randomAngle();
    break;
case '6':
    convertToSphere();
    break;
case '7':
    blink();
    break;
case '8':
    setAlpha(10);
    break;
case '9':
    transform();
    break;
case 'f':
    fadeOut();
    break;
    }
}

void Ghost::MidiFunc(ofxMidiMessage msg){
    if(msg.status == MIDI_CONTROL_CHANGE){
                if(msg.control == 1)
                    visualizer->setAlpha(ofMap(msg.value, 0, 127, 8, 255));
    }
    
    if(msg.status == 144){
        switch (msg.pitch) {
            case 36:
                switchRotation();
                break;
            case 37:
                addAndRemoveVertices();
                break;
            case 38:
                drawOneLine();
                break;
            case 39:
                slow();
                break;
                
            case 40:
                randomAngle();
                break;
            case 41:
                convertToSphere();
                break;
            case 42:
                
                break;
            case 43:
                fadeOut();
                break;
                
            case 44:
                blink();
                break;
            case 45:
                for(int i=0; i<40; i++)
                    addAndRemoveVertices();
                break;
            case 46:
                break;
            case 47:
                for(int i=0; i<spacecubes.size(); i++)
                    spacecubes[i]->changeType(0);
                break;
                
            case 48:
                transform();
                break;
            case 49:
                doubleTime();
                break;
            case 50:
                halfTime();
                break;
            case 51:
                for(int i=0; i<spacecubes.size(); i++)
                    spacecubes[i]->changeType(1);
                break;
                
                
                
            default:
                break;
        }
    }
}

void Ghost::makeNewSpaceCube(int amount_){
    for(int i=0; i<amount_; i++){
        addEvent(new SpaceCube(ofVec3f((ofGetWindowWidth()-ofGetWindowHeight())/2.,0,0), ofVec3f(ofGetWindowHeight()*0.75,ofGetWindowHeight()*0.75,-ofGetWindowHeight()*0.75), ofRandom(3,5), 6));
        
        spacecubes.push_back((SpaceCube*)getLast());
        int dir;
        if(ofRandom(-1, 1) > 0){
            dir = 1;
        } else{
            dir = -1;
        }
        spacecubes[i]->radius = 100 + ofRandom((ofGetWindowWidth()/2.)-200);
        spacecubes[i]->rotation_direction = dir;
    }
}

void Ghost::switchRotation(){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->rotateRotationSpeed();
}

void Ghost::addAndRemoveVertices(){
    SpaceCube* scTemp = spacecubes[(int)ofRandom(spacecubes.size())];
    if(ofRandom(-1,1) > 0){
        if(scTemp->mesh.getNumVertices() < 7)
            scTemp->placeNewPoint(ofVec3f(), true);
    } else{
        if(scTemp->mesh.getNumVertices() > 3)
            scTemp->removeLastVertex();
    }
}

void Ghost::drawOneLine(){
    spacecubes[(int)ofRandom(spacecubes.size())]->draw_line = true;
}

void Ghost::slow(){
//    ofSetFrameRate(30);
    for(int i=0; i<spacecubes.size(); i++){
        spacecubes[i]->rotation_speed = spacecubes[i]->rotation_speed/4.;
    }
}

void Ghost::setAlpha(int alpha){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->alpha = 10;
}

void Ghost::randomAngle(){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->randomChooseRotXorRotY();
}

void Ghost::convertToSphere(){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->convert_to_sphere = true;
}

void Ghost::blink(){
    spacecubes[(int)ofRandom(spacecubes.size())]->blink();
}

void Ghost::transform(){
    for(int i=0; i<spacecubes.size(); i++){
        if(i > 0){
            spacecubes[i]->changeType(0);
            spacecubes[i]->getBigger(9);
        } else{
            spacecubes[0]->changeType(0);
            spacecubes[0]->alpha = 5;
        }
    }
}

void Ghost::fadeOut(){
    for(int i=0; i<spacecubes.size(); i++){
//        spacecubes[i]->rotation_speed = spacecubes[i]->rotation_speed/2.;
//        spacecubes[i]->fadeOut();
        spacecubes[i]->active = true;
        spacecubes[i]->setEnvelope(1,1,3000); spacecubes[i]->envelope->triggerEnv();
    }
    spacecubes.clear();
}

void Ghost::halfTime(){
    for(int i=0; i<spacecubes.size(); i++)
        spacecubes[i]->rotation_speed = spacecubes[i]->rotation_speed/2.;
}

void Ghost::doubleTime(){
    for(int i=0; i<spacecubes.size(); i++)
            spacecubes[i]->rotation_speed = spacecubes[i]->rotation_speed*2;
}