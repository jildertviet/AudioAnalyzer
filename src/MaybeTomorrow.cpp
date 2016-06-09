//
//  MaybeTomorrow.cpp
//  Bas
//
//  Created by Jildert Viet on 25-04-16.
//
//

#include "MaybeTomorrow.hpp"

MaybeTomorrow::MaybeTomorrow(Visualizer* visualizer){
    songName = "MaybeTomorrow";
    cout << songName << endl;
    this->visualizer = visualizer;
    
    this->visualizer->makeAlphaBlackScreen();
    visualizer->setAlpha(255);
    
    bpm = 85;
    
//    for(int i=0; i<1; i++)
//        generateChorusMeshes();
}

void MaybeTomorrow::stop(){
//    for(int i=0; i<numMeshes; i++){
//        multiMesh[i]->active = true;
//    }
}

void MaybeTomorrow::keys(int key){
    switch (key) {
        case 'c':
            generateChorusMeshes();
            break;
            
            case 's':
            for(int i=0; i<30; i++)
                generateChorusMeshes();
            break;
            
        case 'x':{
            generateChorusMeshes();
            for(int i=0; i<numMeshes; i++){
                MultiMeshMaybeTomorrow* mesh = multiMesh[i];
                mesh->deleteWithFade(8000+ofRandom(5000),800);
            }
        }
            break;
            
        case 'b':
        {
        for(int i=0; i<numMeshes; i++)
            multiMesh[i]->bMoveHorizontal = true;
        }
        break;
            
        case 'z':{
            generateChorusMeshes();
            for(int i=0; i<numMeshes; i++){
                multiMesh[i]->bMoveVertical = true;
                multiMesh[i]->direction = ofVec2f(0,ofRandom(0.1, 1.0)/2.);
            }
        }
            break;
            case 'a':
            generateChorusMeshes();
            for(int i=0; i<numMeshes; i++){
                multiMesh[i]->bMoveVertical = true;
                multiMesh[i]->direction = ofVec2f(0,ofRandom(0.1, 1.0)/2.);
                multiMesh[i]->deleteWithFade(10000,1000);
            }
            break;
            
            
        case '1':{
            visualizer->horizontalNoise();
            Noise* noise = (Noise*)visualizer->startEvent->getLast();
            noise->localColor = ofColor(255);
        }
            break;
            
        case '2':{
            visualizer->verticalNoise();
            Noise* noise = (Noise*)visualizer->startEvent->getLast();
            noise->localColor = ofColor(255);
        }
            break;
            
        case '3':{
            visualizer->horizontalNoise();
            Noise* noise = (Noise*)getLast();
            noise->localColor = ofColor(255);
            noise->setEnvelope(100, 100, 3000);
        }
            
            break;
        
        default:
        break;
    }
}

void MaybeTomorrow::MidiFunc(ofxMidiMessage msg){
    if(msg.status == MIDI_CONTROL_CHANGE){
                if(msg.control == 1)
                    visualizer->setAlpha(ofMap(msg.value, 0, 127, 8, 255));
    }
    
    if(msg.status == 144){
        switch (msg.pitch) {
            case 36:
                keys('c');
                break;
            case 37:
                keys('s');
                break;
            case 38:
                keys('x');
                break;
            case 39:
                keys('z');
                break;
                
            case 40:
                keys('b');
                break;
            case 41:
                break;
            case 42:
                break;
            case 43:
                keys('a');
                break;
                
                
            case 44:
                keys('1');
                break;
            case 45:
                keys('2');
                break;
            case 46:
                keys('3');
                break;
                
            default:
                break;
        }
    }
}

void MaybeTomorrow::generateChorusMeshes(){
    numMeshes = 4;
    multiMesh = new MultiMeshMaybeTomorrow*[numMeshes];
    
    addEvent(new MultiMesh(4));
    multiMesh[0] = ((MultiMeshMaybeTomorrow*)getLast());
    
    addEvent(new MultiMeshMaybeTomorrow(5, ofFloatColor(0.6, 0.6, 0.6, 1)));
    multiMesh[1] = ((MultiMeshMaybeTomorrow*)getLast());
    
    addEvent(new MultiMeshMaybeTomorrow(6, ofFloatColor(0.97254901960784,0.7921568627451,0,1)));
    multiMesh[2] = ((MultiMeshMaybeTomorrow*)getLast());
    
    addEvent(new MultiMeshMaybeTomorrow(7, ofFloatColor(0.90980392156863,0.74901960784314,0.33725490196078, 1)));
    multiMesh[3] = ((MultiMeshMaybeTomorrow*)getLast());
    
    for(int i=0; i<numMeshes; i++){
        MultiMeshMaybeTomorrow* mesh = multiMesh[i];
        mesh->generateJildert();
        mesh->deleteWithFade(10000);
    }

}

void MaybeTomorrow::deleteChorusMeshes(){
    
}