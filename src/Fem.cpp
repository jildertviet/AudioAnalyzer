//
//  Fem.cpp
//  Paul
//
//  Created by Jildert Viet on 14-02-16.
//
//

#include "Fem.hpp"

Fem::Fem(Visualizer* visualizer){
    songName = "Fem";
    cout << songName << endl;
    this->visualizer = visualizer;
    visualizer->makeAlphaBlackScreen();
    visualizer->setAlpha(50);
//    addEvent(new AlphaBlackScreen);
//    alphaBlend = ((AlphaBlackScreen*)visualizer->startEvent->getLast());
}

void Fem::stop(){
    for(int i=0; i<numVorms; i++){
        vormen[i]->active = true;
        vormen[i]->setEnvelope(1, 1, 3000);
        vormen[i]->envelope->triggerEnv();
    }
}

void Fem::addVorm(){
    if(numVorms<maxVorm){
        addEvent(new Vorm(8, divisions[numVorms], radiuses[numVorms], ofVec2f(ofGetWindowWidth()/2., ofGetWindowHeight()/2.), false));
        Vorm* last = ((Vorm*)visualizer->startEvent->getLast());
        vormen[numVorms] = last;
        last->formVorm();
        
        last->change_maxspeed(1.0*0.8, 1.5*0.5);
        
        last->particles_visible = false;
        last->lijnmax = pow(40.0, 2.0);
        numVorms++;
        if(lastVorm)
            lastVorm->connectWithVorm(last);
        lastVorm = last;
     } else{
         cout << "Max Vorm amount ("<<maxVorm<<") reached"<<endl;
     }
}

void Fem::makeFirstVorm(){ // Misschien met while?
    addEvent(new Vorm(8, divisions[numVorms], radiuses[numVorms], visualizer->startEvent->screencenter)); numVorms++;
}// Als er niks is, maak dan de eeste 8-hoek

void Fem::deleteVorm(){
    for(int i=0; i<visualizer->startEvent->numEvents; i++){
        if(visualizer->startEvent->getNthEvent(i)->type == "Vorm"){
            delete visualizer->startEvent->getNthEvent(i); break;
            
            
            // Set active = true, time & envelope
        }
    }
}// Met mooie fade out, un-form, get last Vorm



void Fem::MidiFunc(ofxMidiMessage msg){
    if(msg.status == MIDI_CONTROL_CHANGE){
        if(msg.control == 1)
            visualizer->setAlpha(ofMap(msg.value, 0, 127, 8, 255));
    }
    
    if(msg.status == 144){
        if(msg.pitch == 36) addVorm();
        if(msg.pitch == 37) switchRadiusses(false);
        if(msg.pitch == 38) switchRadiusses(true);
        if(msg.pitch == 39){
            switchRadiusses(false);
            addNoise();
        }
        
        if(msg.pitch == 40) rotateVorm();
        if(msg.pitch == 41) formAllVorms();
        if(msg.pitch == 42) oneFrame();
        if(msg.pitch == 43) addNoise();
        
        if(msg.pitch == 46) setLineMax(pow(40.0, 2.0));
        if(msg.pitch == 47) randomLineMax(pow(40.0, 2.0), pow(110.0, 2.0));
        
        if(msg.pitch == 48){
            visualizer->alphaScreen->gradientColor = ofColor(180);
            visualizer->alphaScreen->bGradient = !visualizer->alphaScreen->bGradient;
        }
        if(msg.pitch == 51){
            for(int i=0; i<numVorms; i++){
                vormen[i]->change_state_of_particles(0);
            }
        }
    }
}// slider: lijnmax, slider: alphaBlend

void Fem::keys(int key){
    switch(key){
            case '1':
            addVorm();
            break;
            
        case '2':
            switchRadiusses(false);
            break;
            
        case '3':
            switchRadiusses(true);
            break;
            
        case '4':
            rotateVorm();
            break;
            
        case '5':
            oneFrame();
            break;
            
        case '6':
            formAllVorms();
            break;
            
        case '7':
            addNoise();
            break;
    }
}

void Fem::addNoise(){
    for(int i=0; i<numVorms; i++){
        for(int j=0; j<vormen[i]->particles_amount; j++){
            vormen[i]->particles[j]->add_noise = true;
        }
    }
}

void Fem::randomLineMax(int min, int max){
    for(int i=0; i<numVorms; i++){
        vormen[i]->lijnmax = ofRandom(min, max);
    }
}

void Fem::setLineMax(int val){
    for(int i=0; i<numVorms; i++){
        vormen[i]->lijnmax = val;
    }
}