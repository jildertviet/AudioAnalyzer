//
//  Analyzer.hpp
//  example-spectrumOutput
//
//  Created by Jildert Viet on 15-01-16.
//
//

#ifndef Analyzer_hpp
#define Analyzer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxAudioAnalyzer.h"
#include "FluxMeter.hpp"
#include "Meter.hpp"
#include "ofxGui.h"
#include "OnsetDetector.hpp"
#include "deviceSelector.hpp"
#include "ofxInputField.h"
#include "SpectrumDisplay.hpp"

class Analyzer{
public:
    Analyzer();
    Analyzer(ofBaseApp* baseApp, int bufferSize, int sampleRate);
    ~Analyzer(){
        analyzer.exit();
        soundStream.stop();
        soundStream.close();
    }
    
    void display();
    void update();
    void mouseFunc(int x, int y);
//    float value=0;
//    string title;
    float interpolate(float v1, float v2, float division);
    void setValueInterpolated(float v, float division);
    
//------------------------------------------------------------------ ONSET DETECTION & FILTERING
    void setFilters(int numBands, float *frequencies);
    OnsetDetector* *onsetDetectors;
    Filter* *filters;
    float **filteredBuffers;
    int numFilters;
    void writeFilterDataToBuffer(float *buffer, int bufferSize);
//------------------------------------------------------------------

    
    void displayValueWithMeter(float value, ofVec2f loc, ofVec2f size, string name);
    
    void chopSpectrum(float *spectrum, int *cutoffFreqs, int numBands, float **bands);
    
    int freqToBinIndex(int freq){
        float binWidth = (sampleRate/2.)/bufferSize;
        binWidth*=2.;
        return freq/binWidth;
    }
    
    void setCutOffFreqs(int *cutOffFreqs, int numBands);
    
    float RMS=0, Salience=0, HarmonicComplexity=0, Hfc=0, SelectedBin=0.5;
//    float RMSLP=10, SalienceLP=10, HarmonicComplexityLP=10, HfcLP=8;
    
//    float **bands;
    int sampleRate, bufferSize;
//    int *cutOffFreqs;
    
//    struct valuePerBand {float RMS=0; int bandIndex;};
//    valuePerBand *valuesPerBand;
    int numMeters;
    Meter* *meters;
    
    bool bDisplayGui=false;
    
    ofXml globalXml; void loadXmlValues(); void saveXmlValues();
    
    
    
    //-------------------------------------------------------------------------------------------------------------
    void process(float *buffer, int bufferSize);
    
    float *buffer;
    
    void analyzerKeys(int key);
    bool bDisplay=false;
    //-------------------------------------------------------------------------------------------------------------
    SpectrumDisplay* spectrumDisplay;
//    float* spectrum;
//    int spectrumSize;
    
    
private:
    // PRESETS
    string presetNames[5] = {"1", "2", "3", "4", "5"};
    ofxPanel loadPresetGui, savePresetGui;
    ofxButton loadButtons[5]; ofxButton saveButtons[5];
    Button* loadPresetButton; Button* savePresetButton;
    int selectedPreset=0;
    void presetSetup();
    
    void loadPresetButtonPressed1(){selectedPreset = 0; loadXmlValues();};
    void loadPresetButtonPressed2(){selectedPreset = 1; loadXmlValues();};
    void loadPresetButtonPressed3(){selectedPreset = 2; loadXmlValues();};
    void loadPresetButtonPressed4(){selectedPreset = 3; loadXmlValues();};
    void loadPresetButtonPressed5(){selectedPreset = 4; loadXmlValues();};
    
    void savePresetButtonPressed1(){selectedPreset = 0; saveXmlValues();};
    void savePresetButtonPressed2(){selectedPreset = 1; saveXmlValues();};
    void savePresetButtonPressed3(){selectedPreset = 2; saveXmlValues();};
    void savePresetButtonPressed4(){selectedPreset = 3; saveXmlValues();};
    void savePresetButtonPressed5(){selectedPreset = 4; saveXmlValues();};
    
    // GUI
    ofxPanel gui;
    void guiSetup();
    ofxFloatSlider RMSLP, SalienceLP, HarmonicComplexityLP, HfcLP, SelectedBinLP;
//    ofxToggle* deviceToggles;
    
    
    void setValuePerBand();
    
    int bandWritePos=0;
    ofxAudioAnalyzer analyzer;
    
    
    
    ofSoundStream soundStream;
    void audioSetup(ofBaseApp* baseApp, string device);
//    void changeAudioDevice(bool & val);
    ofBaseApp* baseApp;
    
    deviceSelector* deviceSelector;
    
    

    
    ofxIntField oscPort;
    
    
};
#endif /* Analyzer_hpp */
