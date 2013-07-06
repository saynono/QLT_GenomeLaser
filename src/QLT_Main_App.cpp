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
    
    ciilda::Etherdream      mEtherdream;
    ciilda::Frame           mIldaFrame;
    
    ci::gl::Fbo             mPreviewFbo;
    
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
    mEtherdream.setup();

    createInitialLaser();

	gl::Fbo::Format format;
    //	format.setSamples( 2 ); // uncomment this to enable 4x antialiasing
	mPreviewFbo = gl::Fbo( 1000, 1000, format );
    mWindowManager.setPreviewFbo(&mPreviewFbo);
    mWindowManager.setIldaFrame(&mIldaFrame);
    
    
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
    mIldaFrame.moveTo(Vec2f(.3,.2));
    mIldaFrame.lineTo(Vec2f(.6,.2));
    mIldaFrame.lineTo(Vec2f(.6,.6));
    mIldaFrame.end();
}

void QLT_Main_App::update()
{
    mWindowManager.update();
}

void QLT_Main_App::draw()
{

    mPreviewFbo.bindFramebuffer();
	gl::clear( Color( 0, 0, 0 ) );
    mIldaFrame.draw(0,0,mPreviewFbo.getWidth(),mPreviewFbo.getHeight());
    mPreviewFbo.unbindFramebuffer();

    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
//    float ratioX = getWindowWidth() / 4096.0f;
//    float ratioY = getWindowHeight() / 4096.0f;
//    float percent = (float)getMousePos().x/(float)getDisplay()->getWidth();
//    l = min(l,max(0,(int)(l * percent)));
    
    mWindowManager.draw();
    
    
//    mIldaFrame.draw(10,10,300,300);
//    
//    gl::draw( mPreviewFbo.getTexture(),Rectf(10,320,300,600) );

//    gl::draw( mPreviewFbo.getTexture() );
    
}

CINDER_APP_NATIVE( QLT_Main_App, RendererGl )
