//
//  Functies.cpp
//  example-spectrumOutput
//
//  Created by Jildert Viet on 21-01-16.
//
//

#include "Functions.hpp"
//--------------------------------------------------------------
Functions::Functions(){
    cout << "Functions object made" << endl;
}

//--------------------------------------------------------------
void Functions::convertToLogSpectrum(float *spectrum, float *newSpectrum, int bandWidth, int spectrumSize){
    for(int i=0; i<bandWidth; i++){
        newSpectrum[i] = 0;
        int start = (int)(((i/(float)bandWidth)*(i/(float)bandWidth))*(spectrumSize));
        int end = (int)((((i+1)/(float)bandWidth)*((i+1)/(float)bandWidth))*(spectrumSize));
        int width = end - start;
        float value = 0;
        
        for(int i=start; i<end; i++){
            value += ofMap(spectrum[i], log10(0.001), log10(1.0), 0.0, 1.0);
        }
        value/=width;
        newSpectrum[i] = value;
    }
}

//--------------------------------------------------------------
void Functions::addToFreqBandTracks(float *logSpectrum, float *arrayToWrite, int bandWidth, int freqBandTracksSize){
    for(int i=0; i<bandWidth; i++){
        if(logSpectrum[i]>0){
            arrayToWrite[i+writePosFreqBandTracks] = logSpectrum[i];
        } else{
            arrayToWrite[i+writePosFreqBandTracks] = 0;
        }
    }
    if((writePosFreqBandTracks+=bandWidth)>=freqBandTracksSize)
        writePosFreqBandTracks = 0;
}

void Functions::testFunction(float *array){
    cout << "Second element is: " << array[1] << endl;
}

//--------------------------------------------------------------
//void Functions::calculateMostActiveBandRMS(float tracks[], float arrayToWrite[]){
//    float value = 0;
//    for(int i=0; i<BANDWIDTH; i++){
//        for(int j=0; j<freqBandTracksSize/BANDWIDTH; j++){
//            value += pow(tracks[i+((j+1)*(int)BANDWIDTH)], 2); // Kwadraat van elke value bij elkaar optellen
//            cout << i << ": " << tracks[i+((j+1)*(int)BANDWIDTH)] << endl;
//            cout << "Value: " << value << endl;
//        }
//        //        arrayToWrite[i] = sqrt(value); // Is dit de RMS? Van 1 track in dat geval
//    }
//}


