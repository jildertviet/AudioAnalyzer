//
//  CustomMesh.hpp
//  Bas
//
//  Created by Jildert Viet on 01-05-16.
//
//

#ifndef CustomMesh_hpp
#define CustomMesh_hpp

#include <stdio.h>
#include "Event.hpp"
#include "Envelope.h"

class CustomMesh: public Event{
public:
    CustomMesh();
    ofMesh mesh;
    void display();
//    bool bAddMirror = true;
    void specificFunction();
    
    
    
    bool bMoveRandomPoint = false;
    void moveRandomPoint();
    void doMoveRandomPoint();
    int pointToMove = 0;
    
    vector<Envelope*> envelopes;
    vector<int> pointsToMove;
    vector<ofVec2f> locToMove;
    vector<ofVec2f> direction;
};
#endif /* CustomMesh_hpp */
