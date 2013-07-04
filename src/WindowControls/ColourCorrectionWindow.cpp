//
//  ColourCorrectionWindow.cpp
//  LaserGateway
//
//  Created by say nono on 19.03.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "ColourCorrectionWindow.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include "cinder/app/App.h"
#include "cinder/Path2d.h"

#include "CinderGwen.h"

using namespace Gwen;
using namespace ci;

ColourCorrectionWindow::ColourCorrectionWindow( Gwen::Controls::Base *parent )
: Controls::Base( parent, "ColourCorrection" )
{
    
}

ColourCorrectionWindow::~ColourCorrectionWindow()
{
	app::console() << "ColourCorrectionWindow destroyed." << std::endl;
}

void ColourCorrectionWindow::setup(){
    
    mTempValues.resize( 50 );
    
    mFilePath = "colorSettings.xml" ;
    
    Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
    label->SetText( "Colour Channel" );
    label->SizeToContents();
    label->SetPos( 20, 14 );
	ci::Rectf bounds( cigwen::fromGwen( label->GetBounds() ) );
    
    mColourNames[0] = "red";
    mColourNames[1] = "green";
    mColourNames[2] = "blue";
    mColourNames[3] = "intensity";
    
    Gwen::Controls::ComboBox* combo = new Gwen::Controls::ComboBox( this );
    combo->SetPos( bounds.x2 + 20, bounds.y1 - 4 );
    combo->SetWidth( 70 );
    combo->AddItem( L"RED", mColourNames[0] );
    combo->AddItem( L"GREEN", mColourNames[1] );
    combo->AddItem( L"BLUE", mColourNames[2] );
    combo->AddItem( L"Intensity (-)", mColourNames[3] );
    combo->onSelection.Add( this, &ColourCorrectionWindow::OnComboSelect );
    
	Gwen::Controls::Button *btn = new Gwen::Controls::Button( this );
	btn->SetBounds( combo->GetBounds().x + combo->GetBounds().w + 20, combo->GetBounds().y , 70, 20 );
	btn->SetText( "Save" );
	btn->onPress.Add( this, &ColourCorrectionWindow::onButtonPressed );
//	btn->AddAccelerator( "x" );

    mColorSelectionID = 0;
    mIsMouseDragging = false;
    bColorValuesConnected = false;
    mMousePressOffset = Vec2f(0,0);
    
    setColourBounds();
    mColoursDraw[0] = Colorf(1,0,0);
    mColoursDraw[1] = Colorf(0,1,0);
    mColoursDraw[2] = Colorf(0,0,1);
    mColoursDraw[3] = Colorf(.5,.5,.5);
    
    Vec2f start(0,0);
    Vec2f end(1,1);
    
    for(int j=0;j<COLOR_MAX_CURVE_POINTS;j++){
        mCurvesDragging.push_back(Vec2f());
    }
    
    for(int i=0;i<4;i++){
        mColourPaths[i].moveTo(0,0);
        for(int j=0;j<COLOR_MAX_CURVE_POINTS;j++){
            float percent = j/(float)(COLOR_MAX_CURVE_POINTS-1);
            mColourCurves[i].push_back(lerp(start,end,percent));
            mColourPaths[i].lineTo(mColourCurves[i][j]*100);
        }
    }
    loadSettings();
    
    calculateValues(&mTempValues, mColorSelectionID);
}

void ColourCorrectionWindow::loadSettings(){
    mSetttings = XmlTree( loadAsset(mFilePath) );
    XmlTree lib = mSetttings.getChild( "library" );
    XmlTree clrSettings = lib.getChild("colorSettings");
    int amountColours = clrSettings.getAttributeValue<int>("amount");
    for(int i=0;i<amountColours;i++){
        for( XmlTree::Iter clrSetting = clrSettings.begin(); clrSetting != clrSettings.end(); ++clrSetting ){
            int id = clrSetting->getAttributeValue<int>("id");
            XmlTree points = clrSetting->getChild("points");
//            int amount
//            mColourCurves[id].clear();
            for( XmlTree::Iter point = points.begin(); point != points.end(); ++point ){
                int pos = point->getAttributeValue<int>("id");
//                mColourCurves[id].push_back(Vec2f(point->getChild("x").getValue<float>(),point->getChild("y").getValue<float>()));
                mColourCurves[id][pos].x = point->getChild("x").getValue<float>();
                mColourCurves[id][pos].y = point->getChild("y").getValue<float>();
            }
        }
    }
    for(int i=0;i<COLOR_AMOUNT_COLORS;i++){
        mColourPaths[i] = Path2d( BSpline2f( mColourCurves[i], 2, false, true ) );
        mColourPaths[i].scale(Vec2f(100,100));
    }
}

