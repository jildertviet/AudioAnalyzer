#include "ofApp.h"

#define AUDIODEV    2
#define BANDWIDTH   32.f
#define SAMPLERATE  44100.f
#define BUFSIZE 256
#define FRAMERATE   60
#define kAUDIOANALYZER  1
#define kPAUL   0
#define kBATOBE 0
#define MUTE    0

//--------------------------------------------------------------
void ofApp::setup(){
    // OF
    ofSetWindowShape(1280, 800);
//    ofSetWindowShape(100, 100);
    ofSetFullscreen(false);
    ofBackground(0);
    ofSetBackgroundAuto(true);
    ofSetFrameRate(FRAMERATE);
    
    // GUI
    gui.setup();
    gui.add(inputGain.setup("inputGain", 1., 0., 10.));
    
    // VISUALIZER
    
    if(kBATOBE){
        batobe = new Batobe;
        visualizer = &(batobe->visualizer);
    }
    if(kPAUL)
        visualizer = new Visualizer;
    
//    visualizer->displayVorm(true);
//    bDisplayVisualizer = true;
    
    // ANALYZER
    if(kAUDIOANALYZER){
        // AUDIO
        analyzer = new Analyzer(this, BUFSIZE, SAMPLERATE);
        analyzer->bDisplay = true;
    }
//    float frequencies [3] = {0.2, 4.0, 9.0}; // Kan dit ook in de functie?
//    analyzer->setFilters(3, frequencies);
    
    if(kPAUL) paul = new Paul(analyzer, nullptr);
//    if(kPAUL) paul = new Paul(nullptr, visualizer);
}

//--------------------------------------------------------------
void ofApp::update(){
    // OF
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    // Paul
    if(kPAUL)
        paul->update();
    
    if(kBATOBE)
        batobe->update();
    
    // VISUALIZER
    if(visualizer)
        visualizer->update();
    
    // ANALYZER
    if(kAUDIOANALYZER)
        analyzer->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    if(bDisplayVisualizer){
        if(visualizer)
            visualizer->display();
    }
    if(kAUDIOANALYZER)
        analyzer->display();
    if(bDisplayGui)
        gui.draw();
    if(kPAUL)
        paul->display();
}

//------------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    if(kAUDIOANALYZER){
        if(!MUTE && analyzer){
            for (int i = 0; i < bufferSize; i++){
                float val;
        //        val = analyzer->filteredBuffers[3][i];
                val = analyzer->buffer[i];
                output[i*nChannels] = val;
                output[(i*nChannels)+1] = val;
            }
        }
    }
}

//------------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    if(kAUDIOANALYZER){
        for (int i = 0; i < bufferSize; i++){
            if(analyzer)
                analyzer->buffer[i] = input[i*nChannels]*inputGain;
        }
        if(analyzer)
            analyzer->process(analyzer->buffer, BUFSIZE);
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    if(kAUDIOANALYZER)
        delete analyzer;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
//        case 32:
////            if(visualizer){
////                visualizer->horizontalNoise();
////                visualizer->verticalNoise();
////            }
//            break;
//        case 'v':
//            bDisplayVisualizer = !bDisplayVisualizer;
//            break;
//        case 'q':
//            bDisplayGui = !bDisplayGui;
//            break;
//
//        case 's':
//            if(kAUDIOANALYZER)
//                analyzer->saveXmlValues();
//            break;
    }
    if(kAUDIOANALYZER)
        analyzer->analyzerKeys(key);
    
    if(kPAUL)
        paul->keys(key);
    
    if(kBATOBE)
        batobe->keys(key);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(kAUDIOANALYZER){
        analyzer->mouseFunc(x,y);
    }
}



