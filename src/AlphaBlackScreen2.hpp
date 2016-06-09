//
//  AlphaBlackScreen.hpp
//  Paul
//
//  Created by Jildert Viet on 14-02-16.
//
//

#ifndef AlphaBlackScreen_hpp
#define AlphaBlackScreen_hpp

#include <stdio.h>
#include "Event.hpp"

class AlphaBlackScreen: public Event{
public:
    AlphaBlackScreen();
    AlphaBlackScreen(bool hasAlphaBlending);
    ~AlphaBlackScreen();
    void display();

    void specificFunction();
    
private:
    bool alphaIs255 = false;
    bool hasAlphaBlending = true;
};
#endif /* AlphaBlackScreen_hpp */
