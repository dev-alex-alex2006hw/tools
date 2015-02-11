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

#include "wrapped_component/response_listeners/information_rsc_resp_listener.h"
#include "wrapped_component/control_manager_wrapper.h"

namespace webservice
{

    typedef Singleton<InformationResourceResponseListener, LeakySingletonTraits<InformationResourceResponseListener> >
    InformationResourceResponseListenerSingleton;
    InformationResourceResponseListener
    *InformationResourceResponseListener::information_rsc_resp_listener_instance_ = NULL;

    InformationResourceResponseListener::InformationResourceResponseListener()
    {
    }

    InformationResourceResponseListener::~InformationResourceResponseListener()
    {
    }

    InformationResourceResponseListener *InformationResourceResponseListener::GetInstance()
    {
        DLOG(INFO) << " : Enter";
        if (!information_rsc_resp_listener_instance_)
        {
            information_rsc_resp_listener_instance_ = InformationResourceResponseListenerSingleton::get();
        }
        DLOG(INFO) << " : Exit";
        return information_rsc_resp_listener_instance_;
    }

    void InformationResourceResponseListener::DestroyInstance()
    {
        DLOG(INFO) << " : Enter";
        static base::Lock destroy_lock;
        base::AutoLock auto_lock(destroy_lock);
        if (information_rsc_resp_listener_instance_)
        {
            delete information_rsc_resp_listener_instance_;
            information_rsc_resp_listener_instance_ = NULL;
        }
        DLOG(INFO) << " : Exit";
    }

    bool InformationResourceResponseListener::ongetInformation(int &requestId, int status,
            Information *respData)
    {
        LOG(ERROR) << "ongetInformation:: " << requestId;
        // create a new instance of 'Information' and copy all the details from 'respData' and store it for in the map for future use.
        // Otherwise the CM will delete the respData as soon as the CB returns.
        Information *information = NULL;
        if (respData)
        {
            information = new Information();
            if (!information)
                return false;
            information->clone(respData);
        }
        ControlManagerWrapper *cm_wrapper = ControlManagerWrapper::GetInstance();
        if (cm_wrapper)
        {
            cm_wrapper->DataReceivedForRequest(requestId, information, status);
        }
        return true;
    }

    void InformationResourceResponseListener::onSubscribeResponseReceived( int requestId, int status,
            std::string &subscriptionUri)
    {
    }

    void InformationResourceResponseListener::onUnSubscribeResponseReceived(int requestId, int status)
    {
    }

    void InformationResourceResponseListener::onError(int requestId, int statusCode,
            OC::Cm::CMError error, OC::Cm::Serialization::Xsd::CMErrorMessage *errorMessage)
    {
    }

}
