//
//  MamaOtis.hpp
//  Bas
//
//  Created by Jildert Viet on 24-04-16.
//
//

#ifndef MamaOtis_hpp
#define MamaOtis_hpp

#include <stdio.h>
#include "Song.hpp"
#include "Visualizer.hpp"
#include "ofMain.h"
#include "Vorm.h"
#include "VormCustom.hpp"

class MamaOtis: public Song{
public:
    MamaOtis(Visualizer* visualizer);
    void stop();
    
    void keys(int key);
    void MidiFunc(ofxMidiMessage msg);
    
    vector<Vorm*> vormen;
    vector<VormCustom*> triangles;
    VormCustom* lastTriangle = nullptr;
    
    
    void makeVorm(int numSides, int sideDivision, float radius, ofVec2f center, Boolean on_destination=true);
    void functionOne();
    void functionTwo();
    void changeSpeed();
    void makeThings1();
    void makeThings2();
    
    void makeCube1(); // squares
    void makeCube2();
    void showParticlesVormen();
    
    void fall();
    void thingsWithCircle();
    
    void finalVorm();
    
    
private:
    Vorm* cube1 = nullptr; Vorm* cube2 = nullptr;
};
#endif /* MamaOtis_hpp */
