//
//  MyThread.cpp
//  AudioAnalyzer
//
//  Created by Jildert Viet on 22-01-16.
//
//

#include "MyThread.hpp"
using namespace std;

//--------------------------------------------------------------
void MyThread::calculateMostActiveBandFlux(){
    vector<Value> spectrumValues(bandWidth);
    float value = 0;
    for(int i=0; i<bandWidth; i++){
        for(int j=0; j<freqBandTrackSize; j++){
            value += freqBandTracks[i+((j+0)*bandWidth)];
            //            cout << i << " " << j << endl;
        }
        value/=freqBandTrackSize;
        spectrumValues[i].value = value;
        spectrumValues[i].index = i;
    }
    cout << "Calculated average values of the spectrum " << ofGetTimestampString() << endl;
    sort(spectrumValues.begin(), spectrumValues.end(), this->sortByValue);
        cout << "Ordered the values" << endl;
//        for (vector<int>::size_type i = 0; i != spectrumValues.size(); ++i)
        for (int i = spectrumValues.size()-1; i>=0; i--)
            cout << spectrumValues[i].index << " ";
        cout << endl;
}

//--------------------------------------------------------------
void MyThread::searchPeaks(){
    // values moeten nog genormalized worden...
    vector<Value> spectrumValues(bandWidth);
    vector<Value> spectrumValuesSubtracted(bandWidth-2);
    float value = 0;
    for(int i=0; i<bandWidth; i++){
        for(int j=0; j<freqBandTrackSize; j++){
            value += freqBandTracks[i+((j+0)*bandWidth)];
        }
        value/=freqBandTrackSize;
        spectrumValues[i].value = value;
        spectrumValues[i].index = i;
        // 32-average values, not searched for peaks yet.
    }
    for(int i=0; i<bandWidth-2; i++){
        float val = spectrumValues[i+1].value;
        float valLeft = abs(val-spectrumValues[i-1].value);
        float valRight = abs(val-spectrumValues[i+1].value);
        val/=val; valLeft/=val; valRight/=val;
        spectrumValuesSubtracted[i].value = valLeft + valRight;
        spectrumValuesSubtracted[i].index = i;
    }
    sort(spectrumValuesSubtracted.begin(), spectrumValuesSubtracted.end(), this->sortByValue);
    for (int i = spectrumValuesSubtracted.size()-1; i>=0; i--)
        cout << spectrumValuesSubtracted[i].index << " ";
    cout << endl;
}




