/*
 Envelop.cpp - Library for using envelopes.
 Created by Jildert Viet, October 24, 2015.
 Released into the public domain.
 */

#include "Envelope.h"

Envelope::Envelope(){
    
}

Envelope::Envelope(int attackTime, int sustainTime, int releaseTime){
    this->attackTime = attackTime;
    this->sustainTime = sustainTime;
    this->releaseTime = releaseTime;
    
    value = 0;
    gate = loop = sustainBool = false;
}

void Envelope::attack(){
    done = false;
    if(time+attackTime > ofGetElapsedTimeMillis()){
        value = (ofGetElapsedTimeMillis() - time)/attackTime;
    } else{
        sustainBool = true;
        time = ofGetElapsedTimeMillis();
        gate = false;
    }
    if(value > 1) value = 1;
}

void Envelope::sustain(){
    if(time+sustainTime > ofGetElapsedTimeMillis() && sustainBool){
        value = 1;
    } else{
        time = ofGetElapsedTimeMillis();
        sustainBool = false;
        releaseBool = true;
    }
}

void Envelope::release(){
    if(time+releaseTime > ofGetElapsedTimeMillis()){
        value = 1.f-((ofGetElapsedTimeMillis() - time)/releaseTime);
    } else{
        if(loop){
            gate = true;
            time = ofGetElapsedTimeMillis();
        } else{
            value = 0;
            releaseBool = false;
            done = true;
            active = false;
        }
    }
    if(value < 0) value = 0;
}

float Envelope::process(){
    if(trigger){
        active = true;
        time = ofGetElapsedTimeMillis();
        gate = true;
        trigger = false;
    }
    if(gate)
        attack();
    if(sustainBool)
        sustain();
    if(releaseBool)
        release();
    return value*amp;
}

void Envelope::setShape(int attack, int sustain, int release){
    attackTime = attack;
    sustainTime = sustain;
    releaseTime = release;
}