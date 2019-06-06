#include "MiniQbtQasmAsyncInterpreter.hpp"
#include <miniqbt/MiniQbt.hpp>
#include<stdio.h>

using namespace MiniQbt;

constexpr char POINTER_NAME[] = "nativeQasmPointer";
constexpr char POINTER_TYPE[] = "J"; // The type of a long is J in jni

inline QasmAsyncInterpreter* getInterpreterFromMemory(JNIEnv *env, jobject obj) {
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
    // Store the pointer in java. So we can use it.
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
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    return interpreter->hasErrors();
}

JNIEXPORT jstring JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_getError (JNIEnv *env, jobject obj) {
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    std::string res = interpreter->getError();
    return env->NewStringUTF(res.c_str());


}

JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_resetSuperPosition (JNIEnv *env, jobject obj,jstring qregister) {
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    const char *inCStr = env->GetStringUTFChars(qregister, nullptr);
    interpreter->resetSuperPosition(std::string(inCStr));
    env->ReleaseStringUTFChars(qregister, inCStr);
}


JNIEXPORT jobjectArray Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_getRegisters(JNIEnv *env, jobject obj) {
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    std::vector<std::string> classicRegisters = interpreter->getRegisters();
    const int size = classicRegisters.size();
    jobjectArray result= (jobjectArray)env->NewObjectArray(
        size, 
        env->FindClass("java/lang/String") , 
        env->NewStringUTF("")
    );

    jstring fill[size];
    for(int i =0; i < size; i++) {
        env->SetObjectArrayElement(result, i, env->NewStringUTF(classicRegisters[i].c_str()));
    }   
    return result;
}


JNIEXPORT jobjectArray Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_getQuantumRegisters(JNIEnv *env, jobject obj) {
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    std::vector<std::string> quantumRegisters = interpreter->getQuantumRegisters();
    const int size = quantumRegisters.size();
    jobjectArray result= (jobjectArray)env->NewObjectArray(
        size, 
        env->FindClass("java/lang/String") , 
        env->NewStringUTF("")
    );

    jstring fill[size];
    for(int i =0; i < size; i++) {
        env->SetObjectArrayElement(result, i, env->NewStringUTF(quantumRegisters[i].c_str()));
    }   
    return result;
}



 JNIEXPORT jbooleanArray Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_readClassicRegister(JNIEnv *env, jobject obj, jstring name) {
    const char *inCStr = env->GetStringUTFChars(name, nullptr);
    QasmAsyncInterpreter* interpreter = getInterpreterFromMemory(env, obj);
    std::vector<bool> data = interpreter->readClassicRegister(std::string(inCStr));
    const int size = data.size();
    jboolean fill[size];
    for (int i = 0; i < size; i++) {
        fill[i] = data[i];
    }
    jbooleanArray result = env->NewBooleanArray(size);
    env->SetBooleanArrayRegion(result, 0, size, fill);
    env->ReleaseStringUTFChars(name, inCStr);
    return result;
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