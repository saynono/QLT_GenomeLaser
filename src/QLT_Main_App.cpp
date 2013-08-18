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
    void saveApplicationSettings();
	void update();
	void draw();
    void keyDown( KeyEvent event );
    
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
    
    mMainController.getDataSaver()->loadAppSettings("");
    
    gl::disableDepthRead();
    gl::disableDepthWrite();
    gl::enableVerticalSync();
        
}


void QLT_Main_App::shutdown(){
    console() << "Exit. ByeBye..." << std::endl;
}

void QLT_Main_App::saveApplicationSettings(){
    
}

void QLT_Main_App::update(){
    
    mMainController.update();
    mViewManager.update();
    mWindowManager.update();

    mLaserController->setPoints( mMainController.getFrame() );
    mLaserController->send();
}

void QLT_Main_App::draw()
{
    
	gl::clear( ci::Color( 0x26/255.f,0x27/255.f,0x26/255.f ) );
    gl::setViewport( getWindowBounds() );
    
    mWindowManager.draw();
    
}

void QLT_Main_App::keyDown( KeyEvent event )
{
    switch(event.getCode()){
//        case 'l':
//            mWindowManager.reloadSkin();
//            break;
        case 'q':
//            quit();
            break;
        case 27:
//            quit();
            break;
        case 282:
        case 283:
        case 284:
        case 285:
            mMainController.getDataController()->toggleCrawlerActivity(event.getCode()-282);
            break;
        default:
            console() << "event.getCode() : " << event.getCode() << std::endl;
    }
}


CINDER_APP_NATIVE( QLT_Main_App, RendererGl )
