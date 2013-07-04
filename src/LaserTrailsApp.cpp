#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "WindowManager.h"

#include "CinderIldaFrame.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LaserTrailsApp : public AppNative {
    
  public:
	void setup();
    void shutdown();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
private:
    
    WindowManager mWindowManager;
    
};

void LaserTrailsApp::shutdown(){
    console() << "Exit" << std::endl;
}

void LaserTrailsApp::setup()
{
 	// TODO: find a better way..
#if defined( CINDER_COCOA )
	fs::path rootPath = getAppPath().parent_path().parent_path().parent_path().parent_path().parent_path().parent_path();
#else
	fs::path rootPath = getAppPath().parent_path().parent_path().parent_path().parent_path().parent_path();
#endif
//	addAssetDirectory( rootPath / "assets" );
   
    
    
    setWindowSize(1280, 800);
    setWindowPos((getDisplay()->getWidth() - getWindowWidth()) / 2 , (getDisplay()->getHeight() - getWindowHeight()) / 2);
    mWindowManager.setup();
    
//    mWindowManager.getColorValueController()->getColorValues(&laserComm.mColorTableRed,0);
//    mWindowManager.getColorValueController()->getColorValues(&laserComm.mColorTableGreen,1);
//    mWindowManager.getColorValueController()->getColorValues(&laserComm.mColorTableBlue,2);
//    mWindowManager.getColorValueController()->getColorValues(&laserComm.mColorTableIntensity,3);
//
//    mWindowManager.getColorValueController()->connectColorValues(&laserComm.mColorTableRed,&laserComm.mColorTableGreen,&laserComm.mColorTableBlue,&laserComm.mColorTableIntensity);
}

void LaserTrailsApp::mouseDown( MouseEvent event )
{
}

void LaserTrailsApp::update()
{
    mWindowManager.update();
}

void LaserTrailsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    float ratioX = getWindowWidth() / 4096.0f;
    float ratioY = getWindowHeight() / 4096.0f;
    float percent = (float)getMousePos().x/(float)getDisplay()->getWidth();
//    l = min(l,max(0,(int)(l * percent)));
    
    
    mWindowManager.draw();
    
}

CINDER_APP_NATIVE( LaserTrailsApp, RendererGl )
