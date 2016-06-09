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
//--------------------------------------------------------------
Analyzer::Analyzer(){
    
}

//--------------------------------------------------------------
Analyzer::Analyzer(ofBaseApp* baseApp, int bufferSize, int sampleRate){
    this->baseApp = baseApp;     this->sampleRate = sampleRate; this->bufferSize = bufferSize;
    audioSetup(baseApp, "Apple Inc.: Jildert"); // "Apple,  Inc.: Jildert" bij Luuk
    gui.setup();
    deviceSelector = new class deviceSelector(baseApp, &soundStream);
    analyzer.setup(bufferSize, sampleRate);
    
    float frequencies [3] = {0.2, 4.0, 9.0}; // Kan dit ook in de functie?
    setFilters(4, frequencies);
    
    numMeters = 9+4; meters = new Meter*[numMeters];
//    setCutOffFreqs(cutOffFreqs, numBands);
    
    meters[0] = new Meter("HarmonicComplex", ofVec2f(0,0), &HarmonicComplexityLP);
    meters[1] = new Meter("RMS", ofVec2f(150,0), &RMSLP);
    meters[2] = new Meter("Hfc", ofVec2f(300,0), &HfcLP);
    meters[3] = new Meter("Salience", ofVec2f(450,0), &SalienceLP);
    
    meters[4] = new FluxMeter("fluxHarmonicComplex", ofVec2f(0,300), &HarmonicComplexityLP);
    meters[5] = new FluxMeter("fluxRMS", ofVec2f(150,300), &RMSLP);
    meters[6] = new FluxMeter("fluxHfc", ofVec2f(300,300), &HfcLP);
    meters[7] = new FluxMeter("fluxSalience", ofVec2f(450,300), &SalienceLP);
    
    for(int i=8; i<numMeters-1; i++){
        meters[i] = new Meter("RMS_filt", ofVec2f((i-1)*100-100,0), &RMSLP);
    }
    
    meters[12] = new Meter("SelectedFreq", ofVec2f(ofGetWindowWidth()-230, 0), &SelectedBinLP);

    guiSetup();
    loadXmlValues();
    

    float spectrumSize = bufferSize/2 + 1;
    ofVec2f sizeTemp = ofVec2f(700,400);
    spectrumDisplay = new SpectrumDisplay(spectrumSize, ofGetWindowSize()-sizeTemp, sizeTemp);
}

//--------------------------------------------------------------
void Analyzer::display(){
    if(bDisplay){
        for(int i=0; i<numMeters; i++)
            meters[i]->display();
        for(int i=0; i<numMeters; i++)
            meters[i]->displayGlobalGui();
        
        if(bDisplayGui){
            ofSetColor(255);
            ofDrawRectangle(0,0,gui.getWidth(), gui.getHeight());
            gui.draw();
        }
        
        if(deviceSelector->bDisplay)
            deviceSelector->display();
        
        //PRESETS
        loadPresetButton->display(); savePresetButton->display();
        if(loadPresetButton->state) loadPresetGui.draw();
        if(savePresetButton->state) savePresetGui.draw();
        ofSetColor(255); ofDrawBitmapString(presetNames[selectedPreset], ofGetWindowWidth()-10, 150);
        
        for(int i=0; i<numMeters; i++){
            meters[i]->displayOscGui();
        }
        
        spectrumDisplay->display();
    }
}

//--------------------------------------------------------------
void Analyzer::update(){
    float* valuePointers[13] = {&HarmonicComplexity, &RMS, &Hfc, &Salience, &HarmonicComplexity, &RMS, &Hfc, &Salience, &(filters[0]->RMS), &(filters[1]->RMS), &(filters[2]->RMS), &(filters[3]->RMS), &SelectedBin};
    // Dit kan beter in de .hpp file
    
    // Waarom moet dit zo? :(
    meters[12]->value = spectrumDisplay->value;
    
    for(int i=0; i<numMeters; i++){
        meters[i]->value = *(valuePointers[i]);
        meters[i]->update();
    }
    
    
}

