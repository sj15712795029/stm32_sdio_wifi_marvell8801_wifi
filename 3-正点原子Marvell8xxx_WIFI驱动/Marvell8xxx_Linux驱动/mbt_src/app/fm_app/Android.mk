LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := fm_main.c
LOCAL_SHARED_LIBRARIES := libc libcutils
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_MODULE = fmapp
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)


