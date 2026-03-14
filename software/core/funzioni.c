#include "Core.h"

JNIEXPORT jint JNICALL Java_Core_somma(JNIEnv *env, jobject obj, jint a, jint b) {
    return a + b;
}

JNIEXPORT jint JNICALL Java_Core_moltiplica(JNIEnv *env, jobject obj, jint a, jint b) {
    return a * b;
}

JNIEXPORT jfloat JNICALL Java_Core_dividi(JNIEnv *env, jobject obj, jint a, jint b) {
    if (b == 0) {
        return 0;
    } else {
        return a / b;
    }
}