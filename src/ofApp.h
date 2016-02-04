#pragma once

#include "ofMain.h"
#include "ofxAudioAnalyzer.h"
#include "Analyzer.hpp"
#include "Functions.hpp"
#include "MyThread.hpp"
#include "Visualizer.hpp"
#include "ofxGui.h"

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
    
    ofSoundStream soundStream;
    ofxAudioAnalyzer audioAnalyzer1;
    
    float *buffer_1;
    
    float *spectrum1;
    int spectrumSize;
    
    int bufferSize;
    
    
    ////// TEST
    
    int xPos=0;
    float *logSpectrum32;
    
//    void convertToLogSpectrum(float spectrum[], float newSpectrum[]);
//    void addToFreqBandTracks(float logSpectrum[], float arrayToWrite[]);
    float *freqBandTracks;
    int freqBandTracksSize;
    int freqBandTrackSize;
//    int writePosFreqBandTracks=0;
//    void calculateMostActiveBandRMS(float tracks[], float arrayToWrite[]);
    float* RMSValues;
//    void calculateMostActiveBandFlux(float tracks[], float arrayToWrite[]);
    float* FluxValues;
    
    void drawFreqBandTracks();
    
    Functions*   functions;

    Visualizer* visualizer;
    Analyzer* analyzer;
    
    void audioSetup();
    
    
    float inputGain=1;
    bool bDisplayAnalyzer=false;
};

