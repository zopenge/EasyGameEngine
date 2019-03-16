#include "EGEEngine.h"

JNI_FUNC_2( void, AndroidUtils, OnSMSCallback, jlong ptr, jboolean success )
{
	ALOG_TRACE( "androidSMSManager::OnSmsCallback begin");

	((ISMSResultCallback*)ptr)->OnResult(success);

	ALOG_TRACE( "androidSMSManager::OnSmsCallback OK" );
}

void androidSMSManager::SendSMS(WStringPtr phoneNumber, WStringPtr text, ISMSResultCallback* cb)
{
	jclass utilClass = androidJNI::GetInstance( ).GetJNIEnv( )->FindClass("com/ege/android/AndroidUtils");
	if(!utilClass)
	{
		ALOG_TRACE("utilClass is null");
	}

	jmethodID sendSMSMethodID = androidJNI::GetInstance( ).GetJNIEnv( )->GetStaticMethodID(
		utilClass, 
		"sendSms", 
		"(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;J)V");

	ALOG_TRACE("after get sendSms");
	if(!sendSMSMethodID)
	{
		ALOG_TRACE("sendSMSMethodID is null");
	}

	ALOG_TRACE("before translate input strings");

	jstring j_phoneNumber = C2JString(phoneNumber).ToJString();
	jstring j_text = C2JString(text).ToJString();
	
	ALOG_TRACE("before call sendSms");
	jobject j_context = androidJNI::GetInstance( ).GetContextObj();
	androidJNI::GetInstance( ).GetJNIEnv( )->CallStaticVoidMethod(utilClass, sendSMSMethodID, j_context, j_phoneNumber, j_text, (jlong)cb);
}