//
//  BatobeOSC.cpp
//  Bas
//
//  Created by Jildert Viet on 09-05-16.
//
//

#include "BatobeOSC.hpp"

BatobeOSC::BatobeOSC(){
    type = "BatobeOSC";
    returnType();
    ofTrueTypeFont::setGlobalDpi(72);
    
    font.load("BebasNeue.otf", fontSize, true, true);
    question.load("BebasNeue.otf", 150, true, true);
    answer.load("BebasNeue.otf", 50, true, true);
    percentage.load("BebasNeue.otf", 40, true, true);
    
    font.setLineHeight(18.0f);
    font.setLetterSpacing(1.037);
    
    speed = 1;
    colors = new ofColor[1];
    colors[0] = ofColor(255);
    loc = ofVec2f(0,0);
    
    receiver.setup(57110);
    ansEnv = new Envelope(50,2000,4000);
    questionEnv = new Envelope(50,1000000, 3000); // 1000 s :)
    resultEnv = new Envelope(100,5000, 500);
    whoAreYouEnv = new Envelope(200,5000,5000);
    
    
    
//    doDisplayChoose("44");
}

void BatobeOSC::display(){
    ofSetColor(colors[0]);
    ofSetColor(ofColor(255));
//    ofDrawRectangle(0, 0, 300, 300);
//    ofSetColor(ofColor(255,0,0));
//    font.drawString("Batobe", loc.x,loc.y+fontSize);
    
    displayYouChose();
    
    
    displayChoose();
    displayWhoAreYou();
    
    displayQ();
    displayTempScore();
    
    countDown();
    displayResult();
}

void BatobeOSC::specificFunction(){
    receiveOsc();
    if(envelope->active){
        colors[0].a = 255*envelope->process();
    }
    moveToCenter();
}

void BatobeOSC::moveToCenter(){
    direction = loc-ofGetWindowSize()/2.;
    direction.normalize();
    if(bMoveToCenter){
        if(loc.x != ofGetWindowWidth()/2.){
            loc.x += speed * direction.x;
        }
        if(loc.y != ofGetWindowHeight()/2.){
            loc.y += speed * direction.y;
        }
        
    }
}

void BatobeOSC::receiveOsc(){
    while(receiver.hasWaitingMessages()){
        // get the next message
        cout << "Msg" << endl;
//        startCountDown();
        ofxOscMessage m;
        receiver.getNextMessage(m);
        processMsg(m);
    }
}

void BatobeOSC::countDown(){
    if(bCountDown){
        if(ofGetElapsedTimeMillis() > time + 1000*counts){
            // Longer than 5 sec active;
            bCountDown = false;
            
            bDisplayResult = true;
            resultEnv->setShape(100,5000, 500);
            resultEnv->triggerEnv();
            
            bShowPercentage = false;
            bQuestionOpen = false;
            envelope->setShape(1, 2000, 1);
            envelope->triggerEnv();

            time = ofGetElapsedTimeMillis();
            return;
        }
        ofSetColor(255,200);
        counter = counts - ((int)(ofGetElapsedTimeMillis() - time)/1000.);
        cout << counter + 1 << endl;
        string content = ofToString(counter);
        ofRectangle space = font.getStringBoundingBox(content, 0, 0);
        font.drawString(content, ofGetWindowWidth()/2.-(space.getWidth()/2.), ofGetWindowHeight()/2.+(space.getHeight()/2.));
    }
}

void BatobeOSC::startCountDown(){
    time = ofGetElapsedTimeMillis();
    bCountDown = true;
    envelope->setShape(1, counts*1000, 1);
    envelope->triggerEnv();
}

void BatobeOSC::setFontSize(int size){
    fontSize = size;
    font.load("BebasNeue.otf", size, true, true);
}

