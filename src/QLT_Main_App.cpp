#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "WindowManager.h"

#include "CinderIldaFrame.h"
#include "CinderEtherdream.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class QLT_Main_App : public AppNative {
    
  public:
	void setup();
    void shutdown();
    void createInitialLaser();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
private:
    
    WindowManager mWindowManager;
    
    ciilda::LaserController*    mLaserController;
    ciilda::Frame               mIldaFrame;
    
    ci::gl::Fbo                 mPreview3DFbo;
    
};

void QLT_Main_App::shutdown(){
    console() << "Exit" << std::endl;
}

void QLT_Main_App::setup()
{
 	// TODO: find a better way..
#if defined( CINDER_COCOA )
	fs::path rootPath = getAppPath().parent_path().parent_path().parent_path().parent_path().parent_path().parent_path();
#else
	fs::path rootPath = getAppPath().parent_path().parent_path().parent_path().parent_path().parent_path();
#endif
//	addAssetDirectory( rootPath / "assets" );
   
    gl::enableVerticalSync();
    
    setWindowSize(1280, 800);
    setWindowPos((getDisplay()->getWidth() - getWindowWidth()) / 2 , (getDisplay()->getHeight() - getWindowHeight()) / 2);
    mWindowManager.setup();
    
    mLaserController = new ciilda::Etherdream();
    mLaserController->setup();

    createInitialLaser();

	gl::Fbo::Format format;
    //	format.setSamples( 2 ); // uncomment this to enable 4x antialiasing
	mPreview3DFbo = gl::Fbo( 1000, 1000, format );
    mWindowManager.setPreviewFbo(&mPreview3DFbo);
    mWindowManager.setIldaFrame(&mIldaFrame);
    mWindowManager.setLaserController(mLaserController);
    
    
//    mWindowManager.getColorValueController()->getColorValues(&laserComm.mColorTableRed,0);
//    mWindowManager.getColorValueController()->getColorValues(&laserComm.mColorTableGreen,1);
//    mWindowManager.getColorValueController()->getColorValues(&laserComm.mColorTableBlue,2);
//    mWindowManager.getColorValueController()->getColorValues(&laserComm.mColorTableIntensity,3);
//
//    mWindowManager.getColorValueController()->connectColorValues(&laserComm.mColorTableRed,&laserComm.mColorTableGreen,&laserComm.mColorTableBlue,&laserComm.mColorTableIntensity);
}

void QLT_Main_App::mouseDown( MouseEvent event )
{
}

void QLT_Main_App::createInitialLaser(){
    Shape2d shapeOrg;
    shapeOrg.moveTo(Vec2f(100,100));
    shapeOrg.lineTo(Vec2f(500,100));
    shapeOrg.lineTo(Vec2f(500,450));
    shapeOrg.lineTo(Vec2f(100,450));
    shapeOrg.close();
    
    
    Path2d triangle;
    triangle.moveTo(Vec2f(Vec2f(getWindowWidth()-30,30)));
    triangle.lineTo(Vec2f(600,450));
    triangle.lineTo(Vec2f(Vec2f(30,getWindowHeight()-30)));
    
    Path2d something;
    something.moveTo(Vec2f(300,100));
    something.curveTo(Vec2f(300,150),Vec2f(150,250),Vec2f(100,250));
    //    something.close();
    
    MatrixAffine2f matrix;
    
    matrix.setToIdentity();
    matrix.translate( -Vec2f(getWindowWidth(),getWindowHeight())/2.0 );
    triangle.transform(matrix);
    something.transform(matrix);
    shapeOrg.transform(matrix);
    
    matrix.setToIdentity();
    matrix.scale(Vec2f( 1.0/(float)getWindowWidth(), 1.0/(float)getWindowHeight()));
    matrix.scale(.1);
    
    triangle.transform(matrix);
    something.transform(matrix);
    shapeOrg.transform(matrix);
    
    matrix.setToIdentity();
    matrix.translate( Vec2f(0.5,0.5) );
    triangle.transform(matrix);
    something.transform(matrix);
    shapeOrg.transform(matrix);
    
//    mIldaFrame.params.output.targetPointCount = 200;
    mIldaFrame.begin();
    mIldaFrame.addShape2d(shapeOrg,ColorA(1,0,0,1));
    mIldaFrame.addPath2d(something);
    mIldaFrame.addPath2d(triangle, ColorA(1,0,1,1));
    mIldaFrame.end();
    mLaserController->setPoints(mIldaFrame);
    mLaserController->send();
}

void QLT_Main_App::update()
{
    mWindowManager.update();
    mLaserController->setPoints(mIldaFrame);
    mLaserController->send();
}

void QLT_Main_App::draw()
{

    mPreview3DFbo.bindFramebuffer();
	gl::clear( Color( 0, 0, 0 ) );
    mIldaFrame.draw(0,0,mPreview3DFbo.getWidth(),mPreview3DFbo.getHeight());
    mPreview3DFbo.unbindFramebuffer();

	gl::clear( Color( 0, 0, 0 ) );
    
    
    mWindowManager.draw();
    
//	gl::color( Color( 1,1,1 ) );
//    gl::draw( mPreview3DFbo.getTexture() );
    
}

CINDER_APP_NATIVE( QLT_Main_App, RendererGl )
