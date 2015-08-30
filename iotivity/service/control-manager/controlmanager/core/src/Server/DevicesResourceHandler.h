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



#ifndef DEVICESRESOURCEHANDLER_H_
#define DEVICESRESOURCEHANDLER_H_

#include "CMServerResourceHandler.h"
#include "xsd/Elements.h"

/**
*  @addtogroup Server
*  @{
*/

/**
 * @class   DevicesResourceHandler
 * @brief   Defines methods required to handle requests received
 *
 * This class defines methods to handle requests received corresponding to a Devices resource.
 */
class DevicesResourceHandler : public OC::Cm::Server::ResourceHandler::SyncResourceHandler
{

    public:

        /**
         * Default constructor of Devices class.
         *
         * @param[in] pContext Context to which this handler belongs
         */
        DevicesResourceHandler(OC::Cm::IContext *pContext);

        /**
         * Default virtual destructor of Devices class.
         */
        virtual ~DevicesResourceHandler();

        /**
         * This method will be invoked to distinguish type of http request. If required, validation also will be performed.
         *
         * @param[in] session   Server session to which the request belongs
         * @param[in] methodId  Http method type which needs to be executed (GET, PUT, POST, DELETE)
         * @param[out] statusCode   Http status code to be returned to the client
         * @param[in] request   Serializable request object
         * @param[out] response Serializable response object
         *
         * @return  @c True If the request is properly handled @n
         *          @c False In case of any error occurred
         */
        bool handleSyncResource(OC::Cm::Connector::Server::ServerSession &session,
                                std::string methodId,
                                int &statusCode,
                                OC::Cm::Serialization::ISerializable *request,
                                OC::Cm::Serialization::ISerializable *response);

        /**
         * This method will be invoked to handle a GET request.
         *
         * @param[in] session   Server session to which the request belongs
         * @param[out] statusCode   Http status code to be returned to the client
         * @param[out] respData Devices object to be returned to the server through the serializer. This object should not be re-initialized by a user.
         *
         * @return  @c True If the request is properly handled @n
         *          @c False In case of any error occurred
        */
        bool onGET( OC::Cm::Connector::Server::ServerSession &session, int &statusCode,
                    ::Devices *respData);

        /**
         * This method will be invoked to handle a POST request.
         *
         * @param[in] session   Server session to which the request belongs
         * @param[out] statusCode   Http status code to be returned to the client
         * @param[in] reqData   Received Devices object through the deserializer. This object should not be re-initialized by a user.
         * @param[out] location Contains http location header field information to provide the location of a newly created resource or ask a client to load a different URL
         *
         * @return  @c True If the request is properly handled @n
         *          @c False In case of any error occurred
        */
        bool onPOST( OC::Cm::Connector::Server::ServerSession &session, int &statusCode, ::Device *reqData,
                     std::string &location);

};
/** @} */
#endif /* DEVICESRESOURCEHANDLER_H_ */