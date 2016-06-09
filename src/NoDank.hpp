//
//  NoDank.hpp
//  Bas
//
//  Created by Jildert Viet on 05-05-16.
//
//

#ifndef NoDank_hpp
#define NoDank_hpp

#include <stdio.h>
#include "Song.hpp"
#include "Visualizer.hpp"
#include "ofMain.h"
#include "Image.hpp"
#include "MultiMesh.hpp"
#include "Ellipse.h"
#include "ofxOsc.h"

class NoDank: public Song{
public:
    NoDank(Visualizer* visualizer);
    void keys(int key);
    void MidiFunc(ofxMidiMessage msg);
    void update();
    
    void addEllipse();
    void changeAddMirror();
    void LFO_alpha();
    void halfTime();
    void oneFrameLarger();
    void oneFrame();
    vector<Ellipse*> ellipses;
    void stop();
    
    void deleteCircles();
    
    void receiveOsc();
    ofxOscReceiver* receiver;
    
    int attack=1; int sustain=100; int release=500;
};

#endif /* NoDank_hpp */