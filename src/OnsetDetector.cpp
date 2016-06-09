//
//  OnsetDetector.cpp
//  Paul
//
//  Created by Jildert Viet on 02-02-16.
//
//

#include "OnsetDetector.hpp"

OnsetDetector::OnsetDetector(){
    
}

bool OnsetDetector::checkIfBeat(){
    // storing some values, because that seems to be more efficient...

    // Calculate average local energy
    localEnergy = 0;
    for(int i=0; i<localBufferSize; i++){
        localEnergy += (localBuffer[i]*localBuffer[i]);
    }
    
    // Calculate history energy
    historyEnergy = 0;
    for(int i=0; i<historyBufferSize; i++){
        historyEnergy += (historyBuffer[i]*historyBuffer[i]);
    }
    historyEnergy *= ((float)localBufferSize/(float)historyBufferSize);
//    cout << "History Energy: " << historyEnergy << endl;
    
    float v = abs(getFlux(historyBuffer, historyBufferSize));

//    cout << "V: " << v << endl;
    c_value = (-0.0025714*v)+1.5142857;
    
    // Compare local energy to history energy
    if(localEnergy > (c_value * historyEnergy)){
        if(!beatDetected)
            beatDetected = true;
//        cout <<"Beat, localE: " << localEnergy << ", historyEnergy*C: " << c_value*historyEnergy << ", c: " << c_value << " " << this << endl;
            } else{
                if(beatDetected)
                    beatDetected =  false;
                    }
    return beatDetected;
}
