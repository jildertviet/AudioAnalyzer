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

Analyzer::Analyzer(int *numAnalyzers, int id, string title){
    this->numAnalyzers = numAnalyzers;
    this->id = id;
    this->title = title;
//    cout << *numAnalyzers << endl;
}

void Analyzer::display(){

    xPos++;
    if(xPos>ofGetWindowWidth())
        xPos=0;
    
    int windowWidth = ofGetWindowHeight()/(*numAnalyzers);
    int lowBorder = ofGetWindowHeight()/(*numAnalyzers)*(id+1);
    int highBorder = ofGetWindowHeight()/(*numAnalyzers)*(id);;
    ofSetColor(255);
    ofDrawLine(xPos, lowBorder, xPos, highBorder);
    ofSetColor(0, 200);
    ofDrawLine(xPos, lowBorder, xPos, lowBorder-(value*windowWidth));
    ofSetColor(255, 0, 0);
    ofDrawBitmapString(title, 0, lowBorder-0);
}

