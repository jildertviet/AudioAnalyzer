//
//  Image.hpp
//  Bas
//
//  Created by Jildert Viet on 18-03-16.
//
//

#ifndef Image_hpp
#define Image_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Event.hpp"

class Image: public Event{
public:
    Image(string filename, ofVec3f loc=ofVec2f(0,0));
    ofImage image;
    ofImage backGround;
    ofMesh mesh;
    
    void display();
//    void update();
    void specificFunction();
    
    void createFullScreenCopy();
    void meshSetup();
    
    bool fillScreen = false; bool drawImage=true; bool drawMesh = 0;
    
    void loadImage(string path);
};
#endif /* Image_hpp */
