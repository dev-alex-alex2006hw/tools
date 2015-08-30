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



#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include "CMSerialization.h"
#include "list"
#include "string"
#include "Resource.h"
#include "Float32.h"
#include "HumidityUnitType.h"


/**
*  @addtogroup xsd
*  @{
*/

/**
 * @class   Humidity
 *
 * This is a set of attributes associated with the humidity.
 * Also, this class defines methods that serialize and/or deserialize contents of XSD complex/list type Humidity.
 * @since   1.0.0
 */

class Humidity: public ::Resource
{

    protected:

        /**
         * Serializes the contents of Humidity object using the specified serializer.
         * This function validates the values of each member variable and returns false if any of the member contains invalid value.
         * This function returns false, if one of the mandatory parameter is not set or one of the attribute is invalid.
         *
         * @param[out]  serializer  Serializer object that provides methods to serialize.
         *
         * @return  @c  True    if serialization is successful@n
         *          @c  False   if serialization failed
         * @since   1.0.0
         */
        virtual bool serializeContents(OC::Cm::Serialization::ISerializer &serializer);

        /**
         * Deserializes data and prepares the Humidity object contents.
         * After parsing the values, this function validates the values.
         * This function returns false, if one of the mandatory parameter is not present or one of the attribute is invalid.
         *
         * @param[out]  deserializer    Deserializer object that provides methods to deserialize.
         *
         * @return  @c  True    if deserialization is successful@n
         *          @c  False   if deserialization failed
         * @since   1.0.0
         */
        virtual bool deSerializeContents(OC::Cm::Serialization::IDeserializer &deserializer);

    public:

        /**
         * Default constructor of Humidity class.
         * @since   1.0.0
         */
        Humidity();

        /**
         * Default virtual destructor of Humidity class.
         * @since   1.0.0
         */
        virtual ~Humidity();

        /**
         * This method gets the name of the serializable.
         *
         * @return Returns name of the serializable.
         * @since   1.0.0
         */
        virtual std::string getElementName();

        /**
         * Creates a new Humidity object of the same class as this object. It then initializes each of the new object's fields by assigning it with the same value as the corresponding field in this object.
         *
         * @param[out]  pSrcObject  Source Humidity object to be cloned.
         *
         * @return  @c  True    if cloning is successful@n
         *          @c  False   if cloning failed
         * @since   1.0.0
         */
        bool clone(::Humidity *pSrcObject);

        /**
         * [Mandatory] Indicates current atmospheric humidity, in percent. (e.g., �74.7�)
         */
        ::Float32 *mpCurrent;

        /**
         * [Optional] Indicates desired atmospheric humidity, in percent. (e.g., �40.6�)
         */
        ::Float32 *mpDesired;

        /**
         * [Mandatory] This indicate the unit type defined for this humidity resource.
         */
        ::HumidityUnitType *mpUnit;
};
/** @} */
#endif /* HUMIDITY_H_ */