/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_matthijs_kropholler_jniarticle_MyNativeObject */

#ifndef _Included_com_matthijs_kropholler_jniarticle_MyNativeObject
#define _Included_com_matthijs_kropholler_jniarticle_MyNativeObject
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_matthijs_kropholler_jniarticle_MyNativeObject
 * Method:    printToStdOut
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_matthijs_kropholler_jniarticle_MyNativeObject_printToStdOut
  (JNIEnv *, jobject);

/*
 * Class:     com_matthijs_kropholler_jniarticle_MyNativeObject
 * Method:    addNumbers
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_matthijs_kropholler_jniarticle_MyNativeObject_addNumbers
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_matthijs_kropholler_jniarticle_MyNativeObject
 * Method:    manipulateData
 * Signature: (Lcom/matthijs/kropholler/jniarticle/MyDataObject;)V
 */
JNIEXPORT void JNICALL Java_com_matthijs_kropholler_jniarticle_MyNativeObject_manipulateData
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
