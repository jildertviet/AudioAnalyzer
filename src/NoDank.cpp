//
//  NoDank.cpp
//  Bas
//
//  Created by Jildert Viet on 05-05-16.
//
//

#include "NoDank.hpp"

NoDank::NoDank(Visualizer* visualizer){
    songName = "NoDank";
    cout << songName << endl;
    this->visualizer = visualizer;
    this->visualizer->makeAlphaBlackScreen();
    visualizer->setAlpha(255);
    bpm = 120;
    
//    receiver.setup(5000);
}

void NoDank::stop(){
    for(int i=0; i<ellipses.size(); i++){
        ellipses[i]->active = true;
        ellipses[i]->setEnvelope(1,1,1000);
        ellipses[i]->envelope->triggerEnv();
    }
}

void NoDank::keys(int key){
    switch (key) {
        case '1':
            addEllipse();
            break;
        case '2':
            changeAddMirror();
            break;
        case '3':
            for(int i=0; i<ellipses.size(); i++){
                ellipses[i]->LFO_alpha = !ellipses[i]->LFO_alpha;
            }
            break;
        case '4':
            oneFrame();
            break;
        case '5':
            oneFrameLarger();
            break;
        case '6':
            halfTime();
            break;
        default:
            break;
    }
}

void NoDank::MidiFunc(ofxMidiMessage msg){
    if(msg.status == MIDI_CONTROL_CHANGE){
        if(msg.control == 1)
            visualizer->setAlpha(ofMap(msg.value, 0, 127, 8, 255));
    }
    
    if(msg.status == 144){
        switch (msg.pitch) {
            case 36:
                addEllipse();
                break;
            case 37:
                break;
            case 38:
                break;
            case 39:
                break;
                
            case 40:
                LFO_alpha();
                
                break;
            case 41:
                oneFrame();
                
                break;
            case 42:
                oneFrameLarger();
                break;
                
                
            case 44:
                changeAddMirror();
                break;
                
                
            case 48:
                deleteCircles();
                break;
            case 50:
                halfTime();
                break;
                
            default:
                break;
        }
    }
}

void NoDank::update(){
    receiveOsc();
}

void NoDank::deleteCircles(){
    int num = ellipses.size();
    for(int i=0; i<num;i++){
        ellipses[i]->active = true;
        ellipses[i]->setEnvelope(1,1,100);
        ellipses[i]->envelope->triggerEnv();
    }
    ellipses.clear();
}

void NoDank::receiveOsc(){
    while(receiver->hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver->getNextMessage(m);
        
        cout << m.getArgAsInt(0) << endl;
        switch (m.getArgAsInt(0)) {
            case 2:
            {
                visualizer->displayVerticalBar();
                Bar* bar = ((Bar*)visualizer->startEvent->getLast());
                bar->setEnvelope(attack, sustain, release);
                
                if(ofRandom(0,7)<5){
                    bar->colors[0] = ofColor(255); // WIT
                } else{
                    bar->colors[0] = ofColor(255,153,12); // ORANGJE
                }
            }
                break;
                
            case 9:
                attack = m.getArgAsFloat(1);
                sustain = m.getArgAsFloat(2);
                release = m.getArgAsFloat(3);
                break;
                
            default:
                break;
        }
    }
}


void NoDank::addEllipse(){
//    for(int i=0; i<8; i++){
        addEvent(new Ellipse());
        ellipses.push_back((Ellipse*)getLast());
//    }
}

void NoDank::changeAddMirror(){
    visualizer->bAddMirror = !visualizer->bAddMirror;
}

void NoDank::LFO_alpha(){
    for(int i=0; i<ellipses.size(); i++){
        ellipses[i]->LFO_alpha = true;
    }
}

void NoDank::oneFrame(){
    for(int i=0; i<ellipses.size(); i++){
        ellipses[i]->fill_oneFrame = true;
    }
}

void NoDank::oneFrameLarger(){
    for(int i=0; i<ellipses.size(); i++){
        ellipses[i]->oneFrameLarger = true;
    }
}

void NoDank::halfTime(){
    ellipses[(int)ofRandom(ellipses.size())]->halfTime();
        
}
/*
 
*/