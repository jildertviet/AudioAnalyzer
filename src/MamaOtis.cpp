//
//  MamaOtis.cpp
//  Bas
//
//  Created by Jildert Viet on 24-04-16.
//
//

#include "MamaOtis.hpp"

MamaOtis::MamaOtis(Visualizer* visualizer){
    songName = "MamaOtis";
    cout << songName << endl;
    this->visualizer = visualizer;
    this->visualizer->makeAlphaBlackScreen();
    visualizer->setAlpha(50);
//    bpm = 85;
    
    makeThings1();
//    functionOne();
}

void MamaOtis::stop(){
    for(int i=0; i<vormen.size(); i++){
        Vorm* vorm = vormen[i];
        vorm->active = true;
        vorm->setEnvelope(1, 1, 3000);
        vorm->envelope->triggerEnv();
    }
    
    
//    for(int i=0; i<triangles.size(); i++){
//        VormCustom* triangle = triangles[i];
//        triangle->active = true;
//        triangle->setEnvelope(1, 1, 3000);
//        triangle->envelope->triggerEnv();
//    }
//    if(cube1){
//        cube1->active = true;
//        cube1->setEnvelope(1, 1, 3000);
//        cube1->envelope->triggerEnv();
//    }
//    
//    if(cube2){
//        cube2->active = true;
//        cube2->setEnvelope(1, 1, 3000);
//        cube2->envelope->triggerEnv();
//    }
}

void MamaOtis::keys(int key){
    switch(key){
            case '1':
            functionOne();
            break;
            
            case '3':
            makeThings2();
            break;
            
            case '7':
            thingsWithCircle();
            break;
            
            
        case '5':
            makeCube1();
            break;
            
            case '6':
            makeCube2();
            break;
            
            case '4':
            showParticlesVormen();
            break;
            
            case '8':
            makeCube1(); makeCube2();
            fall();
            break;
            
            case '9':
            finalVorm();
            break;

    }
}

void MamaOtis::MidiFunc(ofxMidiMessage msg){
    if(msg.status == MIDI_CONTROL_CHANGE){
        if(msg.control == 1)
            visualizer->setAlpha(ofMap(msg.value, 0, 127, 8, 255));
    }
    
    if(msg.status == 144){
        switch (msg.pitch) {
            case 36:
                functionOne();
                break;
            case 37:
                makeThings2();
                break;
            case 38:
                showParticlesVormen();
                break;
            case 39:
                break;
                
            case 40:
                makeCube1();
                break;
            case 41:
                makeCube2();
                break;
            case 42:
                break;
            case 43:
                
                break;
                
                
            case 44:
                makeCube1(); makeCube2();
                fall();
                break;
                
                
            case 48:
                finalVorm();
                break;
            case 51:
//                visualizer->alphaScreen->gradientColor = ofColor(255,0,0);
                visualizer->alphaScreen->gradientColor = ofColor(255-20,46-20,45-20);
                visualizer->alphaScreen->bGradient = !(visualizer->alphaScreen->bGradient);
                break;
            default:
                break;
        }
    }
}

void MamaOtis::makeVorm(int numSides, int sideDivision, float radius, ofVec2f center, Boolean on_destination){
    addEvent(new Vorm(numSides, sideDivision, radius, center, on_destination));
    vormen.push_back( (Vorm*)getLast() );
}

void MamaOtis::functionOne(){
    static int index = 0;
    if(index++>=(vormen.size()-1))
        index = 0;
    
    Vorm* vormTemp = vormen[(index + 1) % (vormen.size())];
    Vorm* prevVorm = vormen[index];
    
    prevVorm->switchConnectableness();
//    prevVorm->formVorm();
    
    vormTemp->switchConnectableness();
    vormTemp->rotateCoordinates(20, 1);
}

void MamaOtis::functionTwo(){
    static int index = 0;
    if(index++>=vormen.size())
        index = 0;
    Vorm* vormTemp = vormen[(index + 1) % vormen.size()];
    Vorm* prevVorm = vormen[index];
    
    prevVorm->changeRadius(vormen[(index + 4 + (int)ofRandom(2)) % vormen.size()]->radius);
    vormen[(index + 4 + (int)ofRandom(2)) % vormen.size()]->particles_visible = ofRandom(0,1);
}

void MamaOtis::changeSpeed(){
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->particles_visible = true;
        vormen[i]->change_maxspeed(2.0+(i/12.));
    }
}

void MamaOtis::makeThings1(){
    for(int i=0; i<10; i++){ // IMPLODES
        makeVorm(6,5+(i),150+(i*20),ofGetWindowSize()/2., false);
//        vormen[i]->switchConnectableness();
        vormen[i]->particles_visible = false;
        vormen[i]->change_maxspeed(2.0-(i/10.));
        vormen[i]->formVorm();
        vormen[i]->switchConnectableness();
        vormen[i]->lijnmax = 50*50;
    }
        vormen[1]->switchConnectableness();
 }

void MamaOtis::makeThings2(){
    triangles.clear();
    float num = ofGetWindowWidth()/40;
    for(int i=0; i<num; i++){ // BAR
        int r = ofGetWindowHeight()/2.-50;
        ofVec2f newLoc = (ofGetWindowSize()/2.)+ofVec2f(cos(i/num*TWO_PI)*r, sin(i/num*TWO_PI)*r);
        addEvent(new VormCustom(3, 2, 50, newLoc, true));
        VormCustom* triangle = ((VormCustom*)getLast());
        
        triangles.push_back(triangle);
        if(i!=0){
            triangle->addConnectedVorm(lastTriangle);
        }
        triangle->vectorPointer = &triangles;
        lastTriangle = triangle;
        triangle->formVorm();
//        triangle->switchConnectableness();
        triangle->particles_visible = false;
        triangle->alphaAdd = 0;
        triangle->active = true; triangle->setEnvelope(10, 100, 2000); triangle->envelope->trigger = true;
    }
    triangles.front()->addConnectedVorm(lastTriangle);
}

