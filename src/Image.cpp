//
//  Image.cpp
//  Bas
//
//  Created by Jildert Viet on 18-03-16.
//
//

#include "Image.hpp"

Image::Image(string filename, ofVec3f loc){
    this->loc = loc;
    type = "Image"; returnType();
    image.load(filename);
//    image.mirror(true, false);
    cout << image.getImageType() << endl;
//    image.setImageType(OF_IMAGE_COLOR_ALPHA);
    size = ofVec2f(image.getWidth(), image.getHeight());
    loc = ofVec2f(0,0);
    
    meshSetup();
//    createFullScreenCopy();
}

void Image::display(){
    ofSetColor(255);
    if(fillScreen)
        backGround.draw(loc);
    if(drawImage)
        image.draw(loc);
    if(drawMesh)
        mesh.draw();
}

void Image::specificFunction(){
}

void Image::createFullScreenCopy(){
    backGround.allocate(ofGetWindowWidth(), ofGetWindowHeight(), image.getImageType());
    
    int numChannels = image.getPixels().getNumChannels();
    for(int w=0; w<backGround.getWidth(); w++){
        for(int h=0; h<backGround.getHeight(); h++){
            for(int channels=0; channels<numChannels; channels++){
                backGround.getPixels()[numChannels*(w+(h*backGround.getWidth()))+channels] =
                image.getPixels()[numChannels*((w%(int)image.getWidth())+((int)((h%(int)image.getHeight())*image.getWidth())))+channels];
            }
        }
    }
    backGround.update();
}

void Image::meshSetup(){
    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    mesh.addVertex(loc);
    mesh.addVertex(loc+ofVec2f(100,0));
    mesh.addVertex(loc+ofVec2f(0,100));
}

void Image::loadImage(string path){
    image.clear();
    if(image.load(path))
        cout << "Image " << path << " loaded" << endl;
    image.update();
    size = ofVec2f(image.getWidth(), image.getHeight());
}