void ColourCorrectionWindow::saveSettings(){
//    mSetttings = XmlTree( loadFile( "colorSettings.xml" ) );
    XmlTree library( "library", "" );
    XmlTree clrSettings( "colorSettings", "" );
    clrSettings.setAttribute( "amount", COLOR_AMOUNT_COLORS );
    for(int i=0;i<COLOR_AMOUNT_COLORS;i++){
        XmlTree points("points","");
        points.setAttribute( "amount", COLOR_MAX_CURVE_POINTS );
        for(int j=0;j<COLOR_MAX_CURVE_POINTS;j++){
            XmlTree p("point","");
            p.setAttribute("id", j);
            p.push_back( XmlTree("x",toString(mColourCurves[i][j].x)) );
            p.push_back( XmlTree("y",toString(mColourCurves[i][j].y)) );
            points.push_back( p );
        }
        XmlTree clrSetting( "colorSetting", "" );
        clrSetting.setAttribute( "name", mColourNames[i] );
        clrSetting.setAttribute( "id", i );
        clrSetting.push_back( points );
        clrSettings.push_back(clrSetting);
    }
    
    library.push_back(clrSettings);
    library.write( writeFile( getAssetPath("") / mFilePath ) );    
}

void ColourCorrectionWindow::getColorValues(vector<float>* values, int colorID){
    calculateValues(values, colorID);
}

void ColourCorrectionWindow::getColorValues(vector<char>* values, int colorID){
    vector<float> valuesTemp(values->size(),125);
    calculateValues(&valuesTemp, colorID);
    for(int i=0;i<valuesTemp.size();i++){
        values->at(i) = (int)(valuesTemp[i]*255) & 0xff;
    }
}

void ColourCorrectionWindow::calculateValues(vector<float>* values, int colorID){
    
    int pos = colorID;
    vector<Vec2f> points;
    points.push_back(Vec2f(0,0));
    for(int i=0;i<mColourCurves[0].size();i++){
        points.push_back(mColourCurves[pos][i]);
    }
    points.push_back(Vec2f(1,1));
    BSpline2f path( points , 2, false, true );

    float percent;
    int l = values->size();
    Vec2f valPrev(0,0);
    Vec2f val;
    for(int i=0;i<l;i++){
        percent = i/(float)(l-1);
        val = findPercentInBSpline(percent,path);
        values->at(i) = val.y;
        valPrev = val;
    }
    console() << " Caluclated Values!" << std::endl;
}

// Needs some better algorithm here!!!

Vec2f ColourCorrectionWindow::findPercentInBSpline(float percent, const BSpline2f& bs){
    float step = .0001;
    Vec2f valPrev(0,0);
    Vec2f val;
    for(float p=0;p<=1.0;p+=step){
        val = bs.getPosition(p);
        if(val.x >= percent){
            return val;
        }
        valPrev = val;
    }
    return Vec2f(1,1);
}

void ColourCorrectionWindow::setColourBounds(){
    mBounds = ( cigwen::fromGwen( GetBounds() ) );
    mBoundsColours = mBounds;
    mBoundsColours.y1 += 40;
    mBoundsColours.x1 += 1;
    mBoundsColours.x2 -= 1;
    mBoundsColours.y2 -= 1;
}



