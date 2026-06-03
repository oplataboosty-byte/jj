LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# Lib name — must match System.loadLibrary("gvraudio") in ActivityMain.java
LOCAL_MODULE    := gvraudio

# 64-bit ARM optimizations
LOCAL_CFLAGS := -Wno-error=format-security -fpermissive -fvisibility=hidden -fvisibility-inlines-hidden
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -g0 -fomit-frame-pointer -ffunction-sections -fdata-sections
LOCAL_CPPFLAGS += -fvisibility=hidden -ffunction-sections -fdata-sections
LOCAL_LDFLAGS += -Wl,--strip-all

LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH)
LOCAL_SRC_FILES := main.cpp \
   Substrate/SubstrateDebug.cpp \
   Substrate/SubstrateHook.cpp \
   Substrate/SubstratePosixMemory.cpp \
   KittyMemory/KittyMemory.cpp \
   KittyMemory/MemoryPatch.cpp \
   KittyMemory/MemoryBackup.cpp \
   KittyMemory/KittyUtils.cpp \

LOCAL_LDLIBS := -llog -landroid -lGLESv2

include $(BUILD_SHARED_LIBRARY)
