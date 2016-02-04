//
//  OnsetDetector.hpp
//  Paul
//
//  Created by Jildert Viet on 02-02-16.
//
//

#ifndef OnsetDetector_hpp
#define OnsetDetector_hpp

#include <stdio.h>
#include <math.h>
#include "ofMain.h"

class OnsetDetector{
public:
    OnsetDetector();
    float bufLength, localEnergy=0, historyEnergy=0, C;
    int writePosLocal=0, readPosLocal, writePosHistory=0, readPosHistory;
    float *historyBuffer;
    float *localBuffer;
    bool beatDetected;
    float c_value=1.3;
    
    
    OnsetDetector(float c_value){
        this->c_value = c_value;
        
        cout << "OnsetDetector made" << endl;
        
        // Allocating buffers: (1 for local energy (1024samples), and 1 for history energy (44032 samples))
        historyBuffer = new float[44032];
        for(int i=0; i<44032; i++)
            historyBuffer [0];
        localBuffer = new float[1024];
        for(int i=0; i<1024; i++)
            localBuffer[i] = 0;
    }
    
    bool process(float *buffer, int numSamples){
        // storing some values, because that seems to be more efficient...
        float value, output;
        
        // Fill buffers
        for (int i=0; i<numSamples; ++i){
            value = buffer[i];
            
            // Write to local buffer of 1024 samples
            localBuffer[writePosLocal] = value;
            
            // Write to history buffer of 44032 samples
            historyBuffer[writePosHistory] = value;

        }
        
        //Only execute if a new buffer of 1024 samples is filled (instead of the 64 samples, the audio rate of SuperCollider)
        if(writePosLocal == 0){
            // Calculate average local energy
            localEnergy = 0;
            for(int i=0; i<1024; i++){
                localEnergy += (localBuffer[i]*localBuffer[i]);
            }
            
            // Calculate history energy
            historyEnergy = 0;
            for(int i=0; i<44032; i++){
                historyEnergy += (historyBuffer[i]*historyBuffer[i]);
            }
            historyEnergy *= (1024.0/44032.0);
            
            // Compare local energy to history energy
            if(localEnergy > (c_value * historyEnergy)){
                if(beatDetected != 1)
                    beatDetected = true;
            } else{
                if(beatDetected != 0)
                    beatDetected =  false;
            }
            return beatDetected;
        }
        if(writePosLocal+=numSamples >= 1024)   writePosLocal = 0;
        if(writePosHistory+=numSamples >= 44032)    writePosHistory = 0;
    }
};

#endif /* OnsetDetector_hpp */