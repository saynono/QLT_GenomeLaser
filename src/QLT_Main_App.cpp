#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"

#include "CinderIldaFrame.h"
#include "CinderEtherdream.h"


#include "DataToShapeConverter.h"
#include "WindowManager.h"
#include "LaserPreview3D.h"
#include "CircularDataLayer.h"
#include "DataManager.h"


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
    LaserPreview3D              mLaserPreview3D;
    CircularDataLayer           mCircDataLayer;
    DataManager                 mDataManager;
    DataToShapeConverter        mShapeConverter;
    int                         mDataCounter;
    
};

void QLT_Main_App::shutdown(){
    console() << "Exit" << std::endl;
}

void QLT_Main_App::setup()
{

    mDataCounter = 0;
    
    gl::enableVerticalSync();
    
    mDataManager.setup();
    mShapeConverter.setup();

    
    setWindowSize(getDisplay()->getWidth()-100, getDisplay()->getHeight()-100);
    setWindowPos((getDisplay()->getWidth() - getWindowWidth()) / 2 , (getDisplay()->getHeight() - getWindowHeight()) / 2);
    mWindowManager.setup();
    
    mLaserController = new ciilda::Etherdream();
    mLaserController->setup();

    createInitialLaser();

    mLaserPreview3D.setup( &mIldaFrame,1024,1024 );
    mCircDataLayer.setup(1024,1024);
    mCircDataLayer.setDataBuffer(mDataManager.getDataBuffer());
    mCircDataLayer.updateLayer(100,10000);
    
    mWindowManager.setPreviewFbo( mLaserPreview3D.getTexture() );
    mWindowManager.setLaserPreview3d( &mLaserPreview3D );
    mWindowManager.setCircularDataLayer( &mCircDataLayer );
    mWindowManager.setIldaFrame(&mIldaFrame);
    mWindowManager.setLaserController(mLaserController);
    gl::disableDepthRead();
    gl::disableDepthWrite();

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
    matrix.scale(.4);
    
    triangle.transform(matrix);
    something.transform(matrix);
    shapeOrg.transform(matrix);
    
    matrix.setToIdentity();
    matrix.translate( Vec2f(0.5,0.5) );
    triangle.transform(matrix);
    something.transform(matrix);
    shapeOrg.transform(matrix);
    
    mIldaFrame.begin();
    mIldaFrame.addShape2d(shapeOrg,ColorA(1,0,0,1));
    mIldaFrame.addPath2d(something);
    mIldaFrame.addPath2d(triangle, ColorA(1,0,1,1));
    mIldaFrame.moveTo(Vec2f(.2,.2));
    mIldaFrame.lineTo(Vec2f(.8,.2));
    mIldaFrame.setColor( ColorA(.5,.4,.2,.7) );
    mIldaFrame.lineTo(Vec2f(.8,.8));
    mIldaFrame.lineTo(Vec2f(.2,.8));
    mIldaFrame.lineTo(Vec2f(.2,.2));
    mIldaFrame.end();
    mLaserController->setPoints(mIldaFrame);
    mLaserController->send();

}

void QLT_Main_App::update()
{
    
    float speed = 1.1f;
    float dc = (getElapsedSeconds() * speed);
    if( (int)dc != mDataCounter){
        mDataCounter = (int)dc;
        char d = mDataManager.getNextData();
        Shape2d s = mShapeConverter.convertChar(d);
        mIldaFrame.begin();
        mIldaFrame.setColor( ColorA(.5,.4,.2,.7) );
        mIldaFrame.moveTo(Vec2f(.2,.2));
        mIldaFrame.lineTo(Vec2f(.8,.2));
        mIldaFrame.lineTo(Vec2f(.8,.8));
        mIldaFrame.lineTo(Vec2f(.2,.8));
        mIldaFrame.lineTo(Vec2f(.2,.2));
//        mIldaFrame.setColor( ColorA(1,1,1,1) );
        mIldaFrame.setColor( ColorA(.5,.4,.2,.7) );
        mIldaFrame.addShape2d( s );
        mIldaFrame.end();
        mLaserController->setPoints(mIldaFrame);
        mLaserController->send();
    }else{
        if( dc-mDataCounter > .9 ){
//            char d = '_';
//            Shape2d s = mShapeConverter.convertChar(d);
//            mIldaFrame.begin();
//            mIldaFrame.addShape2d( s );
//            mIldaFrame.end();
//            mLaserController->setPoints(mIldaFrame);
//            mLaserController->send();
        }
    }
    
    mLaserPreview3D.update();
    mCircDataLayer.updateLayer(100,10000);

    mWindowManager.update();
    mLaserController->setPoints(mIldaFrame);
    mLaserController->send();
}

void QLT_Main_App::draw()
{
    
	gl::clear( ci::Color( 0, 0, 0 ) );
    gl::setViewport( getWindowBounds() );
    
    mLaserPreview3D.draw();
    
    mWindowManager.draw();

}


CINDER_APP_NATIVE( QLT_Main_App, RendererGl )
