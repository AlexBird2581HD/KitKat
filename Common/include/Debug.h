#ifndef DEBUG_H
#define DEBUG_H

// Define log functions for android and windows
#ifdef _WIN32
#define  LOGI(...)  printDebug(false, __VA_ARGS__)
#define  LOGE(...)  printDebug(true, __VA_ARGS__)

void printDebug(bool error, const char* message);

#else
#include <android/log.h>
#define  LOG_TAG    "libKaNot"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif
// End of definition

#endif