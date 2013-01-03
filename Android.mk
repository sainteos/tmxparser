LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := TmxParser

# Find Subdirectories
APP_SUBDIRS := $(patsubst $(LOCAL_PATH)/%, %, $(shell find $(LOCAL_PATH)/TmxParser -type d))

# No zlib, zlib is already integrated in Android
LOCAL_CFLAGS := -DUSE_SDL2_LOAD -I$(LOCAL_PATH)/TmxParser -I$(LOCAL_PATH)/TmxParser/tinyxml


LOCAL_SRC_FILES := $(foreach F, $(APP_SUBDIRS), $(addprefix $(F)/,$(notdir $(wildcard $(LOCAL_PATH)/$(F)/*.cpp))))

LOCAL_LDLIBS := -lz
LOCAL_SHARED_LIBRARIES := SDL2


include $(BUILD_SHARED_LIBRARY)
