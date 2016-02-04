//
//  Analyzer.cpp
//  example-spectrumOutput
//
//  Created by Jildert Viet on 15-01-16.
//
//

#include "Analyzer.hpp"
#include <iostream>

using namespace std;

Analyzer::Analyzer(){
    
}

Analyzer::Analyzer(int id, string title, int bufferSize, int sampleRate, int numBands, int bandSize){
    this->title = title; this->numBands = numBands; this->id = id; this->bandSize = bandSize; this->sampleRate = sampleRate; this->bufferSize = bufferSize;
    analyzer.setup(bufferSize, sampleRate);
    cutOffFreqs = new int[numBands];
    valuesPerBand = new valuePerBand[numBands];
    onsetDetectors = new OnsetDetector*[numBands];
    
    for(int i=0; i<numBands; i++){
        cutOffFreqs[i] = 0;
        onsetDetectors[i] = new OnsetDetector(1.3);
    }
    
    numMeters = 8+numBands;
    meters = new Meter*[numMeters];
    setCutOffFreqs(cutOffFreqs, numBands);
    meters[0] = new Meter(&HarmonicComplexity, "HarmonicComplex", ofVec2f(0,0));
    meters[1] = new Meter(&RMS, "RMS", ofVec2f(200,0));
    meters[2] = new Meter(&Hfc, "Hfc", ofVec2f(400,0));
    meters[3] = new Meter(&Salience, "Salience", ofVec2f(600,0));
    
    meters[4] = new Flux(&HarmonicComplexity, "fluxHarmonicComplexity", ofVec2f(0,300));
    meters[5] = new Flux(&RMS, "fluxRMS", ofVec2f(200,300));
    meters[6] = new Flux(&Hfc, "fluxHfc", ofVec2f(400,300));
    meters[7] = new Flux(&Salience, "fluxSalience", ofVec2f(600,300));
    
    for(int i=8; i<numMeters; i++){
        meters[i] = new Meter(&(valuesPerBand[i-8].RMS), "RMS", ofVec2f(i*100,0));
    }
    guiSetup();
}

void Analyzer::display(){
//    ((Flux*)meters[4])->setValue(HarmonicComplexity);
    for(int i=0; i<numMeters; i++){
        meters[i]->display();
    }
    if(bDisplayGui){
        ofSetColor(255);
        ofDrawRectangle(0,0,gui.getWidth(), gui.getHeight());
        gui.draw();
    }
}

void Analyzer::setCutOffFreqs(int *cutOffFreqs, int numBands){
    this->numBands = numBands;
    
    bands = new float*[numBands];
    for(int i=0; i<numBands; i++){
        bands[i] = new float[bandSize];
    }
    cutOffFreqs = new int[numBands];
    for(int i = 0; i<numBands; i++){
        this->cutOffFreqs[i] = cutOffFreqs[i];
    }
}

float Analyzer::interpolate(float v1, float v2, float division){
    return v1   -   ((v1-v2)/division);
}

void Analyzer::setValueInterpolated(float v, float division){
    value = interpolate(value, v, division);
}

void Analyzer::displayValueWithMeter(float value, ofVec2f loc, ofVec2f size, string name){
    ofSetColor(255);
    ofDrawBitmapString(name, ofVec2f(loc.x, loc.y+size.y+10));
    ofDrawRectangle(loc.x, loc.y, size.x, size.y);
    
    ofVec2f newLoc = ofVec2f(loc.x, loc.y+size.y-(size.y * value));
    
    ofVec2f newSize = ofVec2f(size.x, size.y * value);
    ofSetColor(0,200);
    ofDrawRectangle(loc.x, newLoc.y, size.x, newSize.y);
    ofSetColor(ofColor::red);
    ofDrawLine(loc.x, newLoc.y, loc.x+size.x, newLoc.y);
//    cout << value << endl;
}

void Analyzer::chopSpectrum(float *spectrum, int *cutoffFreqs, int numBands, float **bands){
    for(int i=0; i<numBands; i++){
        int startIndex, endIndex, width;
        
        startIndex = freqToBinIndex(cutoffFreqs[i-1]);
        if(i==0)
            startIndex =0;
        endIndex = freqToBinIndex(cutoffFreqs[i]);
        // So spectrum[513] will never be read?
        if(i==numBands-1)
            endIndex--;
        
        width = endIndex - startIndex;
        float value=0;
        for(int i=startIndex; i<endIndex; i++){
            float add = abs(ofMap(spectrum[i], log10(0.001), log10(1.0), 0.0, 1.0));
            if(ofInRange(add, 0.0, 1.0)) // So -inf doesn't fuck it all up
                value += add;
            //                cout<<"spectrumVal"<<spectrum[i]<<endl;
            //                    cout<<spectrum[i]<<endl;
        }
        
        //            cout<<"Start: " << startIndex<<" to End: "<<endIndex<<endl;;
        value /= width;
        bands[i][bandWritePos] = value;
        //            cout <<"Makes the value: " << i<<": "<<value<<endl;
    }
    if(bandWritePos++>=bandSize)
        bandWritePos = 0;
}

void Analyzer::setValuePerBand(){
    for(int i=0; i<numBands; i++){
        valuesPerBand[i].RMS = interpolate(valuesPerBand[i].RMS, bands[i][bandWritePos-1], RMSLP);
    }
}

void Analyzer::guiSetup(){
    gui.setup();
    gui.setDefaultWidth(400);
    gui.add(RMSLP.setup("RMSLP", 10, 1, 100));
    gui.add(SalienceLP.setup("SalienceLP", 10, 1, 100));
    gui.add(HarmonicComplexityLP.setup("HarmonicComplexityLP", 10, 1, 100));
    gui.add(HfcLP.setup("HfcLP", 10, 1, 100));
}





