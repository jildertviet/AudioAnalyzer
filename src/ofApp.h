#pragma once

#include "ofMain.h"
#include "ofxAudioAnalyzer.h"
#include "Analyzer.hpp"
//#include "Functions.hpp"
//#include "MyThread.hpp"
#include "Visualizer.hpp"
#include "ofxGui.h"
#include "Batobe.hpp"
#include "Paul.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    void audioOut(float * input, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);

    Visualizer* visualizer = nullptr;
    Analyzer* analyzer;
    Batobe* batobe;
    Paul* paul;
    
    ofxPanel gui;
    ofxFloatSlider inputGain;
    
    bool bDisplayVisualizer=true;
    bool bDisplayGui=false;
};