void BatobeOSC::processMsg(ofxOscMessage message){
    cout << "0 / Title: " << message.getArgAsString(0) << endl;
    cout << "1 / Ans1: " << message.getArgAsString(1) << endl;
    cout << "2 / Ans2: " << message.getArgAsString(2) << endl;
    cout << "3 / Ans3: " << message.getArgAsString(3) << endl;
    cout << "4 / %1: " << message.getArgAsString(4) << endl;
    cout << "5 / %2: " << message.getArgAsString(5) << endl;
    cout << "6 / %3: " << message.getArgAsString(6) << endl;
    cout << "7 / selected: " << message.getArgAsString(7) << endl;
    cout << "8 / running: " << message.getArgAsString(8) << endl;
    
    if(message.getArgAsString(7)!="1000" && message.getArgAsString(0)=="nil"){
        doDisplayChoose(message.getArgAsString(7));
    }
    
    
    if(message.getArgAsString(0)=="nil"){
        cout << "ASDJASDJASDJASD" << endl;
        return;
    }
    
    if(message.getArgAsString(8)=="0"){ // Running is false (question closed)
        if(bQuestionOpen){
            if(message.getArgAsString(7)=="1000"){
                bQuestionOpen = false;
                cout << "Running is false" << endl;
                if(!bCountDown){
                    startCountDown();
                    questionEnv->setShape(1, 1, 5000); questionEnv->triggerEnv();
                }
                return;
            } else{ // Question met ID is closed
                // Show result
                questionEnv->setShape(1, 1, 400); questionEnv->triggerEnv();
                ansEnv->setShape(1,1,1); ansEnv->triggerEnv();
                
                bDisplayResult = true;
                resultEnv->setShape(100,2000, 500);
                resultEnv->triggerEnv();
                
//                bShowPercentage = false;
                bQuestionOpen = false;
                envelope->setShape(1, 1, 1);
                envelope->triggerEnv();
                
                time = ofGetElapsedTimeMillis();
                return;
            }
        }
        if(!bQuestionOpen){
            bQuestionOpen = true;
            cout << "Display somethinge" << endl;
            title = message.getArgAsString(0);
            ans1 = message.getArgAsString(1);
            ans2 = message.getArgAsString(2);
            ans3 = message.getArgAsString(3);
            firstPercentage = message.getArgAsString(4);
            secondPercentage = message.getArgAsString(5);
            thirdPercentage = message.getArgAsString(6);
            if(firstPercentage=="0" && secondPercentage=="0" && thirdPercentage=="0"){
                // Question
                if(bDisplayQ == false){
                    questionEnv->setShape(1, 100000, 5000);
                    questionEnv->triggerEnv();
//                    if(whoAreYouEnv->active)
//                        whoAreYouEnv->setShape(1, 1, 200);
                }
                bDisplayQ = true;
                
                
                //            bDisplayTempScore = true;
                //            ansEnv->triggerEnv();
                
            } else{ // Answer
                bDisplayTempScore = true;
                ansEnv->setShape(50,2000,4000);
                ansEnv->triggerEnv();
            }
        }
            
        
    }
    if(message.getArgAsString(8) == "1"){ // Running
        bQuestionOpen = true;
        cout << "Display somethinge" << endl;
        title = message.getArgAsString(0);
        ans1 = message.getArgAsString(1);
        ans2 = message.getArgAsString(2);
        ans3 = message.getArgAsString(3);
        firstPercentage = message.getArgAsString(4);
        secondPercentage = message.getArgAsString(5);
        thirdPercentage = message.getArgAsString(6);
        if(firstPercentage=="0" && secondPercentage=="0" && thirdPercentage=="0"){
            // Question
            if(bDisplayQ == false){
                questionEnv->setShape(1, 100000, 5000);
                questionEnv->triggerEnv();
                if(whoAreYouEnv->active)
                    whoAreYouEnv->setShape(1, 1, 200);
            }
            bDisplayQ = true;
            
            
//            bDisplayTempScore = true;
//            ansEnv->triggerEnv();
            
        } else{ // Answer
            bDisplayTempScore = true;
            ansEnv->setShape(50,2000,4000);
            ansEnv->triggerEnv();
        }
        
        if(message.getArgAsString(7)!="1000"){ // Anser @ q with id
            bDisplayTempScore = true;
            if(message.getArgAsString(4)=="0" && message.getArgAsString(5)=="0" && message.getArgAsString(6)=="0"){
                ansEnv->setShape(50,200000,4000);
            } else{
                ansEnv->setShape(50,2000,4000);
            }
            ansEnv->triggerEnv();
        }
    }
}

void BatobeOSC::displayTempScore(){ // Incoming answer
    if(bDisplayTempScore){
//        cout << "displayTempScore" << endl;
        if(!ansEnv->active){
            bDisplayTempScore = false;
        }
        ofSetColor(255, 255*ansEnv->process());
        displayOptions();
        displayPercentage();
        // DISPLAY
    }
}

