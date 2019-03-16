//! @file     NSUIView.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

@class NSUIViewController;

//----------------------------------------------------------------------------
// NSUIView
//----------------------------------------------------------------------------

@interface NSUIView : UIView
{    
@private
    NSUIViewController*	mUIViewController;
}

@property (strong, nonatomic) NSUIViewController* UIViewController;

//! Creates an initializes an EAGLView with a frame and 0-bit depth buffer, and a RGB565 color buffer.
+ (id) viewWithFrame:(CGRect)frame;
//! Creates an initializes an EAGLView with a frame, a color buffer format, and 0-bit depth buffer.
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format;

//! Initializes an EAGLView with a frame and 0-bit depth buffer, and a RGB565 color buffer.
- (id) initWithFrame:(CGRect)frame;
//! Initializes an EAGLView with a frame, a color buffer format, and 0-bit depth buffer.
- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format;

//!	Get the view size.
- (CGSize) getSize;

//!	Initialize the content scale factor.
- (void) InitContentScaleFactor;
//!	Initialize the GL layer.
- (void) InitGLLayer:(NSString*)format;

//!	Create gesture recognizers.
- (void) createGestureRecognizers;

//!	The gesture recognizer event receiver.
- (IBAction) handlePinchGesture:(UIGestureRecognizer*)sender;

//!	Touches event.
- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event;
- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event;
- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event;

@end