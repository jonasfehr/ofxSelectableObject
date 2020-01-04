//
//  ofxSelectableObjects.cpp
//  exampleTabs
//
//  Created by Jonas Fehr on 10/07/2019.
//

#include "ofxSelectableObjects.hpp"

ofxSelectableObjects::ofxSelectableObjects(){
    ofAddListener(ofEvents().mouseReleased, this, &ofxSelectableObjects::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mousePressed, this, &ofxSelectableObjects::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    setup(0, 0, 200, 30, ST_RADIO, false, 0, 5);

}

ofxSelectableObjects::~ofxSelectableObjects(){
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxSelectableObjects::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
    ofRemoveListener(ofEvents().mousePressed, this, &ofxSelectableObjects::mousePressed, OF_EVENT_ORDER_BEFORE_APP);
    
//    for (auto p : childSelectableObjects)
//    {
//      delete p;
//    }
//    childSelectableObjects.clear();
}


void ofxSelectableObjects::setup( ofRectangle rect, SelectType type,  bool isVertical, int fixedSize, int spacing){
    setup(rect.getLeft(), rect.getTop(), rect.getWidth(), rect.getHeight(), type, isVertical, fixedSize, spacing);
}

void ofxSelectableObjects::setup(int x, int y, int w, int h, SelectType type, bool isVertical, int fixedSize, int spacing){
    objectsRectangle.set(x,y,w,h);
    this->type = type;
    this->spacing = spacing;
    this->fixedSize = fixedSize;
    this->isVertical = isVertical;
    this->index = 0;
    this->lastPressedIndex = -1;
    this->isLocked = false;
}

void ofxSelectableObjects::add(shared_ptr<SelectableObjectBase> selectableObject){
    
    
    selectableObject->setIndex(index);
    index++;
    
    selectableObjects.push_back(selectableObject);
    
    recalcPositioning();
    // activate latest added
    if(type == ST_RADIO) activate(selectableObject->getIndex());
    else selectableObject->deactivate();
}

//void ofxSelectableObjects::addChildObjects(ofxSelectableObjects &selectableObjects){
//    childSelectableObjects.push_back(&selectableObjects);
//}

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
    if(lastPressedIndex < selectableObjects.size()) activate(lastPressedIndex);
    else activate(index-1);

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
    drawButtons();
}

void ofxSelectableObjects::drawButtons(){
    int i = 0;
    for(auto & selectableObject : selectableObjects){
        selectableObject->draw();
        i++;
    }
}

//void ofxSelectableObjects::drawChildObjects(){
//    for(auto & c : childSelectableObjects){
//        c->draw();
//    }
//}

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
    lastPressedIndex = index;
    for( auto & selectableObject : selectableObjects){
        switch(type){
            case ST_RADIO:
                if(selectableObject->getIndex() == lastPressedIndex) selectableObject->activate();
                else selectableObject->deactivate();
                break;
            case ST_TOGGLE:
                if(selectableObject->getIndex() == lastPressedIndex){
                    if(selectableObject->isActive()) selectableObject->deactivate();
                    else selectableObject->activate();
                }
                break;
                
            case ST_PRESSED:
                if(selectableObject->getIndex() == lastPressedIndex) selectableObject->activate();
                break;
        }

    }
    string currentSelectedKey = selectableObjects[lastPressedIndex]->getKey();
    ofNotifyEvent(keyActivatedE, currentSelectedKey, this);
    ofNotifyEvent(indexActivatedE, lastPressedIndex, this);
}

void ofxSelectableObjects::deactivate(int index){
    if(index < 0 || index > selectableObjects.size()-1) return;
    lastPressedIndex = index;
    for( auto & selectableObject : selectableObjects){
        switch(type){
            case ST_RADIO:
                
                break;
            case ST_TOGGLE:
                
                break;
                
            case ST_PRESSED:
                if(selectableObject->getIndex() == lastPressedIndex) selectableObject->deactivate();
                break;
        }
        
    }
    string currentSelectedKey = selectableObjects[lastPressedIndex]->getKey();
    ofNotifyEvent(keyDeactivatedE, currentSelectedKey, this);
    ofNotifyEvent(indexDeactivatedE, lastPressedIndex, this);
}

//void ofxSelectableObjects::activateCurrent(){
//    activate(lastPressedIndex);
//}
//
//void ofxSelectableObjects::deactivateCurrent(){
//    for( auto & selectableObject : selectableObjects){
//        if(selectableObject->isActive()){
//            deactivate(selectableObject->getIndex());
//        }
//    }
//}

void ofxSelectableObjects::lock(){
    isLocked = true;
//    for(auto & c : childSelectableObjects){
//        c->lock();
//    }
}

void ofxSelectableObjects::unlock(){
    isLocked = false;
//    for(auto & c : childSelectableObjects){
//        c->unlock();
//    }
}

void ofxSelectableObjects::mouseReleased(ofMouseEventArgs &e){
    if(isLocked) return;
    
    glm::vec2 mousePos = e;
    if(type == ST_PRESSED){
        for( auto & selectableObject : selectableObjects){
            if(selectableObject->clickableSurface.inside(mousePos)){
                deactivate(selectableObject->getIndex());
            }
        }
    }
}

void ofxSelectableObjects::mousePressed(ofMouseEventArgs &e){
    if(isLocked) return;
    
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
    else return lastPressedIndex;
}
string ofxSelectableObjects::getKey(){ return selectableObjects[lastPressedIndex]->getKey(); }

void ofxSelectableObjects::setWindow(ofRectangle window){
    objectsRectangle = window;
    recalcPositioning();
}
