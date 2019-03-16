//! @file     NSUIView.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NSUIView Implementation
//----------------------------------------------------------------------------

@implementation NSUIView
@synthesize UIViewController = mUIViewController;

+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

+ (id) viewWithFrame:(CGRect)frame
{
	return [[self alloc] initWithFrame:frame];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format
{
	return [[self alloc] initWithFrame:frame pixelFormat:format];
}

- (id) initWithFrame:(CGRect)frame
{
	return [self initWithFrame:frame pixelFormat:kEAGLColorFormatRGB565];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format 
{	
	// Create graphic layer for OpenGLES
	if ( self = [super initWithFrame:frame] )
	{
		// Initialize the content scale factor
		[self InitContentScaleFactor];

		// Initialize the GL layer
		[self InitGLLayer:format];
	}
	
	// Enable view features
	self.multipleTouchEnabled = YES;

	// Create gesture recognizers
//	[self createGestureRecognizers];

	return self;
}

- (CGSize) getSize
{
	CGSize frame_size =  [self frame].size;
	frame_size.width  *= [self contentScaleFactor];
	frame_size.height *= [self contentScaleFactor];

	float version = [[[UIDevice currentDevice] systemVersion] floatValue];
	if ( version < 8.0 )
		Math::Swap( frame_size.width, frame_size.height );

	return frame_size;
}

- (void) InitContentScaleFactor
{
	// Get the frame size
	CGSize frame_size = [self frame].size;

	// Get the screen size
	PointU screen_size = NS_ScreenGetSize( );
	
	// Initialize the UI view size by main screen size ( use the max size to compare )
	_float scale = EGE_RATIO( Math::Max( screen_size.x, screen_size.y ), Math::Max( frame_size.width, frame_size.height ) );
    self.contentScaleFactor = scale;
}

- (void) InitGLLayer:(NSString*)format
{
	CAEAGLLayer* layer = (CAEAGLLayer*) self.layer;
	EGE_ASSERT( layer != _null );
		
    layer.contentsScale         = self.contentScaleFactor;
	layer.opaque				= YES;
	layer.drawableProperties	= [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO],
		kEAGLDrawablePropertyRetainedBacking,
		format, 
		kEAGLDrawablePropertyColorFormat, 
		nil];
}

- (void) createGestureRecognizers 
{
	// Creat ethe pinch gesture recognizer
    UIPinchGestureRecognizer* pinch_gesture = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(handlePinchGesture:)];
    [self addGestureRecognizer:pinch_gesture];
}

- (IBAction) handlePinchGesture:(UIGestureRecognizer*)sender 
{
    CGFloat						factor	= [(UIPinchGestureRecognizer*)sender scale];
    UIGestureRecognizerState	state	= [(UIPinchGestureRecognizer*)sender state];
	
	// Determine the zoom flag
	EventPinchGesture::_ZOOM_FLAG zoom_flag = EventPinchGesture::_ZOOM_UNKNOWN;
	static CGFloat init_scale_factor = factor;
	if ( init_scale_factor < factor )
		zoom_flag = EventPinchGesture::_ZOOM_OUT;
	else if ( init_scale_factor > factor )
		zoom_flag = EventPinchGesture::_ZOOM_IN;

	init_scale_factor = factor;
	
	[mUIViewController processPinchGesture:factor zoom_flag:zoom_flag state:(EventPinchGesture::_STATE) state];
}

- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
	[mUIViewController processTouches:touches withEvent:event touches_event:EventTouch::_EVENT_BEGAN];
}

- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
	[mUIViewController processTouches:touches withEvent:event touches_event:EventTouch::_EVENT_ENDED];
}

- (void) touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
	[mUIViewController processTouches:touches withEvent:event touches_event:EventTouch::_EVENT_ENDED];
}

- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
	[mUIViewController processTouches:touches withEvent:event touches_event:EventTouch::_EVENT_MOVED];
}

@end
