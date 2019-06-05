#ifndef MINIQBT_GLOBALS_WRAPPER_HPP
#define MINIQBT_GLOBALS_WRAPPER_HPP
#include <jni.h>

extern "C" {
  
    JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_init (JNIEnv *env, jobject);

    JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_interpret (JNIEnv *env, jobject,jstring src);
    
    JNIEXPORT jboolean JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_hasErrors (JNIEnv *env, jobject);
    
    JNIEXPORT jstring JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_getError (JNIEnv *env, jobject);

    JNIEXPORT void JNICALL Java_nl_hvanderheijden_miniqbt_QasmAsyncInterpreter_dispose (JNIEnv *env, jobject);
}



#endif