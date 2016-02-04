//
//  MyThread.hpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 22-01-16.
//
//

#ifndef MyThread_hpp
#define MyThread_hpp

#include <stdio.h>
#include <iostream>
#include "ofMain.h"
#include <algorithm>
#include <vector>
#include <string>

class MyThread : public ofThread {
private:
    void threadedFunction() {
        while(isThreadRunning()) {
            ofSleepMillis(1000);
            searchPeaks();
        }
    }
    struct Value {int index; float value;};
    static bool sortByValue(const Value &lhs, const Value &rhs){ return lhs.value < rhs.value;};
public:
    float *freqBandTracks;
    int bandWidth;
    int freqBandTrackSize;
    void calculateMostActiveBandFlux();
    void searchPeaks();
};
#endif /* MyThread_hpp */
