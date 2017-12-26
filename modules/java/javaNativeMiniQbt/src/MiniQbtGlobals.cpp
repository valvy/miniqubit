#include "MiniQbtGlobals.hpp"
#include <miniqbt/MiniQbt.hpp>
#include <string.h>
JNIEXPORT jstring JNICALL
Java_nl_hvanderheijden_miniqbt_Globals_getName (JNIEnv *env, jobject obj) {
    return env->NewStringUTF(MiniQbt::NAME);
}


JNIEXPORT jstring JNICALL Java_nl_hvanderheijden_miniqbt_Globals_getVersion (JNIEnv *env, jobject){
    return env->NewStringUTF(MiniQbt::VERSION);
}