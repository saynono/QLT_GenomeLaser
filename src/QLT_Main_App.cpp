#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"

#include "CinderIldaFrame.h"
#include "CinderEtherdream.h"


#include "MainController.h"
#include "ViewManager.h"
#include "WindowManager.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class QLT_Main_App : public AppNative {
    
  public:
	void setup();
    void shutdown();
	void update();
	void draw();
    
private:
    
    ciilda::LaserController*    mLaserController;
    MainController              mMainController;
    ViewManager                 mViewManager;
    WindowManager               mWindowManager;
    
};

void QLT_Main_App::setup()
{
    

    setWindowSize(getDisplay()->getWidth()-100, getDisplay()->getHeight()-100);
    setWindowPos((getDisplay()->getWidth() - getWindowWidth()) / 2 , (getDisplay()->getHeight() - getWindowHeight()) / 2);
    
    mLaserController = new ciilda::Etherdream();
    mLaserController->setup();

    mMainController.setup();
    mViewManager.setup( &mMainController );
    mWindowManager.setup( &mMainController, &mViewManager );
    
    gl::disableDepthRead();
    gl::disableDepthWrite();
    gl::enableVerticalSync();
    
}


void QLT_Main_App::shutdown(){
    console() << "Exit. ByeBye..." << std::endl;
}


void QLT_Main_App::update()
{
    
    mMainController.update();
    mViewManager.update();
    mWindowManager.update();

    mLaserController->setPoints( mMainController.getFrame() );
    mLaserController->send();

}

void QLT_Main_App::draw()
{
    
	gl::clear( ci::Color( 0, 0, 0 ) );
    gl::setViewport( getWindowBounds() );
    
    mWindowManager.draw();
    
}


CINDER_APP_NATIVE( QLT_Main_App, RendererGl )
