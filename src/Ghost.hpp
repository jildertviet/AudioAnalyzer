//
//  Ghost.hpp
//  Bas
//
//  Created by Jildert Viet on 24-04-16.
//
//

#ifndef Ghost_hpp
#define Ghost_hpp

#include <stdio.h>
#include "Song.hpp"
#include "Visualizer.hpp"
#include "ofMain.h"
#include "SpaceCube.h"

class Ghost: public Song{
public:
    Ghost(Visualizer* visualizer);
    void keys(int key);
    void MidiFunc(ofxMidiMessage msg);
    void stop();
    
    vector<SpaceCube*> spacecubes;
    
private:
    void makeNewSpaceCube(int amount);
    void switchRotation();
    void addAndRemoveVertices();
    void drawOneLine();
    void slow();
    void randomAngle();
    void convertToSphere();
    void blink();
    void setAlpha(int alpha);
    void transform();
    void fadeOut();
    
    void halfTime();
    void doubleTime();
};
#endif /* Ghost_hpp */
