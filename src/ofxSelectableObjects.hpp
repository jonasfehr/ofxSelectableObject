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
    void recalcPositioning();
    void deleteSelected();
    void deleteAtIndex(int index);
    void reIndex();
    
    void clear();
    void draw();
    void drawButtons();

    bool select(string key);
    bool select(int index);
        
    int getIndexFromKey(string key);
    
    void activate(int index);
    void deactivate(int index);
    void activateCurrent();
    void deactivateCurrent();
    
    void lock();
    void unlock();

    bool mouseReleased(ofMouseEventArgs &e);
    bool mousePressed(ofMouseEventArgs &e);

    int size();
    
    int getIndex();
    string getKey();
    
    void setWindow(ofRectangle window);
    
    vector<shared_ptr<SelectableObjectBase>> selectableObjects;
    ofRectangle objectsRectangle;
    int index;
    int spacing, fixedSize;
    bool isVertical;
    
    int lastPressedIndex;
    
    SelectType type;
    
    ofEvent<string> keyActivatedE;
    ofEvent<int> indexActivatedE;
    ofEvent<string> keyDeactivatedE;
    ofEvent<int> indexDeactivatedE;
    
    bool isLocked;
};
#endif /* ofxSelectableObjects_hpp */

