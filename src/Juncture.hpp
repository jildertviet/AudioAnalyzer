//
//  Juncture.hpp
//  Bas
//
//  Created by Jildert Viet on 06-04-16.
//
//

#ifndef Juncture_hpp
#define Juncture_hpp

#include <stdio.h>
#include "Song.hpp"
#include "Visualizer.hpp"
#include "ofMain.h"
#include "Mirror.h"
#include "Square.hpp"

class Juncture: public Song{
public:
    Juncture(Visualizer* visualizer);
    void MidiFunc(ofxMidiMessage msg);
    void stop();
    
    int numSquares = 0; int numSquares1=0; int numSquares2=0; int numSquares3 = 0;
    Square* allSquares[150];
    Square* squares1[50]; int maxSquares1 = 50;
    Square* squares2[50]; int maxSquares2 = 50;
    Square* squares3[50]; int maxSquares3 = 50;
//    Mirror* mirrors[10];
    int maxMirrors = 10;
    int numMirrors = 0;
    vector<Mirror*> mirrors;
    void keys(int key);

private:
    
    void makeSquare(int type);
    void randomMizeMirrorAngle(int min, int max, int index=99);
    void randomMizeSquareSpeed(float min, float max, int index=99);
    void switchMirrorMovement();
    void switchMirrorVisibility();
    void deleteAllSquares();
    void makeRandomMirror();
    void fadeOutAllSquares();
    void jumpForWard(int index, int amount);
    
    void jumpAllForward(int min, int max);
    void deleteHalfSquares();
    void halfTime();
    void doubleTime();
    
    Event* topLayer;
};

#endif /* Juncture_hpp */
