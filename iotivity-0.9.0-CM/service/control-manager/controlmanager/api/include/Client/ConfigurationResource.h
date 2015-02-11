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



#ifndef CONFIGURATIONRESOURCE_H_
#define CONFIGURATIONRESOURCE_H_

#include "CMClientResource.h"
#include "xsd/Elements.h"

#include "IConfigurationResourceResponseListener.h"


/**
*  @addtogroup Client
*  @{
*/

/**
 * @class   ConfigurationResource
 * @brief   ConfigurationResource class implements OC::Cm::Client::Resource::Resource and OC::Cm::Client::Resource::IResourceResponseListener @n
 *          This class provides base listener methods to receive response of Control Manager requests.<br><br>
 *
 *          Application developers must have the knowledge of input and output data format of Control Manager requests.@n
 *          Then only they can properly type cast the response data.<br><br>
 *
 *          Application needs to type cast the response data to corresponding data class generated by Control Manager-SDK.@n
 *          Control Manager-SDK also generates resource specific controllers and status listeners. It is advisable to use@n
 *          these resource specific controllers and interfaces to avoid type casting.<br><br>
 */
class ConfigurationResource : public OC::Cm::Client::Resource::Resource
{

    public:

        /**
         * Constructor of ConfigurationResource class.
         *
         * @param[in]   context         Context of Control Manager framework
         * @param[in]   protocol        Specify type of protocol to be used (http, https, scs, shs)
         * @param[in]   deviceAddress   Address of peer device. String format can be different for different protocol. (IP address:port [http,https,shs] or PeerID [scs])
         */
        ConfigurationResource(OC::Cm::IContext *context, std::string &protocol, std::string &deviceAddress);

        /**
         * Default virtual destructor of ConfigurationResource class.
         */
        virtual ~ConfigurationResource();

        /**
         * This method will initialize p_respListener variable.<br>
         * Please make sure that user must register their own listener class through this method before sending a request.
         * Otherwise, all the received response will be ignored.
         *
         * @param[in]   ConfigurationResourceResponseListener   Object that implements IConfigurationResourceResponseListener interface
         */

        void addResponseListener (IConfigurationResourceResponseListener &respListener) ;

        IConfigurationResourceResponseListener *getResponseListener ();

        bool getConfiguration( int &requestId );


        bool putConfiguration( int &requestId , ::Configuration &reqData);


        void buildPath(std::string deviceId);

    private:
        class ConfigurationResourceListenerInternal : public
            OC::Cm::Client::Resource::IResourceResponseListener
        {
            public:

                ConfigurationResource *resource;

                ConfigurationResourceListenerInternal(ConfigurationResource *res)
                {
                    resource = res;
                }

                ~ConfigurationResourceListenerInternal()
                {
                }

                void
                OnGetResponseReceived( int clientSessionId, int status, OC::Cm::Connector::HeadersList &headers,
                                       OC::Cm::Serialization::ISerializable *response )
                {
                    IConfigurationResourceResponseListener *p_respListener = resource->getResponseListener();

                    if (p_respListener != NULL)
                    {
                        if (response != NULL)
                        {
                            std::string elementName = response->getElementName() ;

                            if ( 0 == elementName.compare(EN_CONFIGURATION))
                            {
                                ::Configuration *respData = (::Configuration *)response ;
                                p_respListener->ongetConfiguration(clientSessionId, status,  respData) ;
                            }
                            else
                            {
                                p_respListener->ongetConfiguration(clientSessionId, 400,  NULL) ;
                            }
                        }
                        else
                        {
                            p_respListener->ongetConfiguration(clientSessionId, status,  NULL) ;
                        }

                    }
                }

                void
                OnPutResponseReceived(int clientSessionId,  int status, OC::Cm::Connector::HeadersList &headers,
                                      OC::Cm::Serialization::ISerializable *response)
                {
                    IConfigurationResourceResponseListener *p_respListener = resource->getResponseListener();

                    if (p_respListener != NULL)
                    {
                        p_respListener->onputConfiguration( clientSessionId, status ) ;
                    }
                }
                void
                OnPostResponseReceived(int clientSessionId, int status, OC::Cm::Connector::HeadersList &headers,
                                       OC::Cm::Serialization::ISerializable *response)
                {
                }

                void
                onDeleteResponseReceived(int clientSessionId, int status, OC::Cm::Connector::HeadersList &headers,
                                         OC::Cm::Serialization::ISerializable *response)
                {
                }

                void
                onSubscribeResponseReceived(int clientSessionId, int status, std::string &subscriptionUri )
                {
                    IConfigurationResourceResponseListener *p_respListener = resource->getResponseListener();
                    if (p_respListener != NULL)
                    {
                        p_respListener->onSubscribeResponseReceived(clientSessionId, status, subscriptionUri) ;
                    }
                }

                void
                onUnSubscribeResponseReceived(int clientSessionId, int status )
                {
                    IConfigurationResourceResponseListener *p_respListener = resource->getResponseListener();
                    if (p_respListener != NULL)
                    {
                        p_respListener->onUnSubscribeResponseReceived(clientSessionId, status) ;
                    }
                }

                void
                onErrorReceived( int requestId, int status, OC::Cm::CMError error,
                                 OC::Cm::Serialization::ISerializable *errorMessage)
                {
                    IConfigurationResourceResponseListener *p_respListener = resource->getResponseListener();
                    if ( p_respListener != NULL )
                    {
                        p_respListener->onError( requestId, status, error,
                                                 (OC::Cm::Serialization::Xsd::CMErrorMessage *)errorMessage ) ;
                    }
                }

                void
                onRequestComplete(int requestId, std::string requestPayload,  std::string responsePayload)
                {
                }
        };

        /**
         * Variable that contains IConfigurationResourceResponseListener object.
         */
        IConfigurationResourceResponseListener *p_respListener ;

        OC::Cm::Client::Resource::IResourceResponseListener *p_internalResponseListener ;

};

/** @} */

#endif /* CONFIGURATIONRESOURCE_H_ */