void BatobeOSC::displayPercentage(){
    if(ans1!="nil" && ans2!="nil" && ans3!="nil"){ // 3 options
        // PERCENTAGE
        int x1 = ofGetWindowWidth()/4;
        int x2 = x1*2;
        int x3 = x1*3;
        
        
        ofRectangle space = percentage.getStringBoundingBox(firstPercentage+"%", 0, 0);
        x1 -= space.getWidth()/2.;
        
        ofSetColor(0, barAlpha*ansEnv->process());
        ofDrawRectangle(0, percentageY-space.getHeight(), ofGetWindowWidth(), space.getHeight());
        
        ofSetColor(255, 255*ansEnv->process());
        percentage.drawString(firstPercentage+"%", x1, percentageY);
        
        space = percentage.getStringBoundingBox(secondPercentage+"%", 0, 0);
        x2 -= space.getWidth()/2.;
        percentage.drawString(secondPercentage+"%", x2, percentageY);
        
        space = percentage.getStringBoundingBox(thirdPercentage+"%", 0, 0);
        x3 -= space.getWidth()/2.;
        percentage.drawString(thirdPercentage+"%", x3, percentageY);
    } else{ // 2 options
        
        int x1 = ofGetWindowWidth()/3;
        int x2 = x1*2;
        
        ofRectangle space = percentage.getStringBoundingBox(firstPercentage+"%", 0, 0);
        x1 -= space.getWidth()/2.;
        
        ofSetColor(0, barAlpha*ansEnv->process());
        ofDrawRectangle(0, percentageY-space.getHeight(), ofGetWindowWidth(), space.getHeight());
        
        ofSetColor(255, 255*ansEnv->process());
        percentage.drawString(firstPercentage+"%", x1, percentageY);
        
        space = percentage.getStringBoundingBox(secondPercentage+"%", 0, 0);
        x2 -= space.getWidth()/2.;
        percentage.drawString(secondPercentage+"%", x2, percentageY);
    }
}

void BatobeOSC::displayOptions(){
    if(ans1!="nil" && ans2!="nil" && ans3!="nil"){ // 3 options
        // OPTIONS
        int x1 = ofGetWindowWidth()/4;
        int x2 = x1*2;
        int x3 = x1*3;
        
        ofRectangle space = answer.getStringBoundingBox(ans1, 0, 0);
        x1 -= space.getWidth()/2.;
        
        ofSetColor(0, barAlpha*ansEnv->process());
        ofDrawRectangle(0, ansY-space.getHeight(), ofGetWindowWidth(), space.getHeight());
        
        ofSetColor(255, 255*ansEnv->process());
        answer.drawString(ans1, x1, ansY);
        
        space = answer.getStringBoundingBox(ans2, 0, 0);
        x2 -= space.getWidth()/2.;
        answer.drawString(ans2, x2, ansY);
        
        space = answer.getStringBoundingBox(ans3, 0, 0);
        x3 -= space.getWidth()/2.;
        answer.drawString(ans3, x3, ansY);
        } else{ // 2 options
        
            int x1 = ofGetWindowWidth()/3;
            int x2 = x1*2;
            
            ofRectangle space = answer.getStringBoundingBox(ans1, 0, 0);
            x1 -= space.getWidth()/2.;
            
            ofSetColor(0, barAlpha*ansEnv->process());
            ofDrawRectangle(0, ansY-space.getHeight(), ofGetWindowWidth(), space.getHeight());

            ofSetColor(255, 255*ansEnv->process());
            answer.drawString(ans1, x1, ansY);
            
            space = answer.getStringBoundingBox(ans2, 0, 0);
            x2 -= space.getWidth()/2.;
            answer.drawString(ans2, x2, ansY);
    }
}

void BatobeOSC::displayQ(){
    if(bDisplayQ){
        if(!questionEnv->active){
            bDisplayQ = false;
        }
        
        
        int x = ofGetWindowWidth()/2.;
        ofRectangle space = question.getStringBoundingBox(title, 0, 0);
        x -= space.getWidth()/2.;
        
        ofSetColor(0, barAlpha*questionEnv->process());
        ofDrawRectangle(0, titleY-space.getHeight(), ofGetWindowWidth(), space.getHeight());
        
        ofSetColor(255, 255*questionEnv->process());
        question.drawString(title, x, titleY);
        
//        displayOptions();
    }
}

