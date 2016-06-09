//
//  Lilium.hpp
//  Bas
//
//  Created by Jildert Viet on 18-03-16.
//
//

#ifndef Lilium_hpp
#define Lilium_hpp

#include <stdio.h>
#include "Visualizer.hpp"
#include "ofMain.h"
#include "Song.hpp"
#include "ofxOpenCv.h"
#include "Image.hpp"

class Lilium: public Song{
public:
    Lilium(Visualizer* visualizer);
};

#endif /* Lilium_hpp */
