//! @file     NSEditBoxView.h
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/09/24

#pragma once
	
@interface NSEditBoxView : UIView< UITextFieldDelegate >
{
@private
	EGE::_dword			mMaxLength;
    EGE::iosEditBox*	mEditBoxDelegate;
}

@property (nonatomic, strong) UITextField*  mUITextField;
@property (nonatomic, strong) NSUIView*     mParentView;

- (void) filterTextField;
- (void) createTextField: (EGE::_dword) editbox_type inittext:(EGE::UStringPtr) inittext default_text:(EGE::UStringPtr) default_text edit_delegate:(EGE::iosEditBox*) edit_delegate parent_view:(NSUIView*) parent_view max_length:(EGE::_dword) max_length;
- (void) destroyTextField;
- (void) confirmTextField;
- (void) cancelTextField;
- (void) destroyView;
@end
