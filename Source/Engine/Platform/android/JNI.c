//! @file     androidPlatform.cpp
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include <jni.h>
#include <pthread.h>
#include <android/log.h>

JNIEXPORT void JNICALL Java_com_ege_android_AndroidEditBox_OnInitJNI( JNIEnv* env, jobject obj )
{
	__android_log_print( ANDROID_LOG_INFO, "ege_android_app", "Java_com_ege_android_AndroidEditBox_OnInitJNI()" );
}