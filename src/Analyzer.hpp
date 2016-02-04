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
#include "Flux.hpp"
#include "Meter.hpp"
#include "ofxGui.h"
#include "OnsetDetector.hpp"

class Analyzer{
public:
    Analyzer();
    Analyzer(int id, string title, int bufferSize, int sampleRate, int bandWidth, int bandSize);
    ~Analyzer(){
        analyzer.exit();
    }
    
    void display();
    float value=0;
    string title;
    float interpolate(float v1, float v2, float division);
    void setValueInterpolated(float v, float division);
//-------------------------------------------------------------------------------------------------------------
    void process(float *buffer, int bufferSize){
        analyzer.analyze(buffer, bufferSize);
        
        RMS = interpolate(RMS, analyzer.getRms(), RMSLP);
        Salience = interpolate(Salience, analyzer.getSalience(), SalienceLP);
        // Moet nog ge-limit worden :)
        HarmonicComplexity = interpolate(HarmonicComplexity, analyzer.getSpectralComplex()/30., HarmonicComplexityLP);
        Hfc = interpolate(Hfc, analyzer.getHfc()/300., HfcLP);
        
        chopSpectrum(analyzer.getSpectrum(), cutOffFreqs, numBands, bands);
        setValuePerBand();
//        fluxRMS.setValue(RMS);  fluxHfc.setValue(Hfc); fluxHarmonicComplexity.setValue(HarmonicComplexity); fluxSalience.setValue(Salience);
    };
    
    
    
    
    
    
    void displayValueWithMeter(float value, ofVec2f loc, ofVec2f size, string name);
    
    void chopSpectrum(float *spectrum, int *cutoffFreqs, int numBands, float **bands);
    
    int freqToBinIndex(int freq){
        float binWidth = (sampleRate/2.)/bufferSize;
        binWidth*=2.;
        return freq/binWidth;
    }
    
    void setCutOffFreqs(int *cutOffFreqs, int numBands);
    
    float RMS=0, Salience=0, HarmonicComplexity=0, Hfc=0;
//    float RMSLP=10, SalienceLP=10, HarmonicComplexityLP=10, HfcLP=8;
    
    float **bands;
    int numBands, bandSize, sampleRate, bufferSize;
    int *cutOffFreqs;
    
    
    struct valuePerBand {float RMS=0; int bandIndex;};
    valuePerBand *valuesPerBand;
    OnsetDetector* *onsetDetectors;
    int numMeters;
    Meter* *meters;
    
    bool bDisplayGui=false;
    
private:
    ofxPanel gui;
    void guiSetup();
    ofxFloatSlider RMSLP, SalienceLP, HarmonicComplexityLP, HfcLP;
    
    Flux fluxRMS, fluxSalience, fluxHfc, fluxHarmonicComplexity;
    
    void setValuePerBand();
    
    int bandWritePos=0;
    ofxAudioAnalyzer analyzer;
    int xPos=0;
    int id;


};
#endif /* Analyzer_hpp */
