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
    // get the ID of nativeQuasmPointer
    jclass wrapperClass = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(
        wrapperClass,
        POINTER_NAME, 
        POINTER_TYPE);
    QasmAsyncInterpreter* interpreter = new QasmAsyncInterpreter();
    // store the pointer in java
    jlong a = reinterpret_cast<jlong>(interpreter);//(long int)&interpreter;
    env->SetLongField(obj, fid, a);

}

JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_interpret (JNIEnv *env, jobject obj, jstring src){
    const char *inCStr = env->GetStringUTFChars(src, nullptr);
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    interpreter->interpret(std::string(inCStr));

}

JNIEXPORT jboolean JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_hasErrors (JNIEnv *env, jobject obj){
    jclass clazz = (*env).FindClass("java/util/ArrayList");

    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);


    return interpreter->hasErrors();
}

JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_dispose (JNIEnv *env, jobject obj) {
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    jclass wrapperClass = env->GetObjectClass(obj);
    const jfieldID fid = env->GetFieldID(
        wrapperClass,
        POINTER_NAME, 
        POINTER_TYPE);

   if(getInterpreterFromMemory != nullptr) {
       env->SetLongField(obj, fid, 0); // Make sure it points to zero
       delete interpreter;
   }
   /* jclass wrapperclass = env->GetObjectClass(obj);

    jfieldID fid = env->GetFieldID(
        wrapperclass,
        POINTER_NAME, 
        POINTER_TYPE);

    jlong pointer = env->GetLongField(obj, fid);

    printf("pointer %ld\n", pointer);
    if (pointer != 0) {
        MiniQbt::QasmAsyncInterpreter* interpreter = reinterpret_cast<MiniQbt::QasmAsyncInterpreter*>(pointer);
        printf("pointer %ld\n", (long int)&pointer);
        //interpreter->interpret(std::string("test"));
        printf(interpreter->hasErrors()? "True" : "False");
        env->SetLongField(obj, fid, 0);
        //(MiniQbt::QasmAsyncInterpreter*) pointer;
        delete interpreter;
        // set it to null
        
    } */

}