void Analyzer::process(float *buffer, int bufferSize){
    analyzer.analyze(buffer, bufferSize);
    
    RMS = analyzer.getRms();
    if(RMS==0) // Disables process() when there's no audio
        return;
    Salience = analyzer.getSalience();
    
    // Moet nog ge-limit worden :)
    HarmonicComplexity = analyzer.getSpectralComplex()/30.;
    if(HarmonicComplexity>1.0)  HarmonicComplexity = 1;
    Hfc = analyzer.getHfc()/300.;
    if(Hfc>1.0) Hfc = 1;
    
    //        chopSpectrum(analyzer.getSpectrum(), cutOffFreqs, numBands, bands);
    //        setValuePerBand(); // Toen ik nog met FFT filter werkte
    
    // Write audiodata to the filters (for the onset detection), and add to OnSetDetector history buffer
    writeFilterDataToBuffer(buffer, bufferSize);
    
    // Get RMS value of filtered band
    for(int i=0; i<numFilters; i++){
        analyzer.analyze(filteredBuffers[i], bufferSize);
        filters[i]->RMS = analyzer.getRms();
    }
    
    for(int i=0; i<numFilters-1; i++){
        //            onsetDetectors[i]->writeToHistoryBuffer(filteredBuffers[i], bufferSize);
        if(onsetDetectors[i]->checkIfBeat()){
            meters[8+i]->beat = true;
            //                cout << i << " BEAT!" << endl;
        } else{
            meters[8+i]->beat = false;
        }
        // Hier iets mee doen // OSC senden :)
    }
    
    
    // FFT
    spectrumDisplay->addSpectrum(analyzer.getSpectrum());
    SelectedBin = abs(spectrumDisplay->value);
//    SelectedBin = ofRandom(0.5);
    cout << abs(spectrumDisplay->value) << endl;
}








//--------------------------------------------------------------
void Analyzer::setCutOffFreqs(int *cutOffFreqs, int numBands){
//    this->numBands = numBands;
//    
//    bands = new float*[numBands];
//    for(int i=0; i<numBands; i++){
//        bands[i] = new float[bandSize];
//    }
//    cutOffFreqs = new int[numBands];
//    for(int i = 0; i<numBands; i++){
//        this->cutOffFreqs[i] = cutOffFreqs[i];
//    }
}

//--------------------------------------------------------------
float Analyzer::interpolate(float v1, float v2, float division){
    return v1   -   ((v1-v2)/division);
}

//--------------------------------------------------------------
void Analyzer::setValueInterpolated(float v, float division){
//    value = interpolate(value, v, division);
}

//--------------------------------------------------------------
void Analyzer::displayValueWithMeter(float value, ofVec2f loc, ofVec2f size, string name){
    ofSetColor(255);
    ofDrawBitmapString(name, ofVec2f(loc.x, loc.y+size.y+10));
    ofDrawRectangle(loc.x, loc.y, size.x, size.y);
    
    ofVec2f newLoc = ofVec2f(loc.x, loc.y+size.y-(size.y * value));
    
    ofVec2f newSize = ofVec2f(size.x, size.y * value);
    ofSetColor(0,200);
    ofDrawRectangle(loc.x, newLoc.y, size.x, newSize.y);
    ofSetColor(ofColor::red);
    ofDrawLine(loc.x, newLoc.y, loc.x+size.x, newLoc.y);
//    cout << value << endl;
}

//--------------------------------------------------------------
void Analyzer::chopSpectrum(float *spectrum, int *cutoffFreqs, int numBands, float **bands){
//    for(int i=0; i<numBands; i++){
//        int startIndex, endIndex, width;
//        
//        startIndex = freqToBinIndex(cutoffFreqs[i-1]);
//        if(i==0)
//            startIndex =0;
//        endIndex = freqToBinIndex(cutoffFreqs[i]);
//        // So spectrum[513] will never be read?
//        if(i==numBands-1)
//            endIndex--;
//        
//        width = endIndex - startIndex;
//        float value=0;
//        for(int i=startIndex; i<endIndex; i++){
//            float add = abs(ofMap(spectrum[i], log10(0.001), log10(1.0), 0.0, 1.0));
//            if(ofInRange(add, 0.0, 1.0)) // So -inf doesn't fuck it all up
//                value += add;
//            //                cout<<"spectrumVal"<<spectrum[i]<<endl;
//            //                    cout<<spectrum[i]<<endl;
//        }
//        
//        //            cout<<"Start: " << startIndex<<" to End: "<<endIndex<<endl;;
//        value /= width;
//        bands[i][bandWritePos] = value;
//        //            cout <<"Makes the value: " << i<<": "<<value<<endl;
//    }
//    if(bandWritePos++>=bandSize)
//        bandWritePos = 0;
}

//--------------------------------------------------------------
void Analyzer::setValuePerBand(){
//    for(int i=0; i<numBands; i++){
//        valuesPerBand[i].RMS = bands[i][bandWritePos];
//    }
}

