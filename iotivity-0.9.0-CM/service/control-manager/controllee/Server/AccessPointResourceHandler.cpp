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

#include "AccessPointResourceHandler.h"

AccessPointResourceHandler::AccessPointResourceHandler(
    OC::Cm::IContext *pContext) :
    OC::Cm::Server::ResourceHandler::SyncResourceHandler(pContext)
{
}

AccessPointResourceHandler::~AccessPointResourceHandler()
{
}

bool AccessPointResourceHandler::handleSyncResource(std::string methodId,
        int &statusCode, OC::Cm::Serialization::ISerializable *request,
        OC::Cm::Serialization::ISerializable *response)
{

    if (0 == methodId.compare("GET"))
    {
        if (false
            == OC::Cm::Server::ResourceHandler::SyncResourceHandler::validateRepresentation(
                response, EN_HUMIDITY))
        {
            statusCode = 404;
            return true;
        }
        this->onGET(statusCode, (::AccessPoint *) response);
    }
    else
    {
        statusCode = 405;
    }

    return true;
}

bool AccessPointResourceHandler::onGET(int &statusCode,
                                       ::AccessPoint *respData)
{
    statusCode = 200;
    return true;
}

