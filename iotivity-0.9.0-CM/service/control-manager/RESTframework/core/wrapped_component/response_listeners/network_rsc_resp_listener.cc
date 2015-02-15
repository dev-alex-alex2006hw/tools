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

#include "wrapped_component/response_listeners/network_rsc_resp_listener.h"
#include "wrapped_component/control_manager_wrapper.h"

namespace webservice
{

    typedef Singleton<NetworkResourceResponseListener, LeakySingletonTraits<NetworkResourceResponseListener> >
    NetworkResourceResponseListenerSingleton;
    NetworkResourceResponseListener
    *NetworkResourceResponseListener::network_rsc_resp_listener_instance_ = NULL;

    NetworkResourceResponseListener::NetworkResourceResponseListener()
    {
    }

    NetworkResourceResponseListener::~NetworkResourceResponseListener()
    {
    }

    NetworkResourceResponseListener *NetworkResourceResponseListener::GetInstance()
    {
        DLOG(INFO) << " : Enter";
        if (!network_rsc_resp_listener_instance_)
        {
            network_rsc_resp_listener_instance_ = NetworkResourceResponseListenerSingleton::get();
        }
        DLOG(INFO) << " : Exit";
        return network_rsc_resp_listener_instance_;
    }

    void NetworkResourceResponseListener::DestroyInstance()
    {
        DLOG(INFO) << " : Enter";
        static base::Lock destroy_lock;
        base::AutoLock auto_lock(destroy_lock);
        if (network_rsc_resp_listener_instance_)
        {
            delete network_rsc_resp_listener_instance_;
            network_rsc_resp_listener_instance_ = NULL;
        }
        DLOG(INFO) << " : Exit";
    }

    bool NetworkResourceResponseListener::ongetNetwork(int &requestId, int status, ::Network *respData)
    {
        LOG(ERROR) << "ongetNetwork:: " << requestId;
        // create a new instance of 'Network' and copy all the details from 'respData' and store it for in the map for future use.
        // Otherwise the CM will delete the respData as soon as the CB returns.
        Network *network = NULL;
        if (respData)
        {
            network = new Network();
            if (!network)
                return false;
            network->clone(respData);
        }
        ControlManagerWrapper *cm_wrapper = ControlManagerWrapper::GetInstance();
        if (cm_wrapper)
        {
            cm_wrapper->DataReceivedForRequest(requestId, network, status);
        }
        return true;
    }

    bool NetworkResourceResponseListener::onputNetwork(int &requestId, int status)
    {
        LOG(ERROR) << "onputNetwork:: " << requestId << "  status:  " << status;
        ControlManagerWrapper *cm_wrapper = ControlManagerWrapper::GetInstance();
        if (cm_wrapper)
        {
            cm_wrapper->DataReceivedForRequest(requestId, 0, status);
        }
        return true;
    }

    void NetworkResourceResponseListener::onSubscribeResponseReceived( int requestId, int status,
            std::string &subscriptionUri)
    {
    }

    void NetworkResourceResponseListener::onUnSubscribeResponseReceived(int requestId, int status)
    {
    }

    void NetworkResourceResponseListener::onError(int requestId, int statusCode, OC::Cm::CMError error,
            OC::Cm::Serialization::Xsd::CMErrorMessage *errorMessage)
    {
    }

}