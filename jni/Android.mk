# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libKaNot
LOCAL_CFLAGS    := -Werror

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../Android/include \
					$(LOCAL_PATH)/../Common/include

# Android specific files
LOCAL_SRC_FILES :=  ../Android/src/gl_code.cpp \
					../Android/src/FileReader.cpp
# Common engine files
LOCAL_SRC_FILES += 	../Common/src/Engine.cpp \
					../Common/src/Debug.cpp \
					../Common/src/Graphics.cpp \
					../Common/src/Shader.cpp \
					../Common/src/Mathlibrary.cpp

LOCAL_LDLIBS    := -llog -lGLESv2 -landroid

include $(BUILD_SHARED_LIBRARY)
