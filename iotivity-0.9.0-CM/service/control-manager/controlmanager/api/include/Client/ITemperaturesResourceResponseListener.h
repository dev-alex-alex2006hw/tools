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



#ifndef ITEMPERATURESRESOURCERESPONSELISTENER_H_
#define ITEMPERATURESRESOURCERESPONSELISTENER_H_

#include "xsd/Elements.h"

/**
*  @addtogroup Client
*  @{
*/

/**
 * @interface   ITemperaturesResourceResponseListener
 * @brief       ITemperaturesResourceResponseListener interface provides listener methods to@n
 *              receive response of Control Manager requests which are sent using OC::Cm::Client::Resource::TemperaturesResource class.<br><br>
 *
 *              Application developers must have the knowledge of input and output data format of Control Manager requests.@n
 *              Then only they can properly type cast the response data.<br><br>
 *
 *              Application needs to type cast the response data to corresponding data class generated by Control Manager-SDK.@n
 *              Control Manager-SDK also generates resource specific controllers and status listeners. It is advisable to use
 *              these resource specific controllers and interfaces to avoid type casting.
 */

class ITemperaturesResourceResponseListener
{

    public:

        virtual ~ITemperaturesResourceResponseListener() {} ;

        /**
         * Listener method to receive a response of add subscription request.<br>
         * In order to make this function to be called, please see the OC::Cm::Client::Resource::TemperaturesResource.onSubscribeResponseReceived() method.
         *
         * @param[in]   requestId   Id of the request to which current response belongs
         * @param[in]   status      Http status code of the response
         * @param[in]   subscriptionUri Subscription URI which corresponds to a specific resource created by a server
         */
        virtual void onSubscribeResponseReceived( int requestId, int status,
                std::string &subscriptionUri ) = 0;

        /**
         * Listener method to receive a response of remove/delete subscription request.<br>
         * In order to make this function to be called, please see the OC::Cm::Client::Resource::TemperaturesResource.onUnSubscribeResponseReceived() method.
         *
         * @param[in]   requestId   Id of the request to which current response belongs
         * @param[in]   status      Http status code of the response
         */
        virtual void onUnSubscribeResponseReceived(int requestId, int status ) = 0;

        /**
         * Error callback method for the HTTP requests sent using OC::Cm::Client::Resource::TemperaturesResource class.
         *
         * @param[in]   requestId   Id of the request to which current response belongs
         * @param[in]   statusCode  (-1) Unable to provide a http status code / Http status code
         * @param[in]   error       Error code defined by a Control Manager framework. Please see the OC::Cm::CMError
         * @param[in]   errorMessage    Serializable object which contains detailed error information
         */
        virtual void onError( int requestId, int statusCode, OC::Cm::CMError error,
                              OC::Cm::Serialization::Xsd::CMErrorMessage *errorMessage  ) = 0;


        virtual bool ongetTemperatures( int &requestId , int status, ::Temperatures *respData) = 0;


        virtual bool onputTemperatures( int &requestId, int status ) = 0;




};

/** @} */
#endif /* ITEMPERATURESRESOURCERESPONSELISTENER_H_ */