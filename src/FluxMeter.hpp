//
//  FluxMeter.hpp
//  Audio_met_Osc
//
//  Created by Jildert Viet on 27-01-16.
//
//

#ifndef FluxMeter_hpp
#define FluxMeter_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Meter.hpp"

class FluxMeter: public Meter{
public:
    FluxMeter();
    FluxMeter(string name, ofVec2f loc, ofxFloatSlider *LP);
    void addValueToBuffer(float value){
        buffer[writePos] = value;
        if(writePos++>=bufferSize)  writePos = 0;
    }
    float *toBuffer;
    
    float getFlux(){
        // Get average, check how big the difference per value is...
        
        // Gets normalized (Sort of... ?)
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
    
    void specificFunction(){
        addValueToBuffer(value);
        value = getFlux();
    }
    
    float flux=0;
    int bufferSize=128, writePos=0;
private:
    float *buffer;
};
#endif /* FluxMeter_hpp */
