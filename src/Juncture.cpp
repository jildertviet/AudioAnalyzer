//
//  Juncture.cpp
//  Bas
//
//  Created by Jildert Viet on 06-04-16.
//
//

#include "Juncture.hpp"

Juncture::Juncture(Visualizer* visualizer){
    songName = "Juncture";
    cout << songName << endl;
    this->visualizer = visualizer;
    bpm = 105;
    topLayer = visualizer->topLayer;
    visualizer->alphaScreen->bGradient = false;
}

void Juncture::stop(){
    for(int i=0; i<numSquares; i++){
        allSquares[i]->deleteWithFade(1000);
    }
    for(int i=0; i<mirrors.size(); i++){
        mirrors[i]->active = true;
    }
}

void Juncture::MidiFunc(ofxMidiMessage msg){
    if(msg.status == MIDI_CONTROL_CHANGE){
                if(msg.control == 1)
                    visualizer->setAlpha(ofMap(msg.value, 0, 127, 8, 255));
    }
    
    if(msg.status == 144){
        switch (msg.pitch) {
            case 36:
                makeSquare(1);
                break;
            case 37:
                makeSquare(2);
                break;
            case 38:
                makeSquare(3);
                break;
            case 39:
                makeRandomMirror();
                break;
                
            case 40:
                switchMirrorVisibility();
                break;
            case 41:
                randomMizeMirrorAngle(-45,45);
                break;
            case 42:
                switchMirrorMovement();
                break;
            case 43:
                
                break;
                
            case 44:
                jumpAllForward(-50,50);
                break;
                
            case 48:
                fadeOutAllSquares();
                break;
            case 49:
                
                doubleTime();
                break;
            case 50:
                halfTime();
                break;
           
                
                
            default:
                break;
        }
    }
} // slider: alphaBlend

void Juncture::keys(int key){
    switch(key){
        case '1':
            makeSquare(1);
            break;
        case '2':
            makeSquare(2);
            break;
        case '3':
            makeSquare(3);
            break;
        case '4':
            makeRandomMirror();
            break;
        case '5':
            switchMirrorVisibility();
            break;
        case 6:
            randomMizeMirrorAngle(-45,45);
            break;
        case 7:
            switchMirrorMovement();
            break;
        case 8:
            
            break;
        case 9:
            
            break;
    }
}

void Juncture::makeSquare(int type){
    switch(type){
        case 1:
            if(numSquares1 < maxSquares1){
                topLayer->addEvent(new Square(ofVec2f(100,50),ofVec2f(ofGetWindowWidth()-100,50+ofRandom(ofGetWindowHeight()-50))));
                squares1[numSquares1] = ((Square*)topLayer->getLast());
                allSquares[numSquares] = ((Square*)topLayer->getLast());
                squares1[numSquares1]->speed = ofRandom(0.5,1.0);
                squares1[numSquares1]->colors[0] = ofColor(255,ofRandom(155)+100);
                
                numSquares1++; numSquares++;
            }
            break;
        case 2:
            if(numSquares2 < maxSquares2){
                topLayer->addEvent(new Square(ofVec2f(5,400), ofVec2f(ofGetWindowWidth()-5,200)));
                squares2[numSquares2] = ((Square*)topLayer->getLast());
                allSquares[numSquares] = ((Square*)topLayer->getLast());
                squares2[numSquares2]->speed = 1.5+ofRandom(0.1);
                squares2[numSquares2]->colors[0] = ofColor(255,ofRandom(155)+100);
                
                numSquares2++; numSquares++;
            }
            break;
        case 3:
//            if(numSquares3 < maxSquares3){
                topLayer->addEvent(new Square(ofVec2f(20,200), ofVec2f(ofGetWindowWidth()-20,ofGetWindowHeight()-200)));
//                squares3[numSquares3] = ((Square*)topLayer->getLast());
                Square* square = ((Square*)topLayer->getLast());
//                squares3[numSquares3] = square;
//                allSquares[numSquares] = squares3[numSquares3];
            
                square->speed = ofRandom(2.5,3.0);
                square->colors[0] = ofColor(255,ofRandom(155)+100);
                square->deleteWithFade(3000);
            
//                numSquares3++; // numSquares++;
//            }
            break;
    }
}

void Juncture::randomMizeMirrorAngle(int min, int max, int index){ // -45, 45
    if(index==99){ // Do for all
        for(int i=0; i<mirrors.size(); i++)
            mirrors[i]->angle = ofRandom(min,max);
        return;
    } else{ // Do specific index
        mirrors[index]->angle = ofRandom(min,max);
    }
}

void Juncture::randomMizeSquareSpeed(float min, float max, int index){ // 1.0, 2.0
    if(index==99){ // Do for all
        for(int i=0; i<numSquares; i++)
            allSquares[i]->speed = ofRandom(min, max);
        return;
    } else{ // Do specific index
        allSquares[index]->speed = ofRandom(min, max);
    }
}

void Juncture::switchMirrorMovement(){
    for(int i=0; i<mirrors.size(); i++)
        mirrors[i]->move_up = !(mirrors[i]->move_up);
}

void Juncture::deleteAllSquares(){
    for(int i=0; i<numSquares; i++){
        allSquares[i]->deleteWithFade(1);
        allSquares[i] = nullptr;
        numSquares--;
    }
}

void Juncture::makeRandomMirror(){
    if(mirrors.size() < maxMirrors){
        int randomAdd = ofRandom(100);
        int size = 100 + randomAdd;
        topLayer->addEvent(new Mirror(ofVec2f(size,size), ofVec2f(ofRandom(ofGetWindowWidth()-size), ofGetWindowHeight()-size)));
        mirrors.push_back(((Mirror*)topLayer->getLast()));
        numMirrors++;
    }
}

void Juncture::switchMirrorVisibility(){
    for(int i=0; i<mirrors.size(); i++){
        cout << i << endl;
        mirrors[i]->bDisplayMirror = !(mirrors[i]->bDisplayMirror);
//        mirrors[i]->type;
//        mirrors[i]->draw_sides = true;
    }
}

void Juncture::fadeOutAllSquares(){
    for(int i=0; i<numSquares; i++){
        allSquares[i]->deleteWithFade(500);
    }
    numSquares = numSquares1 = numSquares2 = numSquares3 = 0;
}

void Juncture::jumpForWard(int index, int amount){
    allSquares[index]->loc.x += amount;
}

void Juncture::jumpAllForward(int min, int max){
    for(int i=0; i<numSquares; i++){
        jumpForWard(i, ofRandom(min,max));
    }
}

void Juncture::deleteHalfSquares(){
    for(int i=numSquares-1; i>numSquares/2; i--){
        allSquares[i]->deleteWithFade(1000);
        allSquares[i] = nullptr;
        numSquares--;
    }
}
void Juncture::halfTime(){
    for(int i=0; i<numSquares; i++)
        allSquares[i]->speed = allSquares[i]->speed/2.;
}
void Juncture::doubleTime(){
    for(int i=0; i<numSquares; i++)
        allSquares[i]->speed = allSquares[i]->speed*2;
}