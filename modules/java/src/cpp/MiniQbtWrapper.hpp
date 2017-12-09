#ifndef MINIQBT_WRAPPER_HPP
#define MINIQBT_WRAPPER_HPP
#include <jni.h>

extern "C" {
    JNIEXPORT jstring JNICALL Java_nl_hvanderheijden_miniqbt_Globals_getName (JNIEnv *, jobject);

     JNIEXPORT jstring JNICALL Java_nl_hvanderheijden_miniqbt_Globals_getVersion (JNIEnv *, jobject);
}

#endif