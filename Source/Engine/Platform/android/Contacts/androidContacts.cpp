//! @file     androidContacts.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// androidContacts Implementation
//----------------------------------------------------------------------------

#define Java_AndroidUtils_ClassPath "com/ege/android/AndroidUtils"
#define Java_ContactEntry_ClassPath "com/ege/android/ContactEntry"
#define Java_ContactEntry_Signature "L"##ContactEntry_ClassPath##";"

androidContacts::androidContacts( )
{
}

androidContacts::~androidContacts( )
{
}

void androidContacts::Refresh( )
{
	mObjects.Clear();

	jobject context = androidJNI::GetInstance( ).GetContextObj();

	jclass utilClass = androidJNI::GetInstance( ).GetJNIEnv( )->FindClass(Java_AndroidUtils_ClassPath);
	jmethodID readContactsMethodID = androidJNI::GetInstance( ).GetJNIEnv( )->GetStaticMethodID(utilClass, "readContacts", "(Landroid/content/Context;)Ljava/util/List;");
	jobject contactEntryList = androidJNI::GetInstance( ).GetJNIEnv( )->CallStaticObjectMethod(utilClass, readContactsMethodID, context);

	jclass listClass = androidJNI::GetInstance( ).GetJNIEnv( )->FindClass("java/util/List");
	jmethodID sizeMethodID = androidJNI::GetInstance( ).GetJNIEnv( )->GetMethodID(listClass, "size", "()I");
	jmethodID getMethodID = androidJNI::GetInstance( ).GetJNIEnv( )->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");

	jclass contactEntryClass = androidJNI::GetInstance( ).GetJNIEnv( )->FindClass("com/ege/android/ContactEntry");

	if(!contactEntryClass)
	{
		ALOG_TRACE("contactEntryClass is null");
	}

	jfieldID nameFieldID = androidJNI::GetInstance( ).GetJNIEnv( )->GetFieldID(contactEntryClass, "Name", "Ljava/lang/String;");
	jfieldID phoneNumbersFieldID = androidJNI::GetInstance( ).GetJNIEnv( )->GetFieldID(contactEntryClass, "PhoneNumbers", "Ljava/util/List;");

	jint listSize = androidJNI::GetInstance( ).GetJNIEnv( )->CallIntMethod(contactEntryList, sizeMethodID);
	
	for(int i = 0; i < listSize; ++i)
	{
		ObjInfo info;

		jobject contactEntry = androidJNI::GetInstance( ).GetJNIEnv( )->CallObjectMethod(contactEntryList, getMethodID, i);
		jstring name = (jstring)androidJNI::GetInstance( ).GetJNIEnv( )->GetObjectField(contactEntry, nameFieldID);
		jobject phoneNumberList = androidJNI::GetInstance( ).GetJNIEnv( )->GetObjectField(contactEntry, phoneNumbersFieldID);

		info.mName = J2CString( name ).ToStringW( );

		jint phoneNumberListSize = androidJNI::GetInstance( ).GetJNIEnv( )->CallIntMethod(phoneNumberList, sizeMethodID);
		for(int j = 0; j < phoneNumberListSize; ++j)
		{
			jstring phoneNumber = (jstring)androidJNI::GetInstance( ).GetJNIEnv( )->CallObjectMethod(phoneNumberList, getMethodID, j);
			info.mPhoneNumbers.Append(J2CString( phoneNumber ).ToStringW( ));
		}

		mObjects.Append(info);
	}
}

const IContacts::ObjInfoArray& androidContacts::GetObjects( ) const
{
	return mObjects;
}