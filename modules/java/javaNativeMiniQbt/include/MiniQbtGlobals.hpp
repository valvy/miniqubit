#ifndef MINIQBT_GLOBALS_WRAPPEr_HPP
#define MINIQBT_GLOBALS_WRAPPER_HPP
#include <jni.h>

extern "C" {
    JNIEXPORT jstring JNICALL Java_nl_hvanderheijden_miniqbt_Globals_getName (JNIEnv *, jobject);

    JNIEXPORT jstring JNICALL Java_nl_hvanderheijden_miniqbt_Globals_getVersion (JNIEnv *, jobject);
}

#endif