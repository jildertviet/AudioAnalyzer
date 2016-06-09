//
//  MultiMesh.hpp
//  Bas
//
//  Created by Jildert Viet on 23-03-16.
//
//

#ifndef MultiMesh_hpp
#define MultiMesh_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Event.hpp"
#include "Wavetable.h"
#include "Envelope.h"

class MultiMesh: public Event{
public:
    MultiMesh(int size, ofFloatColor color = ofFloatColor(1,1,1,1));
    ofMesh* meshes;
    int numMeshes=0;
    
    void display();
    void specificFunction();
    
    ofFloatColor globalColor;
    float* colorAlphas;
    
    void generateRandomMeshes(int num, ofFloatColor color = ofFloatColor(1,1,1,1));
    void generateSymmetricMeshes(int num, ofFloatColor color = ofFloatColor(1,1,1,1), float radius = 400);
    
    void changeMode(ofPrimitiveMode mode);
    Wavetable*** wavetables;
    Envelope* fadeOutEnv; bool bFadeOut = false;
    Envelope* fadeInEnv; bool bFadeIn = false;
    
    void morph(); bool bMorph = false; void doMorph(float angle, float time); float morphAngle, morphTime;
    
    void deleteWithFade(int releaseTime); void fadeOut();
    void fadeIn();
    
    void addRandomMesh(float radius, ofFloatColor color = ofFloatColor(1,1,1,1));
    
    void doubleTime(); void halfTime();
    void changeColor(ofFloatColor color);
    void addRadius(int radiusIncrease);
    void growRadius(int direction, float speed); bool bGrowRadius=false;
    ofVec2f** locations;
    
    void centerPulse();
    
    void setFrequency(float freq, float* multipliers, int size);
    
    int bpm = 120;
    
    float radius;
    void changeLocations();
    
    bool bMoveWithPulse = false; void moveWithPulse(); Wavetable* pulseOsc;
    int pulseMoveWidth; int centerPulseRadius = 50;
};
#endif /* MultiMesh_hpp */
