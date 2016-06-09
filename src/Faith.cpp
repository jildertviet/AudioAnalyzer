//
//  Faith.cpp
//  Bas
//
//  Created by Jildert Viet on 18-04-16.
//
//

#include "Faith.hpp"


Faith::Faith(Visualizer* visualizer){
    songName = "Faith";
    cout << songName << endl;
    this->visualizer = visualizer;
    
    
//    
//    visualizer->gradientColor = ofColor(69, 173, 168, 10);
//    visualizer->gradientAlpha = 10;
//    visualizer->bGradientBackGround = true;
    

    this->visualizer->makeAlphaBlackScreen();
    visualizer->alphaScreen->bGradient = true;
//    int alpha = 10;
    visualizer->alphaScreen->gradientColor = ofColor(255,0,0);
    
    visualizer->setAlpha(1001);
    bpm = 110;
    
    makeCube();
//    makeVerticalParticleLine(0, 5, ofGetWindowWidth(), 0.9, 1.0);
    

    
    addEvent(new VideoPlayer("Animatie_noaudiotest.mov"));
    videoPlayer = (VideoPlayer*)getLast();
    
    addEvent(new VideoPlayer("Janefondatest.mov"));
    videoPlayer2 = (VideoPlayer*)getLast();

}

void Faith::stop(){
    visualizer->alphaScreen->bGradient = false;
//    if(videoPlayer)
//        videoPlayer->active = true;
    
    // Cube niet deleten, ... ???
//    if(cube)
//        cube->active = true;
    
    
    
    // Bij deleten cube moeten wel alle lines weg zijn...
}

void Faith::MidiFunc(ofxMidiMessage msg){
    if(msg.status == MIDI_CONTROL_CHANGE){
                if(msg.control == 1)
                    visualizer->setAlpha(ofMap(msg.value, 0, 127, 8, 255));
    }
    
    if(msg.status == 144){
        switch (msg.pitch) {
            case 36:
                makeVerticalParticleLine(0, 5, ofGetWindowWidth(), 0.9, 1.0);
                break;
            case 37:
                makeVerticalLineConnectedToCube();
                break;
            case 38:
                
                break;
            case 39:
                
                break;
                
            case 40:
                cube->mirror();
                break;
            case 41:
                cube->change_state_of_particles(0);
                break;
            case 42:
                cube->formVorm();
                break;
                
                
            case 44:
                visualizer->bMirror = !visualizer->bMirror;
                break;
            case 45:
                visualizer->bAddMirror = !visualizer->bAddMirror;
                break;
            case 47:
                // Video 1
                videoPlayer->play();
//                videoPlayer->active = true;
                videoPlayer->setEnvelope(1, (36)*1000, 100);
                videoPlayer->envelope->triggerEnv();
                break;
                
            case 48:
                visualizer->alphaScreen->gradientColor = ofFloatColor(0.90980392156863,0.74901960784314,0.33725490196078, 1);
                visualizer->alphaScreen->bGradient = true;
                break;
            case 49:
                visualizer->alphaScreen->gradientColor = ofColor(69, 173, 168);
                visualizer->alphaScreen->bGradient = true;
                break;
            case 51:
                videoPlayer2->play();
//                videoPlayer2->active = true;
                videoPlayer2->setEnvelope(1, (60+47)*1000-10000, 10000);
                videoPlayer2->envelope->triggerEnv();
                break;
            case 50:
                videoPlayer2->setEnvelope(1,1,5000);
                videoPlayer->setEnvelope(1,1,5000);
                break;
                
            default:
                break;
        }
    }
}

void Faith::makeVerticalParticleLine(int x, int amount, int destX, float speedMin, float speedMax){
    addEvent(new VormCustom(2, amount, ofGetWindowHeight(), ofVec2f(0,ofGetWindowHeight()/2.), true));
    VormCustom* line = ((VormCustom*)getLast());

    line->particles_visible = false;
    line->change_maxspeed(speedMin, speedMax);
    line->makeVertLine(x);
    line->instantFormVorm();
    line->lijnmax = (ofGetWindowHeight()/7.)*(ofGetWindowHeight()/7.);
    line->formVorm();
    line->changeCenter(ofVec2f(ofGetWindowWidth()+100, ofGetWindowHeight()/2.));
    line->active = true;
    line->endTime = ofGetElapsedTimeMillis()+(60000); // 60 sec lifetime
    line->lineWidth = 2;
    line->alphaAdd = 200;
    line->envelope->active = false;
    line->deleteWhenOutOfSight = true;
    line->envelope->active = false;
}

void Faith::makeVerticalLineConnectedToCube(){
    makeVerticalParticleLine(0, 5, ofGetWindowWidth(), 0.9, 1.0);
    VormCustom* line = ((VormCustom*)getLast());
    line->addConnectedVorm(cube);
    line->envelope->active = false;
//    line->connectNonRecursive = true;
    
    
    
    for(char i=0; i<lastLines.size(); i++){
        line->addConnectedVorm(lastLines[i]);
    }
    rememberLine(line);
    line->vectorPointer = &lastLines;
}

void Faith::keys(int key){
    switch(key){
        case '1':
            makeVerticalParticleLine(0, 5, ofGetWindowWidth(), 0.9, 1.0);
        break;
        case 'b':
            makeVerticalLineConnectedToCube();
        break;
        case '3':
            cube->mirror();
        break;
        case '4':
            cube->formVorm();
        break;
        case '5':
            cube->change_state_of_particles(0);
            break;
            
        case '6':
            visualizer->bAddMirror = !visualizer->bAddMirror;
            break;
            
        case '7':
            visualizer->bMirror = !visualizer->bMirror;
            break;
    }
}

void Faith::makeCube(){
    addEvent(new VormCustom(4, 4, 400, ofGetWindowSize()/2., true));
    cube = ((VormCustom*)getLast());
//    cube->instantFormVorm();
    cube->formVorm();
    cube->particles_visible = false;
}

void Faith::connectLine(VormCustom* line){
    if(lastLine){
        lastLine->addConnectedVorm(line);
    }
    lastLine = line;
}

void Faith::rememberLine(VormCustom* line){
    if(lastLines.size()<1){
        lastLines.push_back(line);
    } else{
        lastLines.insert(lastLines.begin(), line);
        lastLines.pop_back();
    }
}