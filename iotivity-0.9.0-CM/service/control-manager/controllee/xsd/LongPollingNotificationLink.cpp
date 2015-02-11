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

#include "LongPollingNotificationLink.h"


#include "Elements.h"

using namespace std;

LongPollingNotificationLink::LongPollingNotificationLink()
{


}

LongPollingNotificationLink::~LongPollingNotificationLink()
{

}

bool
LongPollingNotificationLink::serializeContents(OC::Cm::Serialization::ISerializer &serializer)
{
    if (false == ::Link::serializeContents(serializer)) { return false;}



    return true ;
}

bool
LongPollingNotificationLink::deSerializeContents(OC::Cm::Serialization::IDeserializer &deserializer)
{
    if (false == ::Link::deSerializeContents(deserializer)) {return false;}



    return true ;
}

std::string
LongPollingNotificationLink::getElementName()
{
    return EN_LONGPOLLINGNOTIFICATIONLINK;
}

bool
LongPollingNotificationLink::clone(::LongPollingNotificationLink *pSrcObject)
{
    if (pSrcObject == NULL)
    {
        return false ;
    }

    if (false == ::Link::clone(pSrcObject)) {return false;}



    return true ;
}
