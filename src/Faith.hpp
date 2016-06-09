//
//  Faith.hpp
//  Bas
//
//  Created by Jildert Viet on 18-04-16.
//
//

#ifndef Faith_hpp
#define Faith_hpp

#include <stdio.h>
#include "Song.hpp"
#include "VormCustom.hpp"
#include "VideoPlayer.hpp"

#endif /* Faith_hpp */

class Faith: public Song{
public: Faith(Visualizer* visualizer);
    void makeVerticalParticleLine(int x, int amount, int destX, float speedMin, float speedMax);
    void makeVerticalLineConnectedToCube();
    void keys(int key);
    void stop();
    void MidiFunc(ofxMidiMessage msg);
    
    VideoPlayer* videoPlayer = nullptr;
    VideoPlayer* videoPlayer2 = nullptr;
    VormCustom* lastLine = nullptr;
    VormCustom* cube = nullptr;
    void makeCube();
private:
    void connectLine(VormCustom* line);
    VormCustom* lastCubeLine = nullptr;
    vector<VormCustom*> lastLines;
    void rememberLine(VormCustom* line);
    
    void startMove(int duration);
};
