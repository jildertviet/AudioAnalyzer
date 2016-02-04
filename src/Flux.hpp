//
//  Flux.hpp
//  Audio_met_Osc
//
//  Created by Jildert Viet on 27-01-16.
//
//

#ifndef Flux_hpp
#define Flux_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Meter.hpp"

class Flux: public Meter{
public:
    Flux();
    Flux(float *toBuffer, string name, ofVec2f loc){
        buffer = new float[bufferSize];
        this->name = name; this->loc = loc; this->toBuffer = toBuffer;
        size = ofVec2f(50,200);
        value = &flux;
    }
    void setValue(float *value){
        buffer[writePos] = *value;
        if(writePos++>=bufferSize)  writePos = 0;
    }
    float *toBuffer;
    
    void getFlux(){
        float val1=0, val2=0;
        for(int i=0; i<bufferSize-1; i++){
            if(i%(int)(bufferSize/4)<(int)(bufferSize/8)){
                val1 += buffer[i]*buffer[i];
            } else{
                val2 += buffer[i]*buffer[i];
            }
        }
        val1/=(bufferSize/2.);
//        cout << "Val1: " << val1<<endl;
        val2/=(bufferSize/2.);
//        cout << abs(val1-val2) << endl;
        flux = interpolate(flux, abs(val1-val2)*2, 5);
    }
    
    void specificFunction(){
        setValue(toBuffer);
        getFlux();
    }
    
    float flux=0;
    int bufferSize=64, writePos=0;
private:
    float *buffer;
};
#endif /* Flux_hpp */
