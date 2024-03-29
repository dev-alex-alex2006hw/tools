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

#ifndef WEBSERVICE_SRC_NEW_RESOURCE_HANDLER_GENERATED_RESOURCE_RESOURCE_WIFI_H_
#define WEBSERVICE_SRC_NEW_RESOURCE_HANDLER_GENERATED_RESOURCE_RESOURCE_WIFI_H_

#include "base_resource/base_resource.h"
#include "data_types/simple_data_type.h"
#include "data_types/simple_array_data_type.h"

namespace webservice
{

    class ResourceWiFi : public BaseResource
    {
        public:
            ResourceWiFi(void);
            virtual ~ResourceWiFi(void);
            /**
              * Create this class.
              * @return BaseResource*
              */
            static BaseResource *Create(void);

        public:
            /**
              * Register function to create this class.
              * @param[in] string
              * @param[in] BaseResource*
              * @return static RegisterResource
              */
            static RegisterResource regResource;

        private:
            WifiOperationType *operationType_;
            UInt8 *channel_;
            String50 *ssid_;
            Int8 *rssi_;
            String20 *securityType_;
            String20 *encryptionType_;
            String100 *securityKey_;
            WifiEventType *wifiDirectStatus_;
            _boolean *wpsEnabled_;
            WifiEventType *wpsStatus_;
    };

}

#endif /* WEBSERVICE_SRC_NEW_RESOURCE_HANDLER_GENERATED_RESOURCE_RESOURCE_WIFI_H_ */