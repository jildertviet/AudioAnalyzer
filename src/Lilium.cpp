//
//  Lilium.cpp
//  Bas
//
//  Created by Jildert Viet on 18-03-16.
//
//

#include "Lilium.hpp"

Lilium::Lilium(Visualizer* visualizer){
    songName = "Lilium";
    this->visualizer = visualizer;
    visualizer->startEvent->addEvent(new Image("Schoonhoven-02.jpg"));
//    visualizer->startEvent->addEvent(new Bar());
}

