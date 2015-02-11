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

#include "AccessPoints.h"

#include "Elements.h"

using namespace std;

AccessPoints::AccessPoints()
{
    setList(true);

}

AccessPoints::~AccessPoints()
{
    for (std::list< ::AccessPoint *>::const_iterator itr = mpAccessPoint.begin();
         itr != mpAccessPoint.end(); itr++)
    {
        delete (*itr);
    }
    mpAccessPoint.clear();

}

bool AccessPoints::serializeContents(
    OC::Cm::Serialization::ISerializer &serializer)
{
    if (false == ::List::serializeContents(serializer))
    {
        return false;
    }

    {
        bool bRet = true;

        if (mpAccessPoint.size() > 0)
        {
            if (serializer.validateMandatory() == false)
            {
                serializer.setIDExcemption(true);
            }
            serializer.startListProperty("AccessPoints");
            for (std::list< ::AccessPoint *>::const_iterator itr =
                     mpAccessPoint.begin(); itr != mpAccessPoint.end(); itr++)
            {
                (*itr)->setInstanceName("AccessPoints");
                if (false == (*itr)->serialize(serializer))
                {
                    bRet = false;
                    break;
                }
            }
            serializer.endListProperty("AccessPoints");
            if (false == bRet)
            {
                if (serializer.isInFilteringMode("AccessPoints") == false)
                {
                    serializer.setErrorMessage(
                        "Failed To Serialize parameter (Invalid content) : AccessPoints");
                    return false;
                }
            }
        }

    }

    return true;
}

bool AccessPoints::deSerializeContents(
    OC::Cm::Serialization::IDeserializer &deserializer)
{
    if (false == ::List::deSerializeContents(deserializer))
    {
        return false;
    }

    {
        bool isArray = deserializer.getIsArray("AccessPoints");
        int sizeOfArray = 0;

        if (deserializer.validateMandatory() == false)
        {
            deserializer.setIDExcemption(true);
        }

        if (isArray)
        {
            sizeOfArray = deserializer.getSize("AccessPoints");

            if (sizeOfArray > 0)
            {
                for (int i = 0; i < sizeOfArray; i++)
                {
                    ::AccessPoint *m = new ::AccessPoint();

                    deserializer.setCurrentArrayIndex("AccessPoints", i);

                    m->setInstanceName("AccessPoints");

                    if (false == m->deSerialize(deserializer))
                    {
                        return false;
                    }

                    mpAccessPoint.push_back(m);
                }
            }
            else if (sizeOfArray == 0)
            {
                deserializer.removeParameter("AccessPoints");
            }
        }
        else
        {
            if (true == deserializer.hasProperty("AccessPoints"))
            {
                ::AccessPoint *m = new ::AccessPoint();

                m->deSerialize(deserializer);

                mpAccessPoint.push_back(m);
            }
            else
            {
                if ((deserializer.isInFilteringMode("AccessPoints") == false))
                {
                    deserializer.setErrorMessage(
                        "Failed To deserialize : AccessPoints");
                    return false;
                }
            }
        }
    }

    return true;
}

std::string AccessPoints::getElementName()
{
    return EN_ACCESSPOINTS;
}

bool AccessPoints::clone(::AccessPoints *pSrcObject)
{
    if (pSrcObject == NULL)
    {
        return false;
    }

    {
        for (std::list< ::AccessPoint *>::const_iterator itr =
                 mpAccessPoint.begin(); itr != mpAccessPoint.end(); itr++)
        {
            delete (*itr);
        }
        mpAccessPoint.clear();
        for (std::list< ::AccessPoint *>::const_iterator itr =
                 pSrcObject->mpAccessPoint.begin();
             itr != pSrcObject->mpAccessPoint.end(); itr++)
        {
            ::AccessPoint *pTemp = new ::AccessPoint();
            if (false == pTemp->clone((*itr)))
            {
                delete pTemp;
                return false;
            };
            mpAccessPoint.push_back(pTemp);
        }
    }

    return true;
}
