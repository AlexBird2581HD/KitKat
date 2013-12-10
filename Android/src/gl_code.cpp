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
#include <time.h>

#include <Engine.h>
#include <Debug.h>

#include <FileReader.h>

using namespace KitKat;

Engine* engine = new Engine();

inline long TimeDifference(const struct timespec& last, const struct timespec& current)
{
    // Note: There are 1000000000 nanoseconds in each second
    if (current.tv_sec > last.tv_sec)
        return (1000000000 - last.tv_nsec) + current.tv_nsec;
    else
        return current.tv_nsec - last.tv_nsec;
}

float deltaTime = 0.0f;
static struct timespec lastTime;

void renderFrame() {
	engine->Update(deltaTime);
	engine->Draw();

	struct timespec currTime;
	clock_gettime(CLOCK_MONOTONIC, &currTime);

	// TimeDifference returns nanoseconds
	deltaTime = TimeDifference(lastTime, currTime) / 1e9;
	lastTime = currTime;
}

extern "C" {
							//Java kakkaa, hyi. Activity_Library_function
    JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_step(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_GetManager(JNIEnv* env, jclass clazz, jobject assetManager);
};

JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	//enter native
    engine->Init(width, height);
	clock_gettime(CLOCK_MONOTONIC, &lastTime);
}

JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_com_android_KaNot_KaNotLib_GetManager(JNIEnv* env, jclass clazz, jobject assetManager)
{
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	FileReader::mgr = mgr;
}
