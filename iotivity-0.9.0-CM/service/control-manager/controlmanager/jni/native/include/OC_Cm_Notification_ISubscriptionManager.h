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
/* Header for class OC_Cm_Notification_ISubscriptionManager */

#ifndef _Included_OC_Cm_Notification_ISubscriptionManager
#define _Included_OC_Cm_Notification_ISubscriptionManager
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    addSubscriptionProvider
 * Signature: (JLOC/Cm/Notification/ISubscriptionProvider;)J
 */
JNIEXPORT jlong JNICALL Java_OC_Cm_Notification_ISubscriptionManager_addSubscriptionProvider
(JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    removeSubscriptionProvider
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Notification_ISubscriptionManager_removeSubscriptionProvider
(JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    addNotificationListener
 * Signature: (JLOC/Cm/Notification/INotificationListener;)J
 */
JNIEXPORT jlong JNICALL Java_OC_Cm_Notification_ISubscriptionManager_addNotificationListener
(JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    removeNotificationListener
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_OC_Cm_Notification_ISubscriptionManager_removeNotificationListener
(JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    addSubscription
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;LOC/Cm/Client/Resource/IResourceResponseListener;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_OC_Cm_Notification_ISubscriptionManager_addSubscription
(JNIEnv *, jobject, jlong, jstring, jstring, jstring, jstring, jobjectArray, jobject, jstring);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    removeSubscription
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;LOC/Cm/Client/Resource/IResourceResponseListener;)Ljava/util/HashMap;
 */
JNIEXPORT jobject JNICALL
Java_OC_Cm_Notification_ISubscriptionManager_removeSubscription__JLjava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2_3Ljava_lang_String_2LOC_Cm_Client_Resource_IResourceResponseListener_2
(JNIEnv *, jobject, jlong, jstring, jstring, jstring, jobjectArray, jobject);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    notify
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_OC_Cm_Notification_ISubscriptionManager_notify
(JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    notifymultiple
 * Signature: (J[J)Z
 */
JNIEXPORT jboolean JNICALL Java_OC_Cm_Notification_ISubscriptionManager_notifymultiple
(JNIEnv *, jobject, jlong, jlongArray);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    notifyAll
 * Signature: (JLjava/lang/String;Ljava/lang/String;LOC/Cm/Serialization/ISerializable;)Z
 */
JNIEXPORT jboolean JNICALL Java_OC_Cm_Notification_ISubscriptionManager_notifyAll
(JNIEnv *, jobject, jlong, jstring, jstring, jobject);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    getMySubscription
 * Signature: (JLjava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_OC_Cm_Notification_ISubscriptionManager_getMySubscription
(JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     OC_Cm_Notification_ISubscriptionManager
 * Method:    removeSubscription
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;LOC/Cm/Client/Resource/IResourceResponseListener;)I
 */
JNIEXPORT jint JNICALL
Java_OC_Cm_Notification_ISubscriptionManager_removeSubscription__JLjava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2LOC_Cm_Client_Resource_IResourceResponseListener_2
(JNIEnv *, jobject, jlong, jstring, jstring, jstring, jstring, jobject);

#ifdef __cplusplus
}
#endif
#endif
