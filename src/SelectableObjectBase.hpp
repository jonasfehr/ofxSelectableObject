//
//  SelectableObjectBase.hpp
//  exampleTabs
//
//  Created by Jonas Fehr on 10/07/2019.
//

#ifndef SelectableObjectBase_hpp
#define SelectableObjectBase_hpp

#include <stdio.h>
#include "ofMain.h"
class SelectableObjectBase{
public:
    
    SelectableObjectBase(){}
    SelectableObjectBase(string key, string imgPath = "none", bool isLocked = false){
        setup(key, imgPath, isLocked);
    }
    ~SelectableObjectBase(){}
    
    void setup(string key, string imgPath = "none", bool isLocked = false){
        this->key = key;
        if(imgPath != "none"){
            hasImg = true;
            img.load(imgPath);
            img.update();
        }else{
            hasImg = false;
        }
        this->isLocked = isLocked;
    }
    
    void setClickableSurface(int x, int y, int w, int h){
        clickableSurface.set(x,y,w,h);
        if(hasImg){
            img.resize(w,h);
            img.update();
        }
    }
    
    void setIndex( int index ){ this->index = index; }
    int getIndex(){ return index; }
    void setKey(string newKey){ this->key = newKey; }
    string getKey(){ return key; }


    virtual void draw(){
        ofPushStyle();
        {
            // background
            if(isActive()) ofSetColor(ofColor::gray);
            else ofSetColor(ofColor::black);
            ofDrawRectangle(clickableSurface);
            
            if(hasImg){
                ofSetColor(ofColor::white);
                img.draw(clickableSurface.getTopLeft());
            } else {
                if(isActive()) ofSetColor(ofColor::orange);
                else ofSetColor(ofColor::white);
                ofDrawBitmapString(key, clickableSurface.getLeft()+5, clickableSurface.getBottom()-5);
                ofNoFill();
                ofDrawRectangle(clickableSurface);
            }
        }
        ofPopStyle();
    }
    
    bool isActive(){ return active; }
    
    virtual void activate(){
        active = true;
        ofNotifyEvent(isActiveE, active, this);
        cout << "activated: " << getKey() << endl;
    }
    virtual void deactivate(){
        active = false;
        ofNotifyEvent(isActiveE, active, this);
        cout << "deactivated: " << getKey() << endl;

    }
    
    virtual void lock(){
        isLocked = true;
    }
    
    virtual void unlock(){
        isLocked = false;
    }
    
    
private:
    string key;
    int index;
    bool active;
    bool hasImg;
    ofImage img;
    
    
public:
    ofEvent<bool> isActiveE;
    ofRectangle clickableSurface;
    bool isLocked;
};

#endif /* SelectableObjectBase_hpp */
