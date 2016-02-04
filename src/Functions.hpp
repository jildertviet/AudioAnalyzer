//
//  Functions.hpp
//  example-spectrumOutput
//
//  Created by Jildert Viet on 21-01-16.
//
//

#ifndef Functions_hpp
#define Functions_hpp

#include <stdio.h>
#include "ofMain.h"

class Functions{
public:
    Functions();
    void convertToLogSpectrum(float *spectrum, float *newSpectrum, int bandWidth, int spectrumSize);
    void addToFreqBandTracks(float *logSpectrum, float *arrayToWrite, int bandWidth, int freqBandTracksSize);
    void testFunction(float *array);
    
    // Unused
    void calculateMostActiveBandFlux(float tracks[], float arrayToWrite[]);
    void calculateMostActiveBandRMS(float tracks[], float arrayToWrite[]);

    
    
    int writePosFreqBandTracks=0;
};

#endif /* Functions_hpp */