void BatobeOSC::displayResult(){
    if(bDisplayResult){
        string option;
        string percentageTemp;
        if(!resultEnv->active){ // 5 sec in beeld
            bDisplayResult = false;
            return;
        }
//        if(firstPercentage==secondPercentage){
//            firstPercentage = ofToString(atoi(firstPercentage.c_str())+1);
//        }
//        if(firstPercentage==thirdPercentage){
//            firstPercentage = ofToString(atoi(firstPercentage.c_str())+1);
//        }
//        if(secondPercentage==thirdPercentage){
//            secondPercentage = ofToString(atoi(secondPercentage.c_str())+1);
//        }
        
        
        if(firstPercentage >= secondPercentage && firstPercentage >= thirdPercentage){ // 1 wint
            option = ans1;
            percentageTemp = firstPercentage;
        } else{
            if(secondPercentage >= firstPercentage && secondPercentage >= thirdPercentage){ // 2 wins
                option = ans2;
                percentageTemp = secondPercentage;
            } else{ // 3 wins
                option = ans3;
                percentageTemp = thirdPercentage;
            }
        }
        
        
        // Option
        ofRectangle space = question.getStringBoundingBox(option, 0, 0);
        
        ofSetColor(0, resultEnv->process()*barAlpha);
        ofDrawRectangle(0, ansY-space.getHeight(), ofGetWindowWidth(), space.getHeight());
        
        ofSetColor(255, resultEnv->process()*255);
        question.drawString(option, ofGetWindowWidth()/2.-(space.getWidth()/2.), ansY);
        
        // Percentage
        int x = ofGetWindowWidth()/2.;
        space = percentage.getStringBoundingBox(percentageTemp+"%", 0, 0);
        x -= space.getWidth()/2.;
        ofSetColor(0, resultEnv->process()*barAlpha);
        ofDrawRectangle(0, percentageY-space.getHeight(), ofGetWindowWidth(), space.getHeight());
        ofSetColor(255, resultEnv->process()*255);
        percentage.drawString(percentageTemp+"%", x, percentageY);
    }
}

void BatobeOSC::showPercentage(){
    
}

void BatobeOSC::displayChoose(){
    if(bDisplayChoose){
        if(!questionEnv->active){
            bDisplayChoose = false;
        }
        
        
        int x = ofGetWindowWidth()/2.;
        ofRectangle space = question.getStringBoundingBox("CHOOSE", 0, 0);
        x -= space.getWidth()/2.;
        
        ofSetColor(0, questionEnv->process()*barAlpha);
        ofDrawRectangle(0, titleY-space.getHeight(), ofGetWindowWidth(), space.getHeight());

        ofSetColor(255, 255*questionEnv->process());
        question.drawString("CHOOSE", x, titleY);
    }
}

void BatobeOSC::doDisplayChoose(){
    bDisplayChoose = true;
    questionEnv->setShape(200,5000,5000);
    questionEnv->triggerEnv();
}

void BatobeOSC::displayWhoAreYou(){
    if(bDisplayWhoAreYou){
        if(!whoAreYouEnv->active){
            cout << "ja" << endl;
            bDisplayWhoAreYou = false;
        }
        
        
        int x = ofGetWindowWidth()/2.;
        ofRectangle space = question.getStringBoundingBox("WHO ARE YOU", 0, 0);
        x -= space.getWidth()/2.;
        
        ofSetColor(0, whoAreYouEnv->process()*barAlpha);
        ofDrawRectangle(0, titleY-space.getHeight(), ofGetWindowWidth(), space.getHeight());
        ofSetColor(255, 255*whoAreYouEnv->process());
        question.drawString("WHO ARE YOU", x, titleY);
        
        x = ofGetWindowWidth()/2.;
        space = question.getStringBoundingBox(id+"?", 0, 0);
        x -= space.getWidth()/2.;
        
        ofSetColor(0, whoAreYouEnv->process()*barAlpha);
        ofDrawRectangle(0, titleY+200-space.getHeight(), ofGetWindowWidth(), space.getHeight());
        ofSetColor(255, 255*whoAreYouEnv->process());
        question.drawString(id+"?", x, titleY+200);

    }
}

void BatobeOSC::doDisplayChoose(string id){
    bDisplayWhoAreYou = true;
    whoAreYouEnv->setShape(200,500000,5000);
    whoAreYouEnv->triggerEnv();
    this->id = id;
}

void BatobeOSC::doDisplayYouChose(string title){
    youChose = title;
    bDiplayYouChose = true;
    ansEnv->setShape(200,6000,3000);
    ansEnv->triggerEnv();
}

void BatobeOSC::displayYouChose(){
    if(bDiplayYouChose){
        if(!ansEnv->active){
            bDiplayYouChose = false;
        }
        int x = ofGetWindowWidth()/2.;
        ofRectangle space = answer.getStringBoundingBox(youChose, 0, 0);
        x -= space.getWidth()/2.;
        
        ofSetColor(0, ansEnv->process()*barAlpha);
        ofDrawRectangle(0, 200-space.getHeight(), ofGetWindowWidth(), space.getHeight());
        ofSetColor(255, 255*ansEnv->process());
        answer.drawString(youChose, x, 200);
    }
}
