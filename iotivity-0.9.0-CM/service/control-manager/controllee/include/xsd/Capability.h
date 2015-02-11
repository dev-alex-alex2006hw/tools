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

#ifndef CAPABILITY_H_
#define CAPABILITY_H_

#include "ISerializer.h"
#include "IDeserializer.h"
#include "list"
#include "string"
#include "Resource.h"
#include "SubscriptionsLink.h"
#include "GroupsLink.h"
#include "RecordsLink.h"
#include "PatternsLink.h"
#include "EnergyLink.h"
#include "DevicesLink.h"
#include "ActionsLink.h"
#include "FoodManagerLink.h"
#include "NotificationsLink.h"
#include "LongPollingNotificationLink.h"


using namespace std;

/**
 * @class   Capability
 * @brief   This class defines methods to serialize and/or deserialize contents of XSD complex/list type TEMPLATE_SERIALIZABLE_NAME
 */

class Capability: public ::Resource
{
    public:

        /**
         * Default constructor of Capability class.
         */
        Capability();

        /**
         * Default virtual destructor of Capability class.
         */
        virtual ~Capability();

        /**
         * Serializes the contents of Capability object.
         *
         * @param[out] serializer   Serializer object which provide methods to serialize
         *
         * @return  @c True if serialization is successful @n
         *          @c False if serialization is failed
         */
        virtual bool serializeContents(OC::Cm::Serialization::ISerializer &serializer);

        /**
         * Deserializes data and prepares the Capability object contents.
         *
         * @param[out] deserializer Deserializer object which provide methods to deserialize
         *
         * @return  @c True if deserialization is successful @n
         *          @c False if deserialization is failed
         */
        virtual bool deSerializeContents(OC::Cm::Serialization::IDeserializer &deserializer);

        /**
         * This method gets name of the serializable.
         *
         * @return  Returns name of the serializable.
         */
        virtual std::string getElementName();

        /**
         * Creates a new Capability object of the same class as this object. It then initializes each of the new object's fields by assigning it the same value as the corresponding field in this object.
         *
         * @param[out] pSrcObject   Source Capability object to be cloned.
         *
         * @return  @c True if cloning is successful @n
         *          @c False if cloning is failed
         */
        bool clone(::Capability *pSrcObject);
        ::SubscriptionsLink    *mpSubscriptionsLink;
        ::GroupsLink   *mpGroupsLink;
        ::RecordsLink  *mpRecordsLink;
        ::PatternsLink     *mpPatternsLink;
        ::EnergyLink   *mpEnergyLink;
        ::DevicesLink  *mpDevicesLink;
        ::ActionsLink  *mpActionsLink;
        ::FoodManagerLink  *mpFoodManagerLink;
        ::NotificationsLink    *mpNotificationsLink;
        ::LongPollingNotificationLink  *mpLongPollingNotificationLink;
};

#endif /* CAPABILITY_H_ */