//--------------------------------------------------------------
void Analyzer::guiSetup(){
    gui.setDefaultWidth(400);
    gui.add(RMSLP.setup("RMSLP", 10, 1, 100));
    gui.add(SalienceLP.setup("SalienceLP", 10, 1, 100));
    gui.add(HarmonicComplexityLP.setup("HarmonicComplexityLP", 10, 1, 100));
    gui.add(HfcLP.setup("HfcLP", 10, 1, 100));
    gui.add(SelectedBinLP.setup("SelectedBinLP", 10, 1, 100));
    
    presetSetup();
    
//    gui.add(oscPort.setup("oscPort:", 7000));
//    oscPort.setPosition(ofVec2f(ofGetWindowWidth()-200, 400));
}

void Analyzer::presetSetup(){
    loadPresetButton = new Button(ofVec2f(30,20), ofVec2f(ofGetWindowWidth()-40, 0), "Load");
    savePresetButton = new Button(ofVec2f(30,20), ofVec2f(ofGetWindowWidth()-40, 30), "Save");
    
    loadPresetGui.setup(); loadPresetGui.setPosition(loadPresetButton->loc);
    savePresetGui.setup(); savePresetGui.setPosition(savePresetButton->loc);
    for(int i=0; i<5; i++){
        loadPresetGui.add(loadButtons[i].setup(presetNames[i]));
        savePresetGui.add(saveButtons[i].setup(presetNames[i]));
    }
    // Kan dit ook anders? Met argumenten en for loops enzo?
    saveButtons[0].addListener(this, &Analyzer::savePresetButtonPressed1); loadButtons[0].addListener(this, &Analyzer::loadPresetButtonPressed1);
    saveButtons[1].addListener(this, &Analyzer::savePresetButtonPressed2); loadButtons[1].addListener(this, &Analyzer::loadPresetButtonPressed2);
    saveButtons[2].addListener(this, &Analyzer::savePresetButtonPressed3); loadButtons[2].addListener(this, &Analyzer::loadPresetButtonPressed3);
    saveButtons[3].addListener(this, &Analyzer::savePresetButtonPressed4); loadButtons[3].addListener(this, &Analyzer::loadPresetButtonPressed4);
    saveButtons[4].addListener(this, &Analyzer::savePresetButtonPressed5); loadButtons[4].addListener(this, &Analyzer::loadPresetButtonPressed5);
}

//--------------------------------------------------------------
void Analyzer::setFilters(int numFilters, float *frequencies){
    this->numFilters = numFilters;
    filters = new Filter*[numFilters]; onsetDetectors = new OnsetDetector*[numFilters]; filteredBuffers = new float*[numFilters];

    for(int i=0; i<numFilters; i++){
        filteredBuffers[i] = new float[bufferSize]; // Make buffers for filtered output
        onsetDetectors[i] = new OnsetDetector(1.3, true); // Make OnsetDetector
        onsetDetectors[i]->localBuffer = filteredBuffers[i]; // Link Local Buffer of OSD-tor to the buffers for the filtered output
        onsetDetectors[i]->localBufferSize = bufferSize;
        
        if(i==0){
            filters[i] = new Filter(LPF, 51, 44.1, frequencies[i]);
        } else{
//            cutOffFreqs[i-1] = (int)frequencies[i]*1000;
            if(i==(numFilters-1)){
                filters[i] = new Filter(HPF, 51, 44.1, frequencies[i-1]);
            } else{
                filters[i] = new Filter(BPF, 51, 44.1, frequencies[i-1], frequencies[i]);
            }
        }
    }    
}

//--------------------------------------------------------------
void Analyzer::writeFilterDataToBuffer(float *buffer, int bufferSize){
    for(int i=0; i<numFilters; i++){
        for(int j=0; j<bufferSize; j++){
            float value = filters[i]->do_sample(buffer[j]);
            onsetDetectors[i]->addValueToHisotryBuffer(value);
            filteredBuffers[i][j] = value;
        }
    }
}

//--------------------------------------------------------------
void Analyzer::loadXmlValues(){
    for(int i=0; i<numMeters; i++){
        meters[i]->outputOsc = "";
    }
    
    ofxXmlSettings settings;
    settings.loadFile("Preset"+presetNames[selectedPreset]+".xml");
    for(int i=0; i<numMeters; i++){
        // All meters
        for(int j=0; j<meters[i]->numToggles; j++){
            // All toggles
            string valueName = "settings:meter"+ofToString(i)+"toggle"+ofToString(j);
            meters[i]->toggles[j] = settings.getValue(valueName, 0); // Als bools niet werken, met integers proberen
            valueName = "settings:meter"+ofToString(i)+"gainslider";
            meters[i]->gain = settings.getValue(valueName, 0.f);
            valueName = "settings:meter"+ofToString(i)+"lowpassslider";
            meters[i]->lowPass = settings.getValue(valueName, 0.f);
        }
    }
}