void MamaOtis::makeCube1(){
    addEvent(new Vorm(4, 10, 110, ofVec2f(125,ofGetWindowHeight()/2.), true));
    Vorm* vorm = ((Vorm*)getLast());
    cube1 = vorm;
    vorm->formVorm();
    //    vorm->switchConnectableness();
    vorm->particles_visible = false;
    vorm->change_maxspeed(0.5);
    vorm->lijnmax = 50*50;
    
    vorm->changeRadius(vorm->radius+100);
    vorm->rotateCoordinates(vorm->particles_amount-10, 1);
    vorm->active = true; vorm->setEnvelope(10, 200, 4000); vorm->envelope->triggerEnv();
}

void MamaOtis::makeCube2(){
    addEvent(new Vorm(4, 10, 110, ofVec2f(ofGetWindowWidth()-125,ofGetWindowHeight()/2.), true));
    Vorm* vorm = ((Vorm*)getLast());
    cube2 = vorm;
    vorm->formVorm();
//    vorm->switchConnectableness();
    vorm->particles_visible = false;
    vorm->change_maxspeed(0.5);
    vorm->lijnmax = 50*50;
    
    vorm->changeRadius(vorm->radius+100);
    vorm->rotateCoordinates(10, 1);
    vorm->active = true; vorm->setEnvelope(10, 200, 4000); vorm->envelope->triggerEnv();
}


void MamaOtis::showParticlesVormen(){
    for(int i=0; i<vormen.size(); i++){
        vormen[i]->particles_visible = !vormen[i]->particles_visible;
    }
}

void MamaOtis::fall(){
    for(int i=0; i<vormen.size(); i++){
        Vorm* vorm = vormen[i];
        vorm->changeCenter(vorm->center + ofVec2f(0,1800));
        vorm->change_maxspeed(0.5, 2.0);
        vorm->formVorm();
        if(vorm->isConnectable() == false)
            vorm->switchConnectableness();
    }
    for(int i=0; i<triangles.size(); i++){
        VormCustom* triangle = triangles[i];
        triangle->changeCenter(triangle->center + ofVec2f(0,1800));
        triangle->change_maxspeed(0.5, 2.0);
        triangle->formVorm();
    }
    if(cube1){
        cube1->changeCenter(cube1->center + ofVec2f(0,1800));
        cube1->change_maxspeed(0.5, 2.0);
        cube1->formVorm();
    }
    
    if(cube2){
        cube2->changeCenter(cube2->center + ofVec2f(0,1800));
        cube2->change_maxspeed(0.5, 2.0);
        cube2->formVorm();
    }
}

void MamaOtis::thingsWithCircle(){
    for(int i=0; i<triangles.size(); i++){
        triangles[i]->switchConnectableness();
    }
}

void MamaOtis::finalVorm(){
    addEvent(new Vorm(6, 10, 110*3, ofGetWindowSize()/2., true));
    Vorm* vorm = ((Vorm*)getLast());
//    cube2 = vorm;
    vorm->formVorm();
    //    vorm->switchConnectableness();
    vorm->particles_visible = false;
    vorm->change_maxspeed(0.6);
    vorm->lijnmax = 50*50;
    
    vorm->changeRadius(vorm->radius/2.);
    vorm->rotateCoordinates(vorm->particles_amount/3., 1);
    vorm->active = true; vorm->setEnvelope(10, 200, 8000); vorm->envelope->triggerEnv();
}

/*
                for(int i=0; i<17; i++){
                    makeVorm(6, 3, 100, ofVec2f(screencenter.x + (cos(i)*50), 0+(i*50)));
                    formVorm(numVorms-1);
                }
                for(int i=0; i<44; i++){
                    Vorm* vorm = vormen[i];
                    vorm->particles_visible = false;
                }
            }
 
                for(int i=44; i<44+17; i++){
                    ofVec2f new_center = ofVec2f(screencenter.x + (wavetable->getNextValueWithOffset((i-44)*(1.0/17.0)*2)*50), vormen[i]->center.y+50);
 
                    if(vormen[i]->center.y > ofGetWindowHeight()-50){
                        vormen[i]->particles_visible = true;
                        new_center.y = 0;
                    }
                    cout << new_center << endl;
                    vormen[i]->changeCenter(new_center);
                }
            }
                
                
                Vorm* vorm = (*(vormpointer+42));
                if(vorm->isConnectable() == false)
                    vorm->switchConnectableness();
                vorm = (*(vormpointer+42));
                if(vorm->isConnectable() == false)
                    vorm->switchConnectableness();

            }
 
                for(int i=44; i<44+17; i++){
                    ofVec2f new_center = ofVec2f(screencenter.x + (wavetable->getNextValueWithOffset((i-44)*(1.0/17.0)*2)*50), vormen[i]->center.y+50);
 
 
                    if(vormen[i]->center.y > ofGetWindowHeight()-50){
                        vormen[i]->particles_visible = true;
                        new_center.y = 0;
                    }
                    cout << new_center << endl;
                    vormen[i]->changeCenter(new_center);
                }
            }

                
                for(int i=0; i<numVorms; i++){
                    vormen[i]->particles_visible = false;
                    vormen[i]->change_state_of_particles(0);
                }

*/
