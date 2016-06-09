/*
 Envelop.cpp - Library for using envelopes.
 Created by Jildert Viet, October 24, 2015.
 Released into the public domain.
 */


#ifndef Envelope_h
#define Envelope_h

#include "ofMain.h"

class Envelope
{
public:
    Envelope();
    Envelope(int attackTime, int sustainTime, int releaseTime);
    float process();
    bool gate = false, sustainBool = false, releaseBool = false;
    float attackTime=100, releaseTime=100, sustainTime=200;
    void attack(), release(), sustain();
    bool loop, trigger;
    float value;
    int time;
    void setShape(int, int, int);
    bool done = false;
    float amp=1;
    void triggerEnv(){ trigger = true; active = true;};
    bool active = false;
};

#endif