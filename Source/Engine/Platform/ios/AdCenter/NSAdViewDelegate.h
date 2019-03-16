//! @file     NSAdViewDelegate.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// NSAdViewDelegate
//----------------------------------------------------------------------------

@interface NSAdViewDelegate : NSObject< AdMoGoDelegate >
{
@private
	UIViewController* mViewController;
}

@property (nonatomic, assign) UIViewController* ViewController;

@end