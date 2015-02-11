//******************************************************************
//
// Copyright 2014 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class OC_Cm_Device */

#ifndef _Included_OC_Cm_Device
#define _Included_OC_Cm_Device
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     OC_Cm_Device
 * Method:    constructNative
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_OC_Cm_Device_constructNative
(JNIEnv *, jobject, jint, jint);

/*
 * Class:     OC_Cm_Device
 * Method:    deleteNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_deleteNative
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setProtocol
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setProtocol
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    setContext
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setContext
(JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    getContext
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_OC_Cm_Device_getContext
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    getAddress
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getAddress
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    getProtocol
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getProtocol
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setAddress
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setAddress
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    getDeviceDescriptionUri
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getDeviceDescriptionUri
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setDeviceDescriptionUri
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setDeviceDescriptionUri
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    getDeviceType
 * Signature: (J)LOC/Cm/DeviceType;
 */
JNIEXPORT jobject JNICALL Java_OC_Cm_Device_getDeviceType
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setDeviceType
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setDeviceType
(JNIEnv *, jobject, jlong, jint);

/*
 * Class:     OC_Cm_Device
 * Method:    getDomain
 * Signature: (J)LOC/Cm/DeviceDomain;
 */
JNIEXPORT jobject JNICALL Java_OC_Cm_Device_getDomain
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setDomain
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setDomain
(JNIEnv *, jobject, jlong, jint);

/*
 * Class:     OC_Cm_Device
 * Method:    getUUID
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getUUID
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setUUID
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setUUID
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    isDeviceDescriptionLoaded
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_OC_Cm_Device_isDeviceDescriptionLoaded
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setDeviceDescriptionLoaded
 * Signature: (JZ)Z
 */
JNIEXPORT jboolean JNICALL Java_OC_Cm_Device_setDeviceDescriptionLoaded
(JNIEnv *, jobject, jlong, jboolean);

/*
 * Class:     OC_Cm_Device
 * Method:    getDescription
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getDescription
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setDescription
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setDescription
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    getManufacturer
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getManufacturer
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setManufacturer
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setManufacturer
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    getDeviceSubType
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getDeviceSubType
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setDeviceSubType
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setDeviceSubType
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    getModelID
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getModelID
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setModelID
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setModelID
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    getSerialNumber
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getSerialNumber
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setSerialNumber
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setSerialNumber
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    getSalesLocation
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_OC_Cm_Device_getSalesLocation
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setSalesLocation
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setSalesLocation
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Device
 * Method:    getSupportedResources
 * Signature: (J)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_OC_Cm_Device_getSupportedResources
(JNIEnv *, jobject, jlong);

/*
 * Class:     OC_Cm_Device
 * Method:    setSupportedResource
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Device_setSupportedResource
(JNIEnv *, jobject, jlong, jstring);



#ifdef __cplusplus
}
#endif
#endif
