//
//  deviceSelector.cpp
//  Paul
//
//  Created by Jildert Viet on 04-03-16.
//
//

#include "deviceSelector.hpp"

deviceSelector::deviceSelector(ofBaseApp* baseApp, ofSoundStream* soundStream, int sampleRate, int bufferSize, int ticksPerBufferDivision){
    this->soundStream = soundStream; this->baseApp = baseApp; this->sampleRate = sampleRate; this->bufferSize = bufferSize; this->ticksPerBuffer = bufferSize / ticksPerBufferDivision;
    gui.setup();
    numDevices = soundStream->getDeviceList().size();
    names = new ofxLabel[numDevices];
    for(int i=0; i<numDevices; i++)
        gui.add(names[i].setup(soundStream->getDeviceList()[i].name));
    gui.add(deviceIndex.setup("deviceIndex", 0, 0, numDevices));
    gui.add(select.setup("SelectInput"));
    select.addListener(this, &deviceSelector::selectFunction);
}

void deviceSelector::display(){
    if(bDisplay)
        gui.draw();
}

void deviceSelector::selectFunction(){
    ofSoundDevice device = soundStream->getDeviceList()[deviceIndex];
    int inChannels = device.inputChannels;
    int outChannels = device.outputChannels;
    int sampleRateTemp = device.sampleRates[0];
    soundStream->stop();
    soundStream->setDeviceID(deviceIndex);
    soundStream->start();
//    device.isDefaultInput;
//    soundStream->setup(baseApp, outChannels, inChannels, sampleRate, bufferSize, ticksPerBuffer);
    // Close and open SoundStream!?
}