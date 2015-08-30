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

#include "CDSerializableDataFactory.h"

using namespace std;

CDSerializableDataFactory::CDSerializableDataFactory()
{
    pApplicationFactory = NULL;
    pSubscriptionFactory = NULL;
}

CDSerializableDataFactory::~CDSerializableDataFactory()
{
    if (NULL != pSubscriptionFactory)
    {
        delete pSubscriptionFactory;
    }
}

bool CDSerializableDataFactory::createMethodSerializables(int resourceType,
        std::string &methodId,
        OC::Cm::Serialization::ISerializable **pp_request,
        OC::Cm::Serialization::ISerializable **pp_response)
{
    bool bRet = false;

    if (NULL != pSubscriptionFactory)
    {
        bRet = pSubscriptionFactory->createMethodSerializables(resourceType,
                methodId, pp_request, pp_response);
    }

    if (false == bRet)
    {
        if (NULL != pApplicationFactory)
        {
            bRet = pApplicationFactory->createMethodSerializables(resourceType,
                    methodId, pp_request, pp_response);
        }
    }

    return bRet;
}

bool CDSerializableDataFactory::createSerializable(std::string &elementType,
        OC::Cm::Serialization::ISerializable **pp_output)
{
    bool bRet = false;

    if (NULL != pSubscriptionFactory)
    {
        bRet = pSubscriptionFactory->createSerializable(elementType, pp_output);
    }

    if (false == bRet)
    {
        if (NULL != pApplicationFactory)
        {
            bRet = pApplicationFactory->createSerializable(elementType,
                    pp_output);
        }
    }

    return bRet;
}

bool CDSerializableDataFactory::deleteMethodSerializables(int resourceType,
        OC::Cm::Serialization::ISerializable *pp_request,
        OC::Cm::Serialization::ISerializable *pp_response)
{
    bool bRet = false;

    if (NULL != pSubscriptionFactory)
    {
        bRet = pSubscriptionFactory->deleteMethodSerializables(resourceType, pp_request,
                pp_response);
    }
    if (false == bRet)
    {
        if (NULL != pApplicationFactory)
        {
            bRet = pApplicationFactory->deleteMethodSerializables(resourceType, pp_request,
                    pp_response);
        }
    }
    return bRet;
}