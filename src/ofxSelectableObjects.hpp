//
//  ofxSelectableObjects.hpp
//  exampleTabs
//
//  Created by Jonas Fehr on 10/07/2019.
//

#ifndef ofxSelectableObjects_hpp
#define ofxSelectableObjects_hpp

#include <stdio.h>
#include "ofMain.h"
#include "SelectableObjectBase.hpp"


class ofxSelectableObjects {
public:
    
    ofxSelectableObjects(){
        ofAddListener(ofEvents().mouseReleased, this, &ofxSelectableObjects::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
        index = 0;
    }
    
    ~ofxSelectableObjects(){
        ofRemoveListener(ofEvents().mouseReleased, this, &ofxSelectableObjects::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
    }
    
    void setup( ofRectangle rect, bool isRadio = true,  bool isVertical = false, int fixedSize = 0, int spacing = 5){
        setup(rect.getLeft(), rect.getTop(), rect.getWidth(), rect.getHeight(), isRadio, isVertical, fixedSize, spacing);
    }
    
    void setup(int x, int y, int w, int h, bool isRadio = true, bool isVertical = false, int fixedSize = 0, int spacing = 5){
        objectsRectangle.set(x,y,w,h);
        this->spacing = spacing;
        this->fixedSize = fixedSize;
        this->isVertical = isVertical;
        this->isRadio = isRadio;
    }
    
    void add(SelectableObjectBase &selectableObject){
        

        selectableObject.setIndex(index);
        index++;
        
        selectableObjects[selectableObject.getKey()] = &selectableObject;
        
        
        // resize and reposition all
        int x = objectsRectangle.getLeft()+spacing;
        int y = objectsRectangle.getTop()+spacing;
        int numObjects = selectableObjects.size();
        
        if(isVertical){
            int w = objectsRectangle.getWidth()-2*spacing;
            int h = fixedSize;
            if(fixedSize == 0) h = (objectsRectangle.getHeight()-(numObjects+1)*spacing)/numObjects;
            int i = 0;
            for(auto & sO : selectableObjects){
                y = objectsRectangle.getTop()+(h + spacing)*i+spacing;
                sO.second->setClickableSurface(x, y, w, h);
                i++;
            }
            
        } else {
            int w = fixedSize;
            if(fixedSize == 0) w = (objectsRectangle.getWidth()-(numObjects+1)*spacing)/numObjects;
            int h = objectsRectangle.getHeight()-2*spacing;
            
            int i = 0;
            for(auto & sO : selectableObjects){
                x = objectsRectangle.getLeft()+(w + spacing)*i+spacing;
                sO.second->setClickableSurface(x, y, w, h);
                i++;
            }
        }
        
        
        // activate latest added
        activate(selectableObject.getKey());
    }
    
    
    void draw(){
        int i = 0;
        for(auto & selectableObject : selectableObjects){
            selectableObject.second->draw();
            i++;
        }
    }
    
    void activate(string key){
        currentSelectedKey = key;
        for( auto & selectableObject : selectableObjects){
            if(selectableObject.second->getKey() == currentSelectedKey && isRadio) selectableObject.second->activate();
            else selectableObject.second->deactivate();
        }
        currentSelectedIndex = selectableObjects[currentSelectedKey]->getIndex();
        ofNotifyEvent(keyChangedE, currentSelectedKey, this);
        ofNotifyEvent(indexChangedE, currentSelectedIndex, this);
    }
    
    bool mouseReleased(ofMouseEventArgs &e){
        glm::vec2 mousePos = e;
        for( auto & selectableObject : selectableObjects){
            if(selectableObject.second->clickableSurface.inside(mousePos)){
                activate(selectableObject.second->getKey());
            }
        }
    }
    
    map<string, SelectableObjectBase*> selectableObjects;
    ofRectangle objectsRectangle;
    int index;
    int spacing, fixedSize;
    bool isVertical;
    bool isRadio;
    
    string currentSelectedKey;
    int currentSelectedIndex;
    
    ofEvent<string> keyChangedE;
    ofEvent<int> indexChangedE;


};
#endif /* ofxSelectableObjects_hpp */

