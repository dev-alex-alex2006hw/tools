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

#include "ControlResponse.h"

namespace OC
{
    namespace Cm
    {
        namespace Connector
        {

            ControlResponse::ControlResponse()
            {
                m_payloadSize = 0 ;
                m_headers_str_length = 0;
                m_response_code = 0;
            }

            bool
            ControlResponse::getProtocolVersion(std::string &version)
            {
                return m_headers.getHeader("HTTP_HEADER_VERSION", version);
            }

            bool
            ControlResponse::setProtocolVersion(const char *version)
            {
                if ((NULL == version) || (0 >= strlen(version))) { return false; }
                std::string versionStr = version;
                return m_headers.setHeader("HTTP_HEADER_VERSION", versionStr);
            }

        }
    }
}