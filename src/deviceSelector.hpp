//
//  deviceSelector.hpp
//  Paul
//
//  Created by Jildert Viet on 04-03-16.
//
//

#ifndef deviceSelector_hpp
#define deviceSelector_hpp

#include <stdio.h>
#include "ofxGui.h"
#include "ofMain.h"

class deviceSelector{
public:
    deviceSelector(ofBaseApp* baseApp, ofSoundStream* soundStream, int sampleRate=441000, int bufferSize=1024, int ticksPerBufferDivision=64);
    void display();
    ofxPanel gui;
    ofxLabel* names;
    ofxButton select;
    ofxIntSlider deviceIndex;
    bool bDisplay=false;
    
private:
    int ticksPerBuffer;
    int sampleRate, bufferSize;
    int numDevices;
    void selectFunction();
    ofSoundStream* soundStream;
    ofBaseApp* baseApp;
};
#endif /* deviceSelector_hpp */
