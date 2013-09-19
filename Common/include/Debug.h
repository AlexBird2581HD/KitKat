#ifndef DEBUG_H
#define DEBUG_H

// Define log functions for android and windows
// OpenGL headers needed for OpenGL debug functions
#ifdef _WIN32 // Windows functions
#include <OpenGL.h>
#define  LOGI(...)  printDebug(false, __VA_ARGS__) // Info
#define  LOGE(...)  printDebug(true, __VA_ARGS__) // Error

void printDebug(bool error, const char* format, ...); // Function to print the log

#else // Android functions
#include <android/log.h>
#include <GLES2/gl2.h>
#define  LOG_TAG    "libKaNot"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__) // Info
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__) // Error
#endif
// End of definition

// Debug functions
void printGLString(const char *name, GLenum s);
void checkGlError(const char* op);
#endif