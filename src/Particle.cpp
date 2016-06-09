//
//  Particle.cpp
//  Shapes
//
//  Created by Jildert Viet on 18-02-15.
//
//

#include "Particle.h"

void Particle::Init(Boolean loc){
    if(loc)
        location = ofVec2f(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
    direction = ofVec2f(   ((int)ofRandom(-8,8)) *0.25,  ((int)ofRandom(-8, 8))*0.25   );
    velocity = ofVec2f(0,0);
    topspeed = ofRandom(2.)+1.;
    state = 0;
    noise_max = 5.5;
    noise_modulo = 20;
}

Particle::Particle(ofVec2f *pointer_, int index_, int vorm_index_){
    vorm_index = vorm_index_;
    index = index_;
    destination = (pointer_+index);
    Init(true);
}

Particle::Particle(ofVec2f *pointer_, int index_, int vorm_index_, Boolean start_loc){
    Init(false);
    vorm_index = vorm_index_;
    index = index_;
    destination = (pointer_+index);

    if(start_loc){
        int input = ofRandom(2);
        switch(input){
            case 0:
                location = ofVec2f(((int)ofRandom(2))*ofGetWindowWidth(),ofRandom(ofGetWindowHeight()));
                break;
            case 1:
                location = ofVec2f(ofRandom(ofGetWindowWidth()),((int)ofRandom(2))*ofGetWindowHeight());
                break;
        }
    } else{
        location = *destination;
    }
}

Particle::Particle(ofVec2f destination_, int vorm_index_){
    Init(true);
    index = 99;
    vorm_index = vorm_index_;
    destination2 = destination_;
    destination = &destination2;
}

void Particle::display(){
    ofSetColor(color);
    ofDrawCircle(location,r);
    if(bubbling)
        bubble(20+(ofNoise(index+ofGetFrameNum()/100.0)*20),0.5, index, ofColor(255,120));
}

void Particle::test(){
    cout << "I exist!" << endl;
}


void Particle::update(){
    checkEdges();
    switch(state){ // Free
            
        case 0:
            
            direction.normalize();
            acceleration = direction * 0.5;
            velocity += acceleration;
//            if(add_noise)
//            velocity += ofVec2f(ofRandom(-noise_max, noise_max), ofRandom(-noise_max, noise_max));
            velocity.limit(topspeed);
            location += velocity;
            break;
            
        case 1: // In formation
            ofVec2f dir2 = *destination - location;
            dir2.normalize();
            dir2 *= 0.4;
            
            acceleration = dir2;
            velocity += acceleration;
            if(add_noise){
                location += ofVec2f(ofRandom(-noise_max, noise_max), ofRandom(-noise_max, noise_max));
                add_noise = false;
            }
            
            velocity.limit(topspeed);
            location += velocity;
            
            
            // So it doesn't vibrate when in formation
            float distance = location.distance(*destination);
            if(distance < 10)
                velocity *= 0.001;
            break;
            
    }
}

int Particle::checkEdges(){
    if (location.x > ofGetWindowWidth()) {
        velocity.x *= -1;
        direction.x *= -1;
        return 1;
    }
    if(location.x < 0){
        velocity.x *= -1;
        direction.x *= -1;
        return 2;
    }
    if (location.y > ofGetWindowHeight()) {
        direction.y *= -1;
        velocity.y *= -1;
        return 3;
    }
    if(location.y < 0){
        direction.y *= -1;
        velocity.y *= -1;
        return 4;
    }
    else{
        return 0;
    }
}

void Particle::changeMode(){
    state = !state;
    if(state)
        direction = ofVec2f(   ((int)ofRandom(-8,8)) *0.25,  ((int)ofRandom(-8, 8))*0.25   );
}

void Particle::bubble(int rad, float speed, int offset, ofColor color){
    ofNoFill();
    ofSetColor(color);
    float r = sin((ofGetFrameNum()+offset)*(speed/10.))*rad;
    ofDrawCircle(location, r);
    ofFill();
}

void Particle::locationIsDestination(){
    location = *destination;
}

void Particle::connectParticle(Particle* p){
//    if(checkIfConnected(p)){
        connectedParticles.push_back(p);
    p->connectedParticles.push_back(this);
//    }
}

bool Particle::checkIfConnected(Particle* p){
    for(int i=0; i<connectedParticles.size(); i++){
        if(this==p){
            return true;
        }
    }
    return false;
}

void Particle::clearConnectedParticles(){
    connectedParticles.clear();
}