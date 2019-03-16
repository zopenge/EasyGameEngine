//! @file     NSAccelerometerDelegate.H
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/09/24

#pragma once

@interface NSAccelerometerDelegate : NSObject< UIAccelerometerDelegate >
{
@private
    EGE::IViewBasedApp*  mViewBasedApp;
}

- (void)SetViewbasedApp: (EGE::IViewBasedApp*) viewbased_app;
@end