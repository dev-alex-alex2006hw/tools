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

package gen.client.resource;

import gen.xsd.Elements;
import OC.Cm.Client.Resource.IResourceResponseListener;
import OC.Cm.Client.Resource.Resource;
import OC.Cm.Connector.HeadersList;
import OC.Cm.Serialization.ISerializable;

/**
 * This class provides base listener methods to receive response of SHP
 * requests.<br>
 * <br>
 * 
 * Application developers must have the knowledge of input and output data
 * format of SHP requests. Then only they can properly type cast the response
 * data.<br>
 * <br>
 * 
 * Application needs to type cast the response data to corresponding data class
 * generated by SHP-SDK. SHP-SDK also generates resource specific controllers
 * and status listeners. It is advisable to use these resource specific
 * controllers and interfaces to avoid type casting.
 * 
 * @since 1.0.0
 */
public class TemperatureResource extends Resource implements
        IResourceResponseListener {
    /**
     * Variable that contains ITemperatureResourceResponseListener object.
     */
    ITemperatureResourceResponseListener p_respListener;

    /**
     * Constructor of TemperatureResource class.
     * 
     * @param context
     *            Context of SHP framework
     * @param protocol
     *            Specify type of protocol to be used (http, https, scs, shs)
     * @param deviceAddress
     *            Address of peer device. String format can be different for
     *            different protocol. (IP address:port [http,https,shs] or
     *            PeerID [scs])
     * @since 1.0.0
     */
    public TemperatureResource(long context, String protocol,
            String deviceAddress) {
        super(context, protocol, deviceAddress);
    }

    /**
     * This method will initialize p_respListener variable.<br>
     * Please make sure that user must register their own listener class through
     * this method before sending a request. Otherwise, all the received
     * response will be ignored.
     * 
     * @param TemperatureResourceResponseListener
     *            Object that implements ITemperatureResourceResponseListener
     *            interface
     * @since 1.0.0
     */
    public void addResponseListener(
            ITemperatureResourceResponseListener respListener) {
        p_respListener = respListener;
    }

    /**
     * Base listener method to receive a response of GET request.
     * 
     * @param clientSessionId
     *            Id of the request to which current response belongs
     * @param statusCode
     *            Http status code of the response
     * @param headers
     *            Response headers
     * @param respData
     *            Received Temperature object through the deserializer. This
     *            object should not be re-initialized by the user.
     * @since 1.0.0
     */
    @Override
    public void OnGetResponseReceived(int clientSessionId, int statusCode,
            HeadersList headers, ISerializable respData) {
        if (p_respListener != null) {
            if (respData != null) {
                String elementName = respData.getElementName();

                if (0 == elementName.compareTo(Elements.EN_TEMPERATURE)) {
                    gen.xsd.Temperature device = (gen.xsd.Temperature) respData;
                    p_respListener.onGetTemperature(clientSessionId,
                            statusCode, device);
                } else {
                    p_respListener.onGetTemperature(clientSessionId, 400, null);
                }
            } else {
                p_respListener.onGetTemperature(clientSessionId, statusCode,
                        null);
            }
        }
    }

    /**
     * Base listener method to receive a response of PUT request.
     * 
     * @param clientSessionId
     *            Id of the request to which current response belongs
     * @param statusCode
     *            Http status code of the response
     * @param headers
     *            Response headers
     * @param respData
     *            Received object through the deserializer. This object should
     *            not be re-initialized by the user.
     * @since 1.0.0
     */
    @Override
    public void OnPutResponseReceived(int clientSessionId, int statusCode,
            HeadersList headers, ISerializable respData) {
        if (p_respListener != null) {
            p_respListener.onPutTemperature(clientSessionId, statusCode);
        }
    }

    /**
     * Base listener method to receive a response of POST request.
     * 
     * @param clientSessionId
     *            Id of the request to which current response belongs
     * @param statusCode
     *            Http status code of the response
     * @param headers
     *            Response headers
     * @param respData
     *            Received object through the deserializer. This object should
     *            not be re-initialized by the user.
     * @since 1.0.0
     */
    @Override
    public void OnPostResponseReceived(int clientSessionId, int statusCode,
            HeadersList headers, ISerializable respData) {
        if (p_respListener != null) {
        }
    }

    /**
     * Base listener method to receive a response of DELETE request.
     * 
     * @param clientSessionId
     *            Id of the request to which current response belongs
     * @param statusCode
     *            Http status code of the response
     * @param headers
     *            Response headers
     * @param respData
     *            Received object through the deserializer. This object should
     *            not be re-initialized by the user.
     * @since 1.0.0
     */
    @Override
    public void onDeleteResponseReceived(int clientSessionId, int statusCode,
            HeadersList headers, ISerializable respData) {
        if (p_respListener != null) {
        }
    }

    /**
     * Base listener method to receive a response of add subscription request.<br>
     * In order to make this function to be called, please see the
     * OC.Cm.Notification.ISubscriptionManager.addSubscription() method.<br>
     * Below sample code shows how send a subscription request to the specific
     * resource.
     * 
     * <p>
     * <blockquote>
     * 
     * <pre>
     * SHP shp = OC.Cm.SHP.getInstance(&quot;shpContext&quot;);
     * String protocol = &quot;http&quot;;
     * String uuid = &quot;f0c0f83a-827a--0000-0000-000000000000&quot;;
     * String deviceAddress = &quot;192.168.100.2:8888&quot;;
     * String selfUuid = &quot;f0c0f83a-827a-0000-0000-000000000000&quot;;
     * String[] resourcePaths = new String[] { &quot;/devices&quot;, &quot;/groups&quot;, &quot;/energy&quot; };
     * 
     * try {
     *     shp.getSubscriptionManager().addSubscription(protocol, uuid, deviceAddress,
     *             selfuuid, resourcePaths, new ResourceResponseImplementation());
     * } catch (Exception e) {
     *     e.printStackTrace();
     * }
     * </pre>
     * 
     * </blockquote>
     * <p>
     * 
     * @param clientSessionId
     *            Id of the request to which current response belongs
     * @param statusCode
     *            Http status code of the response
     * @param subscriptionUri
     *            Subscription URI which corresponds to a specific resource
     *            created by a server
     * @since 1.0.0
     */
    @Override
    public void onSubscribeResponseReceived(int clientSessionId,
            int statusCode, String subscriptionUri) {
        if (p_respListener != null) {
        }
    }

    /**
     * Base listener method to receive a response of remove subscription
     * request.<br>
     * In order to make this function to be called, please see the
     * OC.Cm.Notification.ISubscriptionManager.removeSubscription() method.<br>
     * Below sample code shows how to send a unsubscription request to the
     * specific resource.
     * 
     * <p>
     * <blockquote>
     * 
     * <pre>
     * SHP shp = OC.Cm.SHP.getInstance(&quot;shpContext&quot;);
     * String uuid = &quot;f0c0f83a-827a-0000-0000-000000000000&quot;;
     * String deviceAddress = &quot;192.168.100.2:8888&quot;;
     * String protocol = &quot;https&quot;;
     * String[] resourcePaths = new String[] { &quot;/devices&quot;, &quot;/groups&quot;, &quot;/energy&quot; };
     * 
     * try {
     *     shp.getSubscriptionManager().removeSubscription(uuid, deviceAddress,
     *             protocol, resourcePaths, new ResourceResponseImplementation());
     * } catch (Exception e) {
     *     e.printStackTrace();
     * }
     * </pre>
     * 
     * </blockquote>
     * <p>
     * 
     * @param clientSessionId
     *            Id of the request to which current response belongs
     * @param statusCode
     *            Http status code of the response
     * @since 1.0.0
     */
    @Override
    public void onUnSubscribeResponseReceived(int clientSessionId,
            int statusCode) {
        if (p_respListener != null) {
        }
    }

    /**
     * Error callback method for the http requests sent using this class.
     * 
     * @param clientSessionId
     *            Id of the request to which current response belongs
     * @param statusCode
     *            (-1) Unable to provide a http status code / Http status code
     * @param errorCode
     *            Error code defined by a SHP framework. Please see the
     *            OC.Cm.SHPErrorCode enumeration.
     * @param errorMessage
     *            Description of the error
     * @param errorResponse
     *            Serializable object which contains detailed error information
     * @since 1.0.0
     */
    @Override
    public void onErrorReceived(int clientSessionId, int statusCode,
            OC.Cm.CMErrorCode errorCode, String errorMessage,
            OC.Cm.Serialization.ISerializable errorResponse) {
        if (p_respListener != null)
            p_respListener.onError(clientSessionId, statusCode, errorCode,
                    (OC.Cm.Serialization.Xsd.CMErrorMessage) errorResponse);
    }

    /**
     * Callback method which indicates the completion of processing http
     * requests sent using this class.<br>
     * If application is interested in request and response payload, this method
     * can provide those information. Also, indicates request processing is
     * completed.<br>
     * Please note that this method will be called after SHP framework calling
     * the one of those http response listener or error callback method.
     * 
     * @param clientSessionId
     *            Id of the request to which current response belongs
     * @param requestPayload
     *            HTTP request data
     * @param responsePayload
     *            HTTP response data
     * 
     * @since 1.0.0
     */
    @Override
    public void onRequestComplete(int clientSessionId, String requestPayload,
            String responsePayload) {
        // Auto-generated method stub
    }

    /**
     * This method sends a http GET request to the Temperature resource. This is
     * an asynchronous method.<br>
     * Response of this request can be achieved through the
     * gen.client.resource.TemperatureResource.OnGetResponseReceived() method.
     * 
     * @return (clientSessionId) Id of the request to which current request
     *         belongs. This value is equivalent to the first argument of the
     *         OnGetResponseReceived() method.<br>
     *         (-1) In case of any error. Error description will be printed out
     *         to the console if available.
     */
    public int getTemperature() {
        try {
            return this.get(null, this);
        } catch (Exception e) {
            return -1;
        }
    }

    /**
     * This method sends a http PUT request to the Temperature resource. This is
     * an asynchronous method.<br>
     * Response of this request can be achieved through the
     * gen.client.resource.TemperatureResource.OnPutResponseReceived() method.
     * 
     * @param reqData
     *            Temperature object to be sent
     * 
     * @return (clientSessionId) Id of the request to which current request
     *         belongs. This value is equivalent to the first argument of the
     *         OnPutResponseReceived() method.<br>
     *         (-1) In case of any error. Error description will be printed out
     *         to the console if available.
     */
    public int putTemperature(gen.xsd.Temperature reqData) {
        try {
            return this.put(null, (OC.Cm.Serialization.ISerializable) reqData,
                    this);
        } catch (Exception e) {
            return -1;
        }
    }

    /**
     * This method will designate a resource path corresponds to this
     * Temperature resource.
     * 
     * @param deviceId
     *            DeviceId that represents [/devices] resource.
     * @param temperatureId
     *            TemperatureId that represents [/temperatures] resource.
     */
    public void buildPath(String deviceId, String temperatureId) {
        buildTemplatePath("/devices/{deviceId}/temperatures/{temperatureId}",
                deviceId, temperatureId);
    }
}
