/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code

#include <jni.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <Engine.h>
#include <Debug.h>

Engine* engine = new Engine();

void renderFrame() {
	engine->Update();
	engine->Draw();
}

extern "C" {
							//Java kakkaa, hyi. Activity_Library_function
    JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_step(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	//enter native
    engine->Init(width, height);
}

JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}
