//
//  MaybeTomorrow.hpp
//  Bas
//
//  Created by Jildert Viet on 25-04-16.
//
//

#ifndef MaybeTomorrow_hpp
#define MaybeTomorrow_hpp

#include <stdio.h>
#include "Song.hpp"
#include "Visualizer.hpp"
#include "ofMain.h"
#include "MultiMeshMaybeTomorrow.hpp"

class MaybeTomorrow: public Song{
public:
    MaybeTomorrow(Visualizer* visualizer);
    void keys(int key);
    int numMeshes=0;
    MultiMeshMaybeTomorrow** multiMesh;
    void stop();
    
//    void generateVerseMeshes(); void deleteVerseMeshes();
    void generateChorusMeshes(); void deleteChorusMeshes();
    
//    void start(); bool bIsStarted = false;
//    void changeOneMultiMesh();
    
    void MidiFunc(ofxMidiMessage msg);
    
};
#endif /* MaybeTomorrow_hpp */
