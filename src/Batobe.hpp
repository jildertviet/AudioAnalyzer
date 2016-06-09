//
//  Batobe.hpp
//  Paul
//
//  Created by Jildert Viet on 14-02-16.
//
//

#ifndef Batobe_hpp
#define Batobe_hpp

#include <stdio.h>
#include "Song.hpp"
#include "Fem.hpp"
#include "Lilium.hpp"
#include "TimeForYou.hpp"
#include "Visualizer.hpp"
#include "Juncture.hpp"
#include "Faith.hpp"
#include "Ghost.hpp"
#include "MaybeTomorrow.hpp"
#include "MamaOtis.hpp"
#include "TeachMe.hpp"
#include "NoDank.hpp"
#include "BatobeOSC.hpp"

#include "ofxOsc.h"

class Batobe{
public:
    Batobe();
    
    
    void update();
    
    Visualizer visualizer;
    Song* song = nullptr;
    BatobeOSC* batobeOSC;
    Image* image = nullptr;
    
    ofxOscReceiver receiver;
    
    void keys(int key);
    void setBrightness(int key);
};
#endif /* Batobe_hpp */
