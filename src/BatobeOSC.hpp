//
//  BatobeOSC.hpp
//  Bas
//
//  Created by Jildert Viet on 09-05-16.
//
//

#ifndef BatobeOSC_hpp
#define BatobeOSC_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "Event.hpp"

class BatobeOSC: public Event{
public:
    BatobeOSC();
    
    ofTrueTypeFont font;
    void display();
    void specificFunction();
    
    void moveToCenter();
    bool bMoveToCenter = false;
    
    void countDown();
    void startCountDown();
    bool bCountDown = false;
    int counter = 10;
    int counts = 5;
    int time;
    
    void receiveOsc();
    ofxOscReceiver receiver;
    ofxOscMessage message;
    void setFontSize(int size);
    
    int fontSize = 140;
    
    
    void reset();
    void processMsg(ofxOscMessage message);
    
    void displayResult();
    bool bDisplayResult = false;
    
    void showPercentage();
    bool bShowPercentage = false;
    
    float numVoices = 0 ;
    float pro = 0;
    bool bQuestionOpen = false;
    
    string firstPercentage="0";
    string secondPercentage="0";
    string thirdPercentage="0";
    string ans1;
    string ans2;
    string ans3;
    string title; 
    ofTrueTypeFont question, answer, percentage;
    
    int ansY = 300;
    int percentageY = 300+50;
    
    void displayTempScore();
    bool bDisplayTempScore = false;
    Envelope* ansEnv;
    
    void displayQ();
    bool bDisplayQ = false;
    Envelope* questionEnv;
    
    int titleY = 200;
    
    void displayOptions();
    void displayPercentage();
    Envelope* resultEnv;
    
    void displayChoose();
    bool bDisplayChoose = false;
    void doDisplayChoose();
    
    void displayWhoAreYou();
    bool bDisplayWhoAreYou = false;
    void doDisplayChoose(string id);
    string id = "0";
    Envelope* whoAreYouEnv;
    
    int barAlpha = 100;
    
    bool bDiplayYouChose = false;
    void doDisplayYouChose(string title);
    void displayYouChose();
    string youChose = " ";
};
#endif /* BatobeOSC_hpp */