void ColourCorrectionWindow::Render( Skin::Base* skin )
{
	Vec2f pos( cigwen::fromGwen( LocalPosToCanvas() ) );
	ci::Rectf bounds( cigwen::fromGwen( GetBounds() ) );
	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;
    gl::pushMatrices();
    
    float width = bounds.getWidth();
    float height = bounds.getHeight();
    
    if(aspect > 1){
        width /= aspect;
    }else{
        height *= aspect;
    }
    
	gl::translate( pos );
    gl::color( ci::Color( 0.1,0.1,0.1 ) );
    gl::drawSolidRect(Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h));
    
    gl::color( ci::Color( 0.4,0.4,0.4 ) );
    gl::drawSolidRect(Rectf(mBoundsColours.x1,mBoundsColours.y1,mBoundsColours.x2,mBoundsColours.y2));
    
    gl::color( ci::Color( 0.4,0.4,1.0 ) );
    
//    Vec2f offset(bounds.getWidth()-width,bounds.getHeight()-height);
	gl::translate( mBoundsColours.getLowerLeft() );
    
    Vec2f s = Vec2f(mBoundsColours.getWidth(),mBoundsColours.getHeight());
    s.y *= -1;
    
    gl::pushMatrices();
    gl::scale(s/100.0);
    
    float x;
    gl::color(mColoursDraw[mColorSelectionID]);
    for(int i=0;i<mTempValues.size();i++){
        x = 100 * (i/(float)(mTempValues.size()-1));
        gl::drawLine(Vec2f(x,0), Vec2f(x,(mTempValues[i]*100)));
    }
    
    
    for(int i=0;i<4;i++){
        gl::color(mColoursDraw[i]);
        gl::draw(mColourPaths[i]);
    }
    gl::color(mColoursDraw[mColorSelectionID]);
    gl::draw(mColourPaths[mColorSelectionID]);
    
    if(mIsMouseDragging){
        gl::color(mColoursDraw[mColorSelectionID]);
        gl::draw(mPathDragging);
    }
    
    
    gl::popMatrices();
    

    for(int i=0;i<COLOR_MAX_CURVE_POINTS;i++){
        Vec2f pos;
        if(mIsMouseDragging) pos = mCurvesDragging[i]*s;
        else pos = mColourCurves[mColorSelectionID][i]*s;
        
        gl::color( cigwen::fromGwen(GetSkin()->Colors.Window.TitleInactive) );
        if(mIsMouseDragging && i == mMouseDraggingPointID){
            gl::color( cigwen::fromGwen(GetSkin()->Colors.Window.TitleActive) );
        }
        
        Rectf r(pos.x-3.0,pos.y-3.0,
                pos.x+5.0,pos.y+5.0);
        gl::drawSolidRect(r);
//        gl::drawSolidCircle(mColourCurves[mColorSelectionID][i], 3);
    }
    
    
    gl::popMatrices();
}

void ColourCorrectionWindow::RenderUnder( Skin::Base* skin )
{
}

void ColourCorrectionWindow::OnComboSelect(Gwen::Controls::Base* pControl){
    Gwen::Controls::ComboBox* combo = ( Gwen::Controls::ComboBox* ) pControl;
    string str = combo->GetSelectedItem()->GetName();
    if(str.compare("red") == 0) mColorSelectionID = 0;
    if(str.compare("green") == 0) mColorSelectionID = 1;
    if(str.compare("blue") == 0) mColorSelectionID = 2;
    if(str.compare("intensity") == 0) mColorSelectionID = 3;
    calculateValues(&mTempValues, mColorSelectionID);
}

