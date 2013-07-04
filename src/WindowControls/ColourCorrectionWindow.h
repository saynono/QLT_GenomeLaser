//
//  ColourCorrectionWindow.h
//  LaserGateway
//
//  Created by say nono on 19.03.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <stdlib.h>

#include "cinder/Xml.h"

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/ComboBox.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define COLOR_MAX_CURVE_POINTS 4
#define COLOR_AMOUNT_COLORS 4

class ColourCorrectionWindow : public Gwen::Controls::Base {
    
public:
    
	ColourCorrectionWindow( Gwen::Controls::Base *parent );
	virtual ~ColourCorrectionWindow();
    
    void setup();
    
    void saveSettings();
    void loadSettings();
    
    void connectColorValues(vector<char>* r,vector<char>* g,vector<char>* b,vector<char>* i);
    
    void getColorValues(vector<float>* values, int colorID);
    void getColorValues(vector<char>* values, int colorID);
    void calculateValues(vector<float>* values, int colorID);
    Vec2f findPercentInBSpline(float percent, const BSpline2f& bs);
    
	virtual void Render( Gwen::Skin::Base* skin );
	virtual void RenderUnder( Gwen::Skin::Base* skin );

	void OnComboSelect(Gwen::Controls::Base* pControl);
    void onButtonPressed(Gwen::Controls::Base* pControl);
    virtual void OnMouseClickLeft(int x, int y, bool mouseDown);
    virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );
    virtual void OnBoundsChanged( Gwen::Rect oldBounds );
    virtual void OnMouseLeave();
    
    
    
private:
    
    void        setColourBounds();
    void        recalculateColorValues();
    
    int         mColorSelectionID;
    bool        mIsMouseDragging;
    bool        bColorValuesConnected;
    int         mMouseDraggingPointID;
    int         mMouseOverPointID;
    Vec2f       mMousePressOffset;
    ci::Rectf   mBounds;
    ci::Rectf   mBoundsColours;
    
    map<string, vector<Vec2f>> mColorDefs;
    vector<Vec2f>  mColourCurves[COLOR_AMOUNT_COLORS];
    Path2d      mColourPaths[COLOR_AMOUNT_COLORS];
    Colorf      mColoursDraw[COLOR_AMOUNT_COLORS];
    string      mColourNames[COLOR_AMOUNT_COLORS];

    vector<Vec2f>  mCurvesDragging;
    Path2d      mPathDragging;
    
    XmlTree     mSetttings;
    string      mFilePath;
    
    vector<float>   mTempValues;
    
    vector<vector<char>*>   mColorValuesConnected;
    
    
};



