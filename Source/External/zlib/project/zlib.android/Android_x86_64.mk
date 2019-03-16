LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


APP_PLATFORM := android-9


APP_STL := c++_static


LOCAL_MODULE_FILENAME := \
libzlib-android

LOCAL_MODULE := \
zlib-android

LOCAL_SRC_FILES := \
../../adler32.c \
../../compress.c \
../../crc32.c \
../../deflate.c \
../../gzclose.c \
../../gzlib.c \
../../gzread.c \
../../gzwrite.c \
../../infback.c \
../../inffast.c \
../../inflate.c \
../../inftrees.c \
../../trees.c \
../../uncompr.c \
../../zutil.c \


LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../../../../Include \
$(LOCAL_PATH)/../../../../../../Document/Resources \
$(LOCAL_PATH)/../../../../../Source \
$(LOCAL_PATH)/../../../../../Source/External \
$(LOCAL_PATH)/../../../../../Source/Module \
$(LOCAL_PATH)/../../ \



LOCAL_CFLAGS := \
 -DNDEBUG -D_NDEBUG -D_LIB -D_PLATFORM_ANDROID_ -DANDROID -D__ANDROID__ -DNO_MALLINFO -Wno-c++11-narrowing -Wno-sign-compare -Wno-unused-local-typedefs -fshort-wchar -ffast-math -fno-rtti -fno-exceptions -mfloat-abi=softfp -w


LOCAL_CPPFLAGS := \
 -std=c++11

include $(BUILD_STATIC_LIBRARY)




