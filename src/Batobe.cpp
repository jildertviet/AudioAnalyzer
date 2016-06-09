//
//  Batobe.cpp
//  Paul
//
//  Created by Jildert Viet on 14-02-16.
//
//

#include "Batobe.hpp"


Batobe::Batobe(){
//        song = new Juncture(&visualizer);
//        song = new TimeForYou(&visualizer);
//    song = new Faith(&visualizer);
//        song = new Ghost(&visualizer);
//        song = new MaybeTomorrow(&visualizer);
//        song = new TeachMe(&visualizer);
//        song = new MamaOtis(&visualizer);
//        song = new NoDank(&visualizer);
//        song = new Fem(&visualizer);
    
    visualizer.topLayer->addEvent(new BatobeOSC());
    batobeOSC = (BatobeOSC*)(visualizer.topLayer->getLast());
    batobeOSC->setFontSize(400);
    
    visualizer.startEvent->addEvent(new Image("1_uitleg.png"));
    image = (Image*)visualizer.startEvent->getLast();
    
    receiver.setup(5000);
}

void Batobe::keys(int key){
//    song->keys(key);
//    cout << song->songName << endl;
    switch (key) {
        case '0':
            if(song)
                song->stop();
            song = new Ghost(&visualizer);
            break;
        case '1':
            if(song)
                song->stop();
            song = new MamaOtis(&visualizer);
            break;
        case '2':
            if(song)
                song->stop();
            song = new Faith(&visualizer);
            break;
        case '3':
            if(song)
                song->stop();
            song = new TimeForYou(&visualizer);
            break;
        case '4':
            if(song)
                song->stop();
            song = new Fem(&visualizer);
            break;
        case '5':
            if(song)
                song->stop();
            song = new Juncture(&visualizer);
            break;
        case '6':
            if(song)
                song->stop();
            song = new TeachMe(&visualizer);
            ((TeachMe*)song)->receiver = &receiver;
            break;
        case '7':
            if(song)
                song->stop();
            song = new NoDank(&visualizer);
            ((NoDank*)song)->receiver = &receiver;
            break;
        case '8':
            if(song)
                song->stop();
            song = new MaybeTomorrow(&visualizer);
            break;
            
        default:
            break;
    }
    setBrightness(key);
}

void Batobe::setBrightness(int key){
    switch(key){
        case 'z':
            visualizer.fadeScreen->colors[0] = ofColor(0,0);
            break;
        case 'x':
            visualizer.fadeScreen->colors[0] = ofColor(0,10);
            break;
        case 'c':
            visualizer.fadeScreen->colors[0] = ofColor(0,20);
            break;
        case 'v':
            visualizer.fadeScreen->colors[0] = ofColor(0,50);
            break;
            
        case 'q':
            visualizer.fadeIn(5000);
            break;
            
        case 'w':
            visualizer.fadeOut(5000);
            break;
            
        case 't':
            visualizer.bAddMirror = !visualizer.bAddMirror;
            break;
        case 'y':
            cout << "Y" << endl;
            if(image){
                image->active = true;
                image->setEnvelope(1, 1, 1);
                image=nullptr;
            }
            break;
            
        case 'l':
            if(image)
                image->loadImage("2_uitleg.png");
            break;
        case 'k':
            if(image)
                image->drawImage = !(image->drawImage);
            break;
            
        case 'u':
            batobeOSC->doDisplayChoose();
            break;
            
//        case 'i':
//            batobeOSC->doDisplayYouChose("You chose: improvise with only one string");
//            break;
//            
//        case 'o':
//            batobeOSC->doDisplayYouChose("You chose: improvise with only two fingers");
//            break;
    }
}

void Batobe::update(){
    if(song){
        song->doMidiFunc();
        song->update();
    }
}