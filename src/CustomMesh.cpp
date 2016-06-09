//
//  CustomMesh.cpp
//  Bas
//
//  Created by Jildert Viet on 01-05-16.
//
//

#include "CustomMesh.hpp"

CustomMesh::CustomMesh(){
    type = "CustomMesh"; returnType();
    active = false;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    colors[0] = ofColor(255,0,200,100);
    envelope = new Envelope(200,0,200);
}

void CustomMesh::display(){
    ofSetColor(colors[0]);
    mesh.draw();
    //        if(bAddMirror){
    //            ofPushMatrix();
    //            ofTranslate(ofGetWindowWidth(), 0);
    //            ofRotateX(180);
    //            mesh.draw();
    //            ofPopMatrix();
    //        }
}

void CustomMesh::specificFunction(){
    if(bMoveRandomPoint){
        doMoveRandomPoint();
    }
}

void CustomMesh::moveRandomPoint(){
    pointToMove = ofRandom(mesh.getNumVertices());
    pointsToMove.push_back(pointToMove);
    locToMove.push_back(mesh.getVertex(pointToMove));
    envelopes.push_back(new Envelope(100,0,200));
    envelopes.back()->trigger = true;
    
    ofVec2f directionTemp;
    int index = ofRandom(4);
    switch (index) {
        case 0:
            directionTemp = ofVec2f(1,0);
            break;
        case 1:
            directionTemp = ofVec2f(-1,0);
            break;
        case 2:
            directionTemp = ofVec2f(0,1);
            break;
        case 3:
            directionTemp = ofVec2f(0,-1);
            break;
            
        default:
            break;
    }
    direction.push_back(directionTemp);
    
    bMoveRandomPoint = true;
}

void CustomMesh::doMoveRandomPoint(){
    for(int i=0; i<pointsToMove.size(); i++){
        ofVec2f newLoc;
        newLoc = locToMove[i];
        
        newLoc += (envelopes[i]->process()*100*direction[i]);
        
        mesh.setVertex(pointsToMove[i], newLoc);
        if(envelopes[i]->done){
            envelopes.erase(envelopes.begin()+i);
            locToMove.erase(locToMove.begin()+i);
            pointsToMove.erase(pointsToMove.begin()+i);
            direction.erase(direction.begin()+i);
        }

    }
}