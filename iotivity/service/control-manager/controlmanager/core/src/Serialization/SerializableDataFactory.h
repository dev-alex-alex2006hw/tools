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



#if !defined(_SERIALIZABLEDATAFACTORY_H)
#define _SERIALIZABLEDATAFACTORY_H

#include "CMConfig.h"
#include "string"

namespace OC
{
    namespace Cm
    {
        namespace Serialization
        {
            class ISerializable;
            /**
            *  @addtogroup Serialization
            *  @{
            */
            /**
             * @interface   SerializableDataFactory
             * @brief       Defines methods required to instantiate a serializable
             *
             * @since       1.0
             *
             * This interface defines methods required to instantiate a serializable.
             * Control Manager framework uses  SerializableDataFactory to instantiate serializable objects as these
             * will be generated by Control Manager-SDK.
             *
             * Control Manager-SDK also generates a SerializableDataFactory class which can instantiate the generated serializable classes.
             * Developers must configure an instance of this generated SerializableDataFactory with framework
             * using OC::Cm::Configuration::setSerializableDataFactory()
             *
             */
            class CMAPI SerializableDataFactory
            {

                public:

                    /**
                     * Default virtual destructor of this class
                     */
                    virtual ~SerializableDataFactory() {}

                    /**
                     * instantiates serializable object which is related to a element
                     *
                     * @param[in] elementType   Represents type of the element
                     * @param[out] pp_output instantiated serializable object
                     *
                     * @return  returns @c true in case of success @n
                     *                  @c false in case of any error
                     *
                     */
                    virtual bool createSerializable( std::string &elementType,
                                                     OC::Cm::Serialization::ISerializable **pp_output ) = 0;

                    /**
                     * instantiates request object which can hold request data of request identified by specified resource and method
                     *
                     * @param[in] resourceType  Represents type of the resource
                     * @param[in] methodId      Represents method identifier
                     * @param[out] pp_request   Represents ISerializable instance of the request
                     * @param[out] pp_response  Represents ISerializable instance of the response
                     *
                     * @return  returns @c true in case of success @n
                     *                  @c false in case of any error
                     *
                     */
                    virtual bool createMethodSerializables( int resourceType, std::string &methodId,
                                                            OC::Cm::Serialization::ISerializable **pp_request,
                                                            OC::Cm::Serialization::ISerializable **pp_response ) = 0;

            };
            /** @} */
        }
    }
}

#endif  //_SERIALIZABLEDATAFACTORY_H