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

enum SelectType: int{
    ST_RADIO,
    ST_TOGGLE,
    ST_PRESSED
};


class ofxSelectableObjects {
public:
    
    ofxSelectableObjects();
    ~ofxSelectableObjects();
    
    void setup();
    void setup( ofRectangle rect, SelectType type = ST_RADIO,  bool isVertical = false, int fixedSize = 0, int spacing = 5);
    void setup(int x, int y, int w, int h, SelectType type = ST_RADIO, bool isVertical = false, int fixedSize = 0, int spacing = 5);
    
    void add(shared_ptr<SelectableObjectBase> selectableObject);
   // void addChildObjects(ofxSelectableObjects &selectableObjects);

    void recalcPositioning();
    void deleteSelected();
    void deleteAtIndex(int index);
    void reIndex();
    
    void clear();
    void draw();
    void drawButtons();
    //void drawChildObjects();

    bool select(string key);
    bool select(int index);
        
    int getIndexFromKey(string key);
    
    void activate(int index);
    void deactivate(int index);
//    void activateCurrent();
//    void deactivateCurrent();
    
    // if the object is locked it won't react towards mouse input.
    void lock();
    void unlock();

    void mouseReleased(ofMouseEventArgs &e);
    void mousePressed(ofMouseEventArgs &e);

    int size();
    
    int getIndex();
    string getKey();
    
    void setWindow(ofRectangle window);
    
    vector<shared_ptr<SelectableObjectBase>> selectableObjects;
    ofRectangle objectsRectangle;
    int index;
    int spacing, fixedSize;
    bool isVertical;
    bool isLocked;
    
    int lastPressedIndex;
    
    SelectType type;
    
    ofEvent<string> keyActivatedE;
    ofEvent<int> indexActivatedE;
    ofEvent<string> keyDeactivatedE;
    ofEvent<int> indexDeactivatedE;
    
    //vector<ofxSelectableObjects*> childSelectableObjects;
    
};
#endif /* ofxSelectableObjects_hpp */

