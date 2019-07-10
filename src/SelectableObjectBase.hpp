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
    
    void setup(string key){
        this->key = key;
    }
    
    void setClickableSurface(int x, int y, int w, int h){
        clickableSurface.set(x,y,w,h);
    }
    
    void setIndex( int index ){ this->index = index; }
    
    virtual void draw(){
        ofPushStyle();
        {
            if(isActive()) ofSetColor(ofColor::gray);
            else ofSetColor(ofColor::black);
            ofDrawRectangle(clickableSurface);
            
            if(isActive()) ofSetColor(ofColor::orange);
            else ofSetColor(ofColor::white);
            ofDrawBitmapString(key, clickableSurface.getLeft()+5, clickableSurface.getBottom()-5);
            ofNoFill();
            ofDrawRectangle(clickableSurface);
            
        }
        ofPopStyle();
    }
    
    bool isActive(){ return active; }
    virtual void activate(){ active = true; }
    virtual void deactivate(){ active = false; }
    
    string & getKey(){ return key; }
    
private:
    string key;
    int index;
    bool active;
    
public:
    ofRectangle clickableSurface;
};

#endif /* SelectableObjectBase_hpp */
