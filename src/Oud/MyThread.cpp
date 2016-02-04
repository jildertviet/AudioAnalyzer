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
