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
//#include "ofxAudioAnalyzer.h"

class Analyzer{
public:
    Analyzer();
    Analyzer(int *numAnalyzers, int id, string title);
    void display();
    float value;
    string title;
private:
    int* numAnalyzers;
//    ofxAudioAnalyzer analyzer;
    int xPos=0;
    int id;

};
#endif /* Analyzer_hpp */
