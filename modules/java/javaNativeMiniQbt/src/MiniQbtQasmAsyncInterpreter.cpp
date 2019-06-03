#include "MiniQbtQasmAsyncInterpreter.hpp"
#include <miniqbt/MiniQbt.hpp>
#include<stdio.h>

JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_init (JNIEnv *env, jobject obj) {
    // get the ID of nativeQuasmPointer
    jfieldID fid = env->GetFieldID(
        env->GetObjectClass(obj),
        "nativeQuasmPointer", 
        "L");
    MiniQbt::QasmAsyncInterpreter* interpreter = new MiniQbt::QasmAsyncInterpreter();
    // store the pointer in java
    long a = reinterpret_cast<long>(&interpreter);
    env->SetLongField(obj, fid, a);

}

JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_interpret (JNIEnv *env, jobject, jstring src){
    const char *inCStr = env->GetStringUTFChars(src, nullptr);
    printf("test: %s", inCStr);
    env->ReleaseStringUTFChars(src, inCStr);
}

JNIEXPORT jboolean JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_hasErrors (JNIEnv *env, jobject){
    jclass clazz = (*env).FindClass("java/util/ArrayList");
    //jobject obj = (*env)->NewObject(clazz, (*env).GetMethodID(clazz, "<init>", "()V"));

    return true;
}

JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_dispose (JNIEnv *env, jobject obj) {
    jfieldID fid = env->GetFieldID(
        env->GetObjectClass(obj),
        "nativeQuasmPointer", 
        "L");
    if (fid != 0) {
       // MiniQbt::QasmAsyncInterpreter* interpreter = &fid;
    }

}