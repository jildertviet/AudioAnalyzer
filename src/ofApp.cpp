#include "ofApp.h"
#define AUDIODEV    4
#define BANDWIDTH   32.f
#define SAMPLERATE  44100.f

// Use Meter-trigger bool for activating functions from visualizer... :)
// Record piezo samples... 

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1280, 800);
    ofSetFullscreen(false);
    ofBackground(0);
    ofSetBackgroundAuto(true);
    ofSetFrameRate(60);
    
    audioSetup();
    
    visualizer = new Visualizer();
    analyzer = new Analyzer(0, "Analyzer", bufferSize, SAMPLERATE, 4, 43);
    
    analyzer->cutOffFreqs[0] = 200; analyzer->cutOffFreqs[1] = 2000; analyzer->cutOffFreqs[2] = 5000; analyzer->cutOffFreqs[3] = SAMPLERATE/2.;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    visualizer->update();
    
    
//     Lines
//    if(analyzer->Hfc>0.5)
//        visualizer->verticalNoise();
//    if(analyzer->valuesPerBand[0].RMS>0.4)
//        visualizer->horizontalNoise();
//
////     Vlakken
//    if(analyzer->valuesPerBand[1].RMS>0.4){
//        visualizer->displayRandomQuarter();
//    }
    
    // VerticalBar
    if((analyzer->valuesPerBand[0].RMS)*(analyzer->HarmonicComplexity)>0.1){
        visualizer->displayVerticalBar();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    visualizer->display();
    if(bDisplayAnalyzer)
        analyzer->display();
}

//------------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++){
        output[i*nChannels] = buffer_1[i];
        output[(i*nChannels)+1] = buffer_1[i];
    }
}

//------------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    // Fill the buffer with incoming audio
    for (int i = 0; i < bufferSize; i++){
        buffer_1[i] = input[i*nChannels]*inputGain;
    }
    analyzer->process(buffer_1, bufferSize);
}

//--------------------------------------------------------------
void ofApp::exit(){
    soundStream.stop();
    soundStream.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 32:
            visualizer->horizontalNoise();
            visualizer->verticalNoise();
            break;
        case '1':
            visualizer->displayRandomQuarter();
            break;
        case 'g':
            analyzer->bDisplayGui = !analyzer->bDisplayGui;
            break;
        case 'a':
            bDisplayAnalyzer = !bDisplayAnalyzer;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::drawFreqBandTracks(){
    ofSetColor(0);
    for(int i=0; i<BANDWIDTH; i++){
        for(int j=0; j<freqBandTracksSize/BANDWIDTH; j++){
            ofDrawLine(j, ofGetWindowHeight()/BANDWIDTH*i, j, (ofGetWindowHeight()/BANDWIDTH*i)-(freqBandTracks[i+((j+1)*(int)BANDWIDTH)]*(ofGetWindowHeight()/BANDWIDTH)));
        }
//        cout << i << ": " << freqBandTracks[i+((0+1)*(int)BANDWIDTH)] << endl;
    }
}

//--------------------------------------------------------------
void ofApp::audioSetup(){
    bufferSize = 1024;

    int outChannels = 2;
    int inChannels = 1;
    int ticksPerBuffer = bufferSize/64;
    
    buffer_1 =  new float[bufferSize];
    freqBandTrackSize = 43*4;
    freqBandTracksSize = BANDWIDTH*freqBandTrackSize;
    freqBandTracks = new float[freqBandTracksSize]; // BPM is hier nog niet variabel, lengte is nu 4 seconden
    
    RMSValues = new float[(int)BANDWIDTH];
    FluxValues = new float[(int)BANDWIDTH];
    logSpectrum32 = new float[(int)BANDWIDTH];
    
    for(int i=0; i<freqBandTracksSize; i++)
        freqBandTracks[i] = 0;
    for(int i=0; i<BANDWIDTH; i++)
        RMSValues[i] = FluxValues[i] = 0; // Kan dit zo?
    for(int i = 0; i < bufferSize; i++)
        buffer_1[i]= 0;
    
    cout << "Audio devices:" <<endl; cout<< soundStream.getDeviceList() << endl;
    
    soundStream.setDeviceID(AUDIODEV);
    
    soundStream.setup(this, outChannels, inChannels, SAMPLERATE, bufferSize, ticksPerBuffer);
    
    spectrumSize = bufferSize/2 + 1;
    spectrum1 = new float[spectrumSize];
    for(int i = 0; i < spectrumSize; i++)
        spectrum1[i]= 0;
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for(int i=0; i<analyzer->numMeters; i++){
        analyzer->meters[i]->isMouseOnMeter(x, y);
    }
}



