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
    
    ofxSelectableObjects();
    ~ofxSelectableObjects();
    
    void setup();
    void setup( ofRectangle rect, bool isRadio = true,  bool isVertical = false, int fixedSize = 0, int spacing = 5);
    void setup(int x, int y, int w, int h, bool isRadio = true, bool isVertical = false, int fixedSize = 0, int spacing = 5);
    
    void add(SelectableObjectBase &selectableObject);
    void recalcPositioning();
    void deleteSelected();
    void deleteAtIndex(int index);
    void reIndex();
    
    void clear();
    void draw();
    
    bool select(string key);
    bool select(int index);
        
    int getIndexFromKey(string key);
    
    void activate(int index);
    bool mouseReleased(ofMouseEventArgs &e);
    
    int size();
    
    int getIndex();
    string getKey();
    
    void setWindow(ofRectangle window);
    
    vector<SelectableObjectBase*> selectableObjects;
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

