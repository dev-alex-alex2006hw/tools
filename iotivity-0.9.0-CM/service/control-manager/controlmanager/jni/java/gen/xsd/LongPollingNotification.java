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

package gen.xsd;

import OC.Cm.Serialization.IDeserializer;
import OC.Cm.Serialization.ISerializer;

/**
 * This Subscription and Notification resource set support a generic,
 * lightweight subscription/notification mechanism for use throughout the
 * specification. This mechanism may be useful when a client wishes to quickly
 * learn of changes to a resource on a server.<br>
 * Also, this class defines methods that serialize and/or deserialize contents
 * of XSD complex/list type LongPollingNotification.
 * 
 * @since 1.0.0
 */
public class LongPollingNotification extends gen.xsd.Resource {
    /**
     * [Mandatory] The subscription from which this notification was triggered.
     * (e.g., â€œ/devices/167261211391/subscriptions/3â€�)
     */
    public gen.xsd.String50               SubscriptionID;

    /**
     * Variable that contains Events objects in the List.
     */
    public java.util.List<gen.xsd.Events> events = new java.util.ArrayList<gen.xsd.Events>();

    /**
     * Default constructor of LongPollingNotification class.
     * 
     * @since 1.0.0
     */
    public LongPollingNotification() {
    }

    /**
     * Destroy method for LongPollingNotification class.
     * 
     * @since 1.0.0
     */
    @Override
    public void destroy() {
        super.destroy();
        for (gen.xsd.Events itr : events) {
            if (itr != null) {
                itr.destroy();
            }
        }
    }

    /**
     * Returns name of the serializable.
     * 
     * @since 1.0.0
     */
    @Override
    public String getElementName() {
        return Elements.EN_LONGPOLLINGNOTIFICATION;
    }

    /**
     * Serializes the contents of LongPollingNotification object.
     * 
     * @param serializer
     *            Serializer object that provides methods to serialize.
     * 
     * @return True if serialization is successful / False if serialization
     *         failed
     * @since 1.0.0
     */
    @Override
    public boolean serializeContents(ISerializer serializer) {
        boolean retValue = true;
        if (false == super.serializeContents(serializer))
            retValue = false;

        try {
            if (serializer.validateMandatory() == true) {
                boolean bRet = true;
                if (null != SubscriptionID) {
                    if (SubscriptionID.value.length() > 0) {
                        if (true == SubscriptionID.validateContent()) {
                            bRet = serializer.setStringPropertyValue(
                                    "subscriptionID", SubscriptionID.value);
                        } else
                            bRet = false;
                    } else
                        bRet = false;
                    if (false == bRet)
                        serializer
                                .setErrorMessage("Failed To Serialize parameter (Invalid content) : "
                                        + " subscriptionID");
                } else {
                    if (serializer.isInFilteringMode("subscriptionID") == false) {
                        serializer
                                .setErrorMessage("Failed To Serialize parameter (Invalid content) : "
                                        + " subscriptionID");
                        bRet = false;
                    } else
                        bRet = true;
                }
                if (retValue == true)
                    retValue = bRet;
            }

            {
                boolean bRet = true;
                if (null != events) {
                    if (serializer.validateMandatory() == false)
                        serializer.setIDExcemption(true);
                    if (events.size() < 1) {
                        if (serializer.isInFilteringMode("Events") == false) {
                            serializer
                                    .setErrorMessage(" parameter item count is less than minOccures value specified in xsd : Events");
                            bRet = false;
                        }
                    }
                    if (bRet == true) {
                        serializer.startListProperty("Events");
                        for (gen.xsd.Events itr : events) {
                            if (false == (itr).serialize(serializer)) {
                                bRet = false;
                                break;
                            }
                        }
                        serializer.endListProperty("Events");
                    }
                    if (false == bRet) {
                        serializer
                                .setErrorMessage("Failed To Serialize parameter (Invalid content) : "
                                        + " Events");
                    }
                } else {
                    if (serializer.isInFilteringMode("Events") == false) {
                        serializer
                                .setErrorMessage("Failed To Serialize parameter (Invalid content) : "
                                        + " Events");
                        bRet = false;
                    } else
                        bRet = true;
                }
                if (retValue == true)
                    retValue = bRet;
            }

        } catch (Exception e) {
            return false;
        }
        return retValue;

    }

    /**
     * Deserializes data and prepares the LongPollingNotification object
     * contents.
     * 
     * @param deserializer
     *            Deserializer object that provides methods to deserialize.
     * 
     * @return True if deserialization is successful / False if deserialization
     *         failed
     * @since 1.0.0
     */
    @Override
    public boolean deSerializeContents(IDeserializer deserializer) {
        boolean retValue = true;
        if (false == super.deSerializeContents(deserializer))
            retValue = false;

        try {
            {
                boolean bRet = true;
                if (true == deserializer.hasProperty("subscriptionID")) {
                    if (deserializer.validateMandatory() == false)
                        bRet = false;
                    if (bRet == true) {
                        SubscriptionID = new gen.xsd.String50();
                        SubscriptionID.value = deserializer
                                .getStringPropertyValue("subscriptionID");
                        if (false == SubscriptionID.validateContent()) {
                            deserializer
                                    .setErrorMessage("Parameter Contains Invalid Value : "
                                            + " subscriptionID");
                            bRet = false;
                        } else
                            bRet = true;
                    }
                } else {
                    if (deserializer.isInFilteringMode("subscriptionID") == false) {
                        deserializer
                                .setErrorMessage("Mandatory Parameter not found : "
                                        + " subscriptionID");
                        bRet = false;
                    } else
                        bRet = true;
                }
                if (retValue == true)
                    retValue = bRet;
            }

            {
                boolean isArray = deserializer.getIsArray("Events");
                int sizeOfArray = 0;

                if (deserializer.validateMandatory() == false) {
                    deserializer.setIDExcemption(true);
                }

                if (isArray) {
                    sizeOfArray = deserializer.getSize("Events");

                    if (sizeOfArray < 1) {
                        if ((deserializer.isInFilteringMode("Events") == false)) {
                            deserializer
                                    .setErrorMessage(" parameter item count is less than minOccures value specified in xsd : Events");
                            retValue = false;
                        }
                    }

                    if (sizeOfArray > 0) {
                        for (int i = 0; i < sizeOfArray; i++) {
                            gen.xsd.Events m = new gen.xsd.Events();

                            deserializer.setCurrentProperty("Events", i);

                            m.setInstanceName("Events");

                            boolean bRet = m.deSerialize(deserializer);
                            if (bRet == false) {
                                retValue = bRet;
                                break;
                            }

                            events.add(m);
                        }
                    } else if (sizeOfArray == 0) {
                        deserializer.removeParameter("Events");
                    }
                } else {
                    if (true == deserializer.hasProperty("Events")) {
                        gen.xsd.Events m = new gen.xsd.Events();
                        boolean bRet = m.deSerialize(deserializer);
                        if (bRet == false) {
                            retValue = bRet;
                        }
                        events.add(m);
                    } else {
                        if ((deserializer.isInFilteringMode("Events") == false)) {
                            deserializer
                                    .setErrorMessage("Parameter not found : "
                                            + " Events");
                            retValue = false;
                        }
                    }
                }
            }

        } catch (Exception e) {
            return false;
        }
        return retValue;

    }
}
