#include "MiniQbtQasmAsyncInterpreter.hpp"
#include <miniqbt/MiniQbt.hpp>
#include<stdio.h>

using namespace MiniQbt;

constexpr char POINTER_NAME[] = "nativeQasmPointer";
constexpr char POINTER_TYPE[] = "J";

QasmAsyncInterpreter* getInterpreterFromMemory(JNIEnv *env, jobject obj) {
    jclass wrapperClass = env->GetObjectClass(obj);
    const jfieldID fid = env->GetFieldID(
        wrapperClass,
        POINTER_NAME, 
        POINTER_TYPE);

    const jlong pointer = env->GetLongField(obj, fid);
    if(pointer != 0) {
        return reinterpret_cast<QasmAsyncInterpreter*>(pointer);
    }
    return nullptr;
}


JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_init (JNIEnv *env, jobject obj) {
    // Get the ID of nativeQuasmPointer
    jclass wrapperClass = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(
        wrapperClass,
        POINTER_NAME, 
        POINTER_TYPE);
    QasmAsyncInterpreter* interpreter = new QasmAsyncInterpreter();
    // Store the pointer in java
    jlong a = reinterpret_cast<jlong>(interpreter);
    env->SetLongField(obj, fid, a);
}

JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_interpret (JNIEnv *env, jobject obj, jstring src){
    const char *inCStr = env->GetStringUTFChars(src, nullptr);
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    interpreter->interpret(std::string(inCStr));
    env->ReleaseStringUTFChars(src, inCStr);
}

JNIEXPORT jboolean JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_hasErrors (JNIEnv *env, jobject obj){
    jclass clazz = (*env).FindClass("java/util/ArrayList");
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    return interpreter->hasErrors();
}

JNIEXPORT jstring JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_getError (JNIEnv *env, jobject obj) {
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    std::string res = interpreter->getError();
    return env->NewStringUTF(res.c_str());
    
}

JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_dispose (JNIEnv *env, jobject obj) {
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    jclass wrapperClass = env->GetObjectClass(obj);
    const jfieldID fid = env->GetFieldID(
        wrapperClass,
        POINTER_NAME, 
        POINTER_TYPE);

   if(getInterpreterFromMemory(env,obj) != nullptr) {
       env->SetLongField(obj, fid, 0); // Make sure it points to zero
       delete interpreter;
   }
}