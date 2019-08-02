//
//  ofxSelectableObjects.cpp
//  exampleTabs
//
//  Created by Jonas Fehr on 10/07/2019.
//

#include "ofxSelectableObjects.hpp"

ofxSelectableObjects::ofxSelectableObjects(){
    ofAddListener(ofEvents().mouseReleased, this, &ofxSelectableObjects::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
    index = 0;
    setup(0, 0, 200, 30, true, false, 0, 5);

}

ofxSelectableObjects::~ofxSelectableObjects(){
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxSelectableObjects::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
//    for (auto pointer : selectableObjects){
//        delete pointer;
//    }
//    selectableObjects.clear();
}


void ofxSelectableObjects::setup( ofRectangle rect, bool isRadio,  bool isVertical, int fixedSize, int spacing){
    setup(rect.getLeft(), rect.getTop(), rect.getWidth(), rect.getHeight(), isRadio, isVertical, fixedSize, spacing);
}

void ofxSelectableObjects::setup(int x, int y, int w, int h, bool isRadio, bool isVertical, int fixedSize, int spacing){
    objectsRectangle.set(x,y,w,h);
    this->spacing = spacing;
    this->fixedSize = fixedSize;
    this->isVertical = isVertical;
    this->isRadio = isRadio;
    this->index = 0;
}

void ofxSelectableObjects::add(SelectableObjectBase &selectableObject){
    
    
    selectableObject.setIndex(index);
    index++;
    
    selectableObjects.push_back(&selectableObject);
    
    recalcPositioning();
    // activate latest added
    activate(selectableObject.getIndex());
}

void ofxSelectableObjects::deleteSelected(){
    deleteAtIndex(getIndex());
}

void ofxSelectableObjects::deleteAtIndex(int index){
    selectableObjects.erase (selectableObjects.begin()+index);
    reIndex();
    recalcPositioning();
}

void ofxSelectableObjects::reIndex(){
    index = 0;
    for(auto & selectableObject :  selectableObjects){
        selectableObject->setIndex(index);
        index++;
    }
    activate(index-1);

}

void ofxSelectableObjects::recalcPositioning(){
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
            sO->setClickableSurface(x, y, w, h);
            i++;
        }
        
    } else {
        int w = fixedSize;
        if(fixedSize == 0) w = (objectsRectangle.getWidth()-(numObjects+1)*spacing)/numObjects;
        int h = objectsRectangle.getHeight()-2*spacing;
        
        int i = 0;
        for(auto & sO : selectableObjects){
            x = objectsRectangle.getLeft()+(w + spacing)*i+spacing;
            sO->setClickableSurface(x, y, w, h);
            i++;
        }
    }
}

void ofxSelectableObjects::clear(){
    selectableObjects.clear();
    index = 0;
}


void ofxSelectableObjects::draw(){
    int i = 0;
    for(auto & selectableObject : selectableObjects){
        selectableObject->draw();
        i++;
    }
}

bool ofxSelectableObjects::select(string key){
    int index = getIndexFromKey(key);
    if(index != -1){
        activate( index );
        return true;
    }
    else return false;
}

bool ofxSelectableObjects::select(int index){
    if(index < selectableObjects.size() && index >= 0 ){
        activate( index );
        return true;
    }
    else return false;
}

int ofxSelectableObjects::getIndexFromKey(string key){
    int index = 0;
    for(auto & selectableObject : selectableObjects){
        if(selectableObject->getKey() == key){
            index = selectableObject->getIndex();
            break;
        }
        
    }
    return index;
}

void ofxSelectableObjects::activate(int index){
    if(index < 0 || index > selectableObjects.size()-1) return;
    currentSelectedIndex = index;
    for( auto & selectableObject : selectableObjects){
        if(selectableObject->getIndex() == currentSelectedIndex && isRadio) selectableObject->activate();
        else selectableObject->deactivate();
    }
    currentSelectedKey = selectableObjects[currentSelectedIndex]->getKey();
    ofNotifyEvent(keyChangedE, currentSelectedKey, this);
    ofNotifyEvent(indexChangedE, currentSelectedIndex, this);
}

bool ofxSelectableObjects::mouseReleased(ofMouseEventArgs &e){
    glm::vec2 mousePos = e;
    for( auto & selectableObject : selectableObjects){
        if(selectableObject->clickableSurface.inside(mousePos)){
            activate(selectableObject->getIndex());
        }
    }
}

int ofxSelectableObjects::size(){ return selectableObjects.size(); }

int ofxSelectableObjects::getIndex(){
    if(selectableObjects.size() == 0) return -1;
    else return currentSelectedIndex;
}
string ofxSelectableObjects::getKey(){ return currentSelectedKey; }

void ofxSelectableObjects::setWindow(ofRectangle window){
    objectsRectangle = window;
    recalcPositioning();
}
