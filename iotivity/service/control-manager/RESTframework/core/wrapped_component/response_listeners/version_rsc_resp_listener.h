/******************************************************************
 *
 * Copyright 2014 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

#ifndef WEBSERVICE_COMMON_WRAPPER_FUNCTIONS_VERSION_RSC_RESP_LISTENER_H_
#define WEBSERVICE_COMMON_WRAPPER_FUNCTIONS_VERSION_RSC_RESP_LISTENER_H_

#include "base/memory/singleton.h"
#include "Client/VersionResource.h"
namespace webservice
{

    class VersionResourceResponseListener : public IVersionResourceResponseListener
    {
        public:
            static VersionResourceResponseListener *GetInstance();
            void DestroyInstance();
            bool ongetVersion(int &requestId, int status, ::Version  *respData);
            bool onputVersion(int &requestId, int status);
            void onSubscribeResponseReceived( int requestId, int status, std::string &subscriptionUri);
            void onUnSubscribeResponseReceived(int requestId, int status);
            void onError(int requestId, int statusCode, OC::Cm::CMError error,
                         OC::Cm::Serialization::Xsd::CMErrorMessage *errorMessage);

        private:
            VersionResourceResponseListener();
            ~VersionResourceResponseListener();
            static VersionResourceResponseListener *version_rsc_resp_listener_instance_;
            // friend member, it creates VersionResourceResponseListener object
            friend struct DefaultSingletonTraits<webservice::VersionResourceResponseListener>;
    };
}

#endif /* WEBSERVICE_COMMON_WRAPPER_FUNCTIONS_VERSION_RSC_RESP_LISTENER_H_ */

