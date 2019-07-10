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
    
    void setup(int x, int y, int w, int h, int spacing = 5, bool isVertical = false){
        objectsRectangle.set(x,y,w,h);
        this->spacing = spacing;
        this->isVertical = isVertical;
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
            int h = (objectsRectangle.getHeight()-(numObjects+1)*spacing)/numObjects;
            cout << h << endl;
            int i = 0;
            for(auto & sO : selectableObjects){
                y = objectsRectangle.getTop()+(h + spacing)*i+spacing;
                sO.second->setClickableSurface(x, y, w, h);
                i++;
            }
        } else {

            int w = (objectsRectangle.getWidth()-(numObjects+1)*spacing)/numObjects;
            int h = objectsRectangle.getHeight()-2*spacing;
            
            int i = 0;
            for(auto & sO : selectableObjects){
                x = objectsRectangle.getLeft()+(w + spacing)*i+spacing;
                sO.second->setClickableSurface(x, y, w, h);
                i++;
            }
        }
    }
    
    
    void draw(){
        int i = 0;
        for(auto & selectableObject : selectableObjects){
            selectableObject.second->draw();
            i++;
        }
    }
    
    bool mouseReleased(ofMouseEventArgs &e){
        
        glm::vec2 mousePos = e;
        for( auto & selectableObject : selectableObjects){
            if(selectableObject.second->clickableSurface.inside(mousePos)){
                string key = selectableObject.first;
                for( auto & selectableObject : selectableObjects){
                    if(selectableObject.second->getKey() == key) selectableObject.second->activate();
                    else selectableObject.second->deactivate();
                }
            }
        }
    }
    
    map<string, SelectableObjectBase*> selectableObjects;
    ofRectangle objectsRectangle;
    int index;
    int spacing;
    bool isVertical;

};
#endif /* ofxSelectableObjects_hpp */

