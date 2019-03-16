//! @file     NSEditBoxView.mm
//! @author   foreven
//! @version  1.1
//! @date     2013/09/24
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NSEditBoxView Implementation
//----------------------------------------------------------------------------

@implementation NSEditBoxView
@synthesize mUITextField, mParentView;

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self confirmTextField];
}

-(id) initWithFrame:(CGRect)frame
{
    if ( (self = [super initWithFrame:frame] ) )
    { 
        self.backgroundColor = [UIColor colorWithRed: 0.0 green:0.0 blue:0.0 alpha: 0.5 ];
        
        mUITextField  = [[UITextField alloc] init];
        mUITextField.backgroundColor = [UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:1.0];
        mUITextField.borderStyle = UITextBorderStyleRoundedRect;
        mUITextField.delegate = self;
        
        [self addSubview:mUITextField];
         
        self.hidden = YES;
            }
    return self;
}

- ( void ) destroyView
{
    [mUITextField removeFromSuperview];
    [self removeFromSuperview];
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
	return YES;
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)textField
{
	return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
	// Check max length
	if ( mMaxLength != -1 )
	{
		NSInteger length = [textField.text length] + string.length - range.length;
		if ( length > mMaxLength )
			return NO;
	}
	
	// Convert string to UTF-16
	WString string_utf16 = NSPlatform::NSStringToUtf16( string );
	
	// Check character filter
	for ( _dword i = 0; i < string_utf16.GetLength( ); i ++ )
	{
		_charw char_code = string_utf16[i];
		
		// 3x3 Input Grid, see referenced website: http://blog.csdn.net/chen_zw/article/details/50589068
		if ( char_code == 65292 || (char_code >= 10122 && char_code <= 10130) )
			continue;

		if ( mEditBoxDelegate->mCheckCharacterFunc.InvokeR( char_code ) == _false )
			return NO;
	}

	return YES;
}

- (void) filterTextField
{
	WString editbox_text = (const _charw*)[mUITextField.text cStringUsingEncoding:NSUnicodeStringEncoding];

	// Check character filter
	for ( _dword i = 0; i < editbox_text.GetLength( ); i ++ )
	{
		_charw char_code = editbox_text[i];
		
		if ( mEditBoxDelegate->mCheckCharacterFunc.InvokeR( char_code ) == _false )
			editbox_text.Remove( i --, 1 );
	}
	
	// Feedback to text filed
	mUITextField.text = NSPlatform( ).Utf16ToNSString( editbox_text );
}

- (void) createTextField: (_dword) editbox_type inittext:(UStringPtr) inittext default_text:(UStringPtr) default_text edit_delegate:(iosEditBox*) edit_delegate parent_view:(NSUIView*) parent_view  max_length:(_dword) max_length
{
	mMaxLength = max_length;
    mEditBoxDelegate = edit_delegate;
    mParentView = parent_view;

    self.hidden = NO;

    mUITextField.returnKeyType = UIReturnKeyDone;
    mUITextField.contentVerticalAlignment = UIControlContentVerticalAlignmentTop;
    
    switch ( editbox_type )
    {
        case IEditBox::_INPUT_TYPE_NORMAL:
            [mUITextField setKeyboardType:UIKeyboardTypeDefault];
            break;
        case IEditBox::_INPUT_TYPE_URL:
            [mUITextField setKeyboardType:UIKeyboardTypeURL];
            break;
        case IEditBox::_INPUT_TYPE_NUMBER_PAD:
            [mUITextField setKeyboardType:UIKeyboardTypeNumberPad];
            break;
        case IEditBox::_INPUT_TYPE_PHONE_PAD:
            [mUITextField setKeyboardType:UIKeyboardTypePhonePad];
            break;
        case IEditBox::_INPUT_TYPE_EMAIL_ADDRESS:
            [mUITextField setKeyboardType:UIKeyboardTypeEmailAddress];
            break;
		case IEditBox::_INPUT_TYPE_PASSWORD:
			[mUITextField setKeyboardType:UIKeyboardTypeDefault];
			mUITextField.secureTextEntry = _true;
			break;
        default:
            [mUITextField setKeyboardType:UIKeyboardTypeDefault];
            break;
    }
    
    //mTextField.placeholder = @"<Enter Text>";
    
    mUITextField.text = [NSString stringWithUTF8String:inittext.Str( )];
	mUITextField.placeholder = [NSString stringWithUTF8String:default_text.Str( )];
	
    [parent_view addSubview:self];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
    // 键盘高度变化通知，ios5.0新增的
    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    if (version >= 5.0) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillChangeFrameNotification object:nil];
    }
    
    [mUITextField becomeFirstResponder];
}

- (void)keyboardWillShow:(NSNotification *)notification
{
    if ( mParentView == nil )
        return;
    
    NSDictionary* info = [notification userInfo];
	CGSize frame_size = self.frame.size;
    CGSize kbSize = [[ info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;
	float version = [[[UIDevice currentDevice] systemVersion] floatValue];
	if ( version < 8.0 )
		Math::Swap( kbSize.width, kbSize.height );
	
	// Use the default region to show
	_float editbox_width	= kbSize.width;
	_float editbox_height	= frame_size.height - kbSize.height;
	mUITextField.frame = CGRectMake( 0, 0, editbox_width, editbox_height );

    mEditBoxDelegate->mHandleEventFunc.Invoke( IEditBox::_EVENT_OPEN, "" );
}

- (void) destroyTextField
{
    mParentView = nil;
    
	[mUITextField resignFirstResponder];
    [self setHidden:YES];
    
    [[NSNotificationCenter defaultCenter]removeObserver:self];
}

- (void) confirmTextField
{
	[self filterTextField];
	
	[self destroyTextField];
    
    UString editbox_text = [mUITextField.text cStringUsingEncoding:NSUTF8StringEncoding];
    
    mEditBoxDelegate->mHandleEventFunc.Invoke( IEditBox::_EVENT_RETURN, editbox_text );
    
	return; 
}

- (void) cancelTextField
{
	[self filterTextField];

	[self destroyTextField];

	UString editbox_text = [mUITextField.text cStringUsingEncoding:NSUTF8StringEncoding];
    
    mEditBoxDelegate->mHandleEventFunc.Invoke( IEditBox::_EVENT_CANCEL, editbox_text );
}

- (BOOL) textFieldShouldReturn:(UITextField* ) textField
{
	[self filterTextField];

	[self destroyTextField];

	UString editbox_text = [mUITextField.text cStringUsingEncoding:NSUTF8StringEncoding];
    
    mEditBoxDelegate->mHandleEventFunc.Invoke( IEditBox::_EVENT_RETURN, editbox_text );
    
	return YES;
}

@end
