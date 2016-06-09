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
    
    int localBufferSize=1024;
    int historyBufferSize=44032;
    float rate=1.;
    float bufLength, localEnergy=0, historyEnergy=0, C;
    int writePosLocal=0, readPosLocal, writePosHistory=0, readPosHistory;
    float *historyBuffer;
    float *localBuffer;
    bool beatDetected;
    float c_value=1.3;
    
    
    OnsetDetector(float c_value, bool withExternalBuffer=false){
        // Normal audio rate = 1, adding a value to the buffer per audio sample
        // When you use FFT, every [FFT-size] samples, there will be one value, so the rate will be 512
        
//        cout<<"LocalBufferSize: " << localBufferSize <<endl;
        
        this->c_value = c_value;
        
//        cout << "OnsetDetector made" << this << endl;
        
        // Allocating buffers: (1 for local energy (1024samples), and 1 for history energy (44032 samples))
        historyBuffer = new float[historyBufferSize];
        for(int i=0; i<historyBufferSize; i++)
            historyBuffer [0];
        
        if(!withExternalBuffer){
            localBuffer = new float[localBufferSize];
            for(int i=0; i<localBufferSize; i++)
                localBuffer[i] = 0;
        }
    }
    
    bool checkIfBeat();
    
    float getFlux(float *buffer, int bufferSize){
        float average=0;
        for(int i=0; i<bufferSize; i++){
            average+=buffer[i];
        }
        average/=(float)bufferSize;
        
        float flux=0;
        for(int i=0; i<bufferSize; i++){
            flux+=(abs(average-buffer[i]));
        }
        flux/=(float)bufferSize;
        return flux;
    }
    
    void addValue(float value){
        if(writePosLocal >= localBufferSize)
            writePosLocal = 0;
        if(writePosHistory >= historyBufferSize)
            writePosHistory = 0;
        
        // Fill buffers
        // Write to local buffer of 1024 samples
        localBuffer[writePosLocal++] = value;

        // Write to history buffer of 44032 samples
        historyBuffer[writePosHistory++] = value;
    }
    
    void addValueToHisotryBuffer(float value){
        if(writePosHistory >= historyBufferSize)
            writePosHistory = 0;
        
        // Write to history buffer of 44032 samples
        historyBuffer[writePosHistory++] = value;
    }
    
    void writeToHistoryBuffer(float *buffer, int bufferSize){
        for(int i=0; i<bufferSize; i++){
            historyBuffer[i] = buffer[i];
        }
        if(writePosHistory >= historyBufferSize){
            writePosHistory = 0;
        } else{
            writePosHistory += bufferSize;
        }
    }
};

#endif /* OnsetDetector_hpp */