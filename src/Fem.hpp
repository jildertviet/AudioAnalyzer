//
//  Fem.hpp
//  Paul
//
//  Created by Jildert Viet on 14-02-16.
/*
 
 Pad 1: Make first
 
 
 
 
 */

#ifndef Fem_hpp
#define Fem_hpp

#include <stdio.h>
#include "Visualizer.hpp" // Zou niet hoeven, gebeurt al bij Song... 
#include "ofMain.h"
#include "Song.hpp"

class Fem: public Song{
public:
    Fem(Visualizer* visualizer); // AlphaBlackScreen maken
    void deleteVorm(); // Met mooie fade out, un-form
    void addVorm(); // 8-hoek die groter is dan de vorige
    void makeFirstVorm(); // Als er niks is, maak dan de eeste 8-hoek
    void stop();
    
    int divisions[9] = {2, 4, 6, 7, 2, 4, 6, 7, 2};
//    int divisions[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    float radiuses[9] = {50, 140, 230, 320, 80, 170, 260, 350, 110};
    int maxVorm = 9;
    Vorm* vormen[9];
    Vorm* lastVorm = nullptr;
    int numVorms = 0;
    
    AlphaBlackScreen* alphaBlend;
    
    
    // MIDI FUNCTIES
    
    void MidiFunc(ofxMidiMessage msg); // slider: lijnmax, slider: alphaBlend, add_noise & noise_max slider
    
    void switchRadiusses(bool instant){
        int oneTemp = ofRandom(numVorms);
        int twoTemp = ofRandom(numVorms);
        while(oneTemp == twoTemp){
            twoTemp = ofRandom(numVorms);
        }
        vormen[oneTemp]->switchRadiusses(vormen[twoTemp]);
        if(instant){
            vormen[oneTemp]->instantFormVorm();
            vormen[twoTemp]->instantFormVorm();
        }
    }
    
    void rotateVorm(){
        int oneTemp = ofRandom(numVorms);
        if(ofRandom(-1,1) > 0){
            vormen[oneTemp]->changeAngleOffset(15);
        } else{
            vormen[oneTemp]->changeAngleOffset(-15);
        }
    }
    
    void oneFrame(){
        for(int i=0; i<numVorms; i++){
            vormen[i]->showFrame = true;
        }
    }
    
    void formAllVorms(){
        for(int i=0; i<numVorms; i++){
            vormen[i]->instantFormVorm();
        }
    }
    
    void keys(int key);
    
    void addNoise();
    void randomLineMax(int min, int max);
    void setLineMax(int val);
    // Array met centers, Vorm-side-divisions, maxSpeeds
    
    
    /*
     

     
     if(msg.pitch == 38){
     composition->lijn_one_frame = true;
     }
     
     */
};
#endif /* Fem_hpp */