//--------------------------------------------------------------
void Analyzer::saveXmlValues(){
    //lets clear everything on mouse pressed so we save just one stroke.
    globalXml.clear();
    
    ofxXmlSettings settings;
    string valueName;
    for(int i=0; i<numMeters; i++){
        // All meters
        for(int j=0; j<meters[i]->numToggles; j++){
            // All toggles
            valueName = "settings:meter"+ofToString(i)+"toggle"+ofToString(j);
            settings.setValue(valueName, meters[i]->toggles[j]); // Klopt getParameter()?
        }
        valueName = "settings:meter"+ofToString(i)+"gainslider";
        settings.setValue(valueName, meters[i]->gain);
        valueName = "settings:meter"+ofToString(i)+"lowpassslider";
        settings.setValue(valueName, meters[i]->lowPass);
    }
    settings.saveFile("Preset"+presetNames[selectedPreset]+".xml");
}

void Analyzer::audioSetup(ofBaseApp* baseApp, string device){
    int outChannels = 0;
    int inChannels = 2;
    int ticksPerBuffer = bufferSize/64;
    
    buffer =  new float[bufferSize];
    for(int i = 0; i < bufferSize; i++)
        buffer[i]= 0;
    
    soundStream.printDeviceList();
    bool audioDeviceFound = false;
//    soundStream.getDeviceList()[0]; // Is eerste device
    for(int i=0; i<soundStream.getDeviceList().size(); i++){
        cout << "Name: " << soundStream.getDeviceList()[i].name << endl;
        if(soundStream.getDeviceList()[i].name == device){
            cout << i << " is input called " << device << endl;
            soundStream.setDeviceID(i);
            outChannels = soundStream.getDeviceList()[i].outputChannels;
            inChannels = soundStream.getDeviceList()[i].inputChannels;
            audioDeviceFound = true;
        }
    }
    
    if(!audioDeviceFound){
        cout << "NOT FOUND!!!" << endl;
        return;
    }
    
    soundStream.setup(baseApp, outChannels, inChannels, (float)sampleRate, bufferSize, ticksPerBuffer);
    
    // DEVICE CHOOSE GUI
//    int numDevices = soundStream.getDeviceList().size();
//    deviceToggles = new ofxToggle[numDevices];
//    for(int i=0; i<numDevices; i++){
////            gui.add(deviceToggles[i].setup(soundStream.getDeviceList()[i].name, true));
//        gui.add(deviceToggles[i].setup(soundStream.getDeviceList()[i].name, false));
//        deviceToggles[i].addListener(this, &Analyzer::changeAudioDevice);
//        // changeAudioDevice checks which toggle is true, derives which device must be set, sets device :)
//    }
}

//void Analyzer::changeAudioDevice(bool & val){
//    // Set all toggles to false, and 'device' as true
//    int numDevices = soundStream.getDeviceList().size();
//    int device = 0;
//    for(int i=0; i<numDevices; i++){
//        if(deviceToggles[i])
//            device = i;
//    }
//    
//    if(soundStream.getSoundStream())
//        soundStream.stop(); // of close()?
//    
//
//    int outChannels = soundStream.getDeviceList()[device].outputChannels;
//    int inChannels = soundStream.getDeviceList()[device].inputChannels;
//    int ticksPerBuffer = bufferSize/64;
//    
//    buffer =  new float[bufferSize];
//    for(int i = 0; i < bufferSize; i++)
//        buffer[i]= 0;
//    
////    soundStream.setDeviceID(device);
//    soundStream.getDeviceList()[device].isDefaultInput;
//    soundStream.setup(baseApp, outChannels, inChannels, (float)sampleRate, bufferSize, ticksPerBuffer);
//    cout << "Selected " << soundStream.getDeviceList()[device].name << "as sound in/out" << endl;
//    
//    for(int i=0; i<numDevices; i++){
//        deviceToggles[i] = false;
//    }
//}

void Analyzer::analyzerKeys(int key){
    switch(key){
        case 'o':
            bDisplayGui = !bDisplayGui;
            break;
        case 'a':
            bDisplay = !bDisplay;
            break;
        case 'd':
            deviceSelector->bDisplay = !deviceSelector->bDisplay;
            break;
    }
}

void Analyzer::mouseFunc(int x, int y){
    spectrumDisplay->mouseFunc(x, y);
    for(int i=0; i<numMeters; i++){
        meters[i]->isMouseOnMeter(x, y);
        meters[i]->globalGuiToggle->checkIfMouseIsOnButton(x, y);
        meters[i]->oscGuiToggle->checkIfMouseIsOnButton(x, y);
    }
    loadPresetButton->checkIfMouseIsOnButton(x,y);
    savePresetButton->checkIfMouseIsOnButton(x,y);
}