void ColourCorrectionWindow::OnMouseClickLeft(int x, int y, bool mouseDown){
    
    if(mouseDown){
        mBounds = cigwen::fromGwen( GetBounds() );
        Vec2f localPos = cigwen::fromGwen( CanvasPosToLocal(Gwen::Point(x,y)) );
        Vec2f pos = ((localPos - mBoundsColours.getUpperLeft())/mBoundsColours.getSize());
        pos.y = 1.0 - pos.y;
        for(int i=0;i<COLOR_MAX_CURVE_POINTS;i++){
            Vec2f p = mColourCurves[mColorSelectionID][i];
            float diffX = mColourCurves[mColorSelectionID][i].x - pos.x;
            float diffY = mColourCurves[mColorSelectionID][i].y - pos.y;
            if( abs(diffX) < 0.04 &&
               abs(diffY) < 0.04){
                mCurvesDragging[0] = mColourCurves[mColorSelectionID][0];
                for(int j=0;j<COLOR_MAX_CURVE_POINTS;j++){
                    mCurvesDragging[j] = mColourCurves[mColorSelectionID][j];
                }
                mPathDragging = Path2d( BSpline2f( mCurvesDragging, 2, false, true ) );
                mPathDragging.scale(Vec2f(100,100));

                mMouseDraggingPointID = i;
                mIsMouseDragging = true;
                mMousePressOffset = -Vec2f(diffX,diffY);
                break;
            }
        }
    }else if(mIsMouseDragging){
        mColourCurves[mColorSelectionID][0] = mCurvesDragging[0];
        for(int j=1;j<COLOR_MAX_CURVE_POINTS;j++){
            mColourCurves[mColorSelectionID][j] = mCurvesDragging[j];
        }
        mColourPaths[mColorSelectionID] = Path2d( BSpline2f( mColourCurves[mColorSelectionID], 2, false, true ) );
        mColourPaths[mColorSelectionID].scale(Vec2f(100,100));
        mIsMouseDragging = false;
        calculateValues(&mTempValues, mColorSelectionID);
//        recalculateColorValues();
        if(bColorValuesConnected) getColorValues(mColorValuesConnected[mColorSelectionID],mColorSelectionID);

    }
}

void ColourCorrectionWindow::OnMouseMoved( int x, int y, int deltaX, int deltaY ){
    if(mIsMouseDragging){
//        x -= mBounds.x1;
//        y -= mBounds.y1;
        
        Vec2f localPos = cigwen::fromGwen( CanvasPosToLocal(Gwen::Point(x,y)) );
        Vec2f pos = ((localPos - mBoundsColours.getUpperLeft())/mBoundsColours.getSize());
        pos.y = 1.0 - pos.y;
        
        pos -= mMousePressOffset;
        
        float posXMin = 0.0;
        float posXMax = 1.0;
        float posYMin = 0.0;
        float posYMax = 1.0;
        if(mMouseDraggingPointID<COLOR_MAX_CURVE_POINTS-1) posXMax = mCurvesDragging[mMouseDraggingPointID+1].x;
        if(mMouseDraggingPointID>0) posXMin = mCurvesDragging[mMouseDraggingPointID-1].x;
        
        if(mMouseDraggingPointID==0) posYMin = posYMax = 0;
        if(mMouseDraggingPointID==COLOR_MAX_CURVE_POINTS-1) posYMin = posYMax = 1;
        pos.y = constrain(pos.y,posYMin,posYMax);
        pos.x = constrain(pos.x,posXMin,posXMax);
        
        mCurvesDragging[mMouseDraggingPointID] = pos;
        
        mPathDragging = Path2d( BSpline2f( mCurvesDragging, 2, false, true ) );
        mPathDragging.scale(Vec2f(100,100));
        
    }
}

void ColourCorrectionWindow::OnMouseLeave(){
    mIsMouseDragging = false;
}

void ColourCorrectionWindow::OnBoundsChanged( Gwen::Rect oldBounds ){
    Base::OnBoundsChanged( oldBounds );
    setColourBounds();
}

void ColourCorrectionWindow::onButtonPressed(Gwen::Controls::Base* pControl){
    Gwen::Controls::Button* button = ( Gwen::Controls::Button* ) pControl;
    String str = button->GetText().Get();
    if(str.compare("Save") == 0){
        saveSettings();
    }
}

void ColourCorrectionWindow::connectColorValues(vector<char>* r,vector<char>* g,vector<char>* b,vector<char>* i){
    mColorValuesConnected.push_back(r);
    mColorValuesConnected.push_back(g);
    mColorValuesConnected.push_back(b);
    mColorValuesConnected.push_back(i);
    bColorValuesConnected = true;
}

void ColourCorrectionWindow::recalculateColorValues(){
    if(!bColorValuesConnected) return;
    for(int i=0;i<mColorValuesConnected.size();i++){
        getColorValues(mColorValuesConnected[i],i);
    }
}