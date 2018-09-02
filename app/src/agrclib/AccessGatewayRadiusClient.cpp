#include <stdio.h>
#include <syslog.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <radcli/radcli.h>
#include "AccessGatewayRadiusClient.h"

using namespace std;

AccessGatewayRadiusClient::AccessGatewayRadiusClient()
{
    initialized = false;

    //std::cout << "Access Gateway Radius Client initialization\n";

    rc_openlog("AccessGatewayRadiusClient");    
    cout << "config file: " << RC_CONFIG_FILE;

    FILE *configFile = fopen(RC_CONFIG_FILE, "r");

    if (configFile == NULL) {
        rc_log(LOG_INFO, "Config file %s does not exist", RC_CONFIG_FILE);
        initialized = false;
        return;
    } else {
        //cout << "Config file  exist\n";
        fclose(configFile);
    }

    rh = rc_read_config(RC_CONFIG_FILE);
    if (rh == NULL)
    {
        rc_log(LOG_INFO, "Initialization not successful");
        cout << "Initialization not successful" << "\n";
    } else {
        initialized = true;
    }
}

AccessGatewayRadiusClient::~AccessGatewayRadiusClient()
{
    rc_log(LOG_INFO, "Closing the handle, rh: %p", rh); 
    rc_destroy(rh);
    rh = NULL;
    initialized = false;
}

AccessGatewayRadiusClient::AgrcStatus 
AccessGatewayRadiusClient::sendAuthRequest(AgrcRequestType reqType, 
                                           list<AccessGatewayRadiusClient::AgrcAttribute>*  sendAttributeList, 
                                           list<AccessGatewayRadiusClient::AgrcAttribute>*  receiveAttributeList)                                           
{
    int32_t                                  attributeId;
    string                                   stringAttributeValue = "";
    int32_t                                  intAttributeValue = 0;    
    VALUE_PAIR                               *sendAttributes = NULL;
    VALUE_PAIR                               *receiveAttributes = NULL;
    AgrcStatus                               requestStatus = AGRC_SUCCESS;
    AccessGatewayRadiusClient::AgrcAttribute receiveAttribute;    
    int32_t                                  result;

    if (this->initialized == false)
    {
        cout << "Radius Client not initialized\n";
        return (AGRC_FAIL);
    } 

    list<AccessGatewayRadiusClient::AgrcAttribute>::iterator it;

    for (it = (*sendAttributeList).begin(); it != (*sendAttributeList).end(); ++it)
    {
/*        
        cout << "Attribute id: " << it->attributeId << "\n";      
        cout << "Attribute type: " << it->attributeType << "\n";                     
        cout << "Attribute int value: " << it->attributeIntValue << "\n";                
        cout << "Attribute String value: " << it->attributeStringValue << "\n";        
*/        

        switch (it->attributeType)
        {
            case PW_TYPE_INTEGER:
                if (rc_avpair_add(rh, &sendAttributes, it->attributeId, 
                              &(it->attributeIntValue), -1, 0) == NULL) {
                    requestStatus = AGRC_FAIL;
                    return (requestStatus);  
                }

                break;

            case PW_TYPE_STRING:
                if (rc_avpair_add(rh, &sendAttributes, it->attributeId, 
                                it->attributeStringValue.c_str(), -1, 0) == NULL) {
                    requestStatus = AGRC_FAIL;
                    return (requestStatus);  
                }
                break;

            case PW_TYPE_IPADDR:
            case PW_TYPE_DATE:
                if (rc_avpair_add(rh, &sendAttributes, it->attributeId, 
                                it->attributeStringValue.c_str(), -1, 0) == NULL) {
                    requestStatus = AGRC_FAIL;
                    return (requestStatus);  
                }
                break;

            default:
                break;

        }
    }

    result = rc_auth(rh, 0, sendAttributes, &receiveAttributes, NULL);

    if (result == OK_RC) {
        VALUE_PAIR *vp = NULL;
        if (reqType == AGRC_AUTH_REQUEST) {
            vp = receiveAttributes;
        } 

        char name[128];
        char value[128];
 
        //fprintf(stderr, "\"%s\" RADIUS Authentication OK\n", username);
        fprintf(stderr, "RADIUS Authentication OK\n");
 
        /* print the known attributes in the reply */
        while (vp != NULL) {
            if (rc_avpair_tostr(rh, vp, name, sizeof(name), value, sizeof(value)) == 0) {
                //fprintf(stderr, "%s:\t%s\n", name, value);
                //printf("%s:\t%s\n", name, value); 
                printf("%s:\t%s\n", name, value); 

                memset(&receiveAttribute, 0, sizeof(struct AccessGatewayRadiusClient::AgrcAttribute_));
                receiveAttribute.attributeId = vp->attribute;
                receiveAttribute.attributeType = vp->type;

                // Received Attribute is Vendor specific attribute
                if (receiveAttribute.attributeId > 0xffff) {
                    // VSA(Vendor specific attribute)
                    uint32_t localAttributeId = receiveAttribute.attributeId;
                    receiveAttribute.vendorpec = localAttributeId >> 16;
                    receiveAttribute.attributeId = localAttributeId & 0xffff;
                    //cout << "Vendor: " << receiveAttribute.vendorpec << "\n";
                    //cout << "Vendor attribute id: " << receiveAttribute.attributeId << "\n";
                } else {
                    receiveAttribute.vendorpec = VENDOR_NONE;
                }
                receiveAttribute.attributeStringName  = string(name);    
                if (receiveAttribute.attributeType == PW_TYPE_INTEGER) {
                    receiveAttribute.attributeIntValue = vp->lvalue;
                }                          
                receiveAttribute.attributeStringValue = string(value);                  
                receiveAttributeList->push_back(receiveAttribute);                
            }
            vp = vp->next;
        }
    } else {
        //fprintf(stderr, "\"%s\" RADIUS Authentication failure (RC=%i)\n", username, result);
        fprintf(stderr, "RADIUS Authentication failure (RC=%i)\n", result);
    }

    return (requestStatus);
}

AccessGatewayRadiusClient::AgrcStatus 
AccessGatewayRadiusClient::sendAcctRequest(AgrcRequestType reqType, 
                                           list<AccessGatewayRadiusClient::AgrcAttribute>*  sendAttributeList) 
{
    int32_t                                  attributeId;
    string                                   stringAttributeValue = "";
    int32_t                                  intAttributeValue = 0;    
    VALUE_PAIR                               *sendAttributes = NULL;
    VALUE_PAIR                               *receiveAttributes = NULL;
    AgrcStatus                               requestStatus = AGRC_SUCCESS;
    AccessGatewayRadiusClient::AgrcAttribute receiveAttribute;    
    int32_t                                  result;

    if (this->initialized == false)
    {
        cout << "Radius Client not initialized\n";        
        return (AGRC_FAIL);
    }  

    list<AccessGatewayRadiusClient::AgrcAttribute>::iterator it;

    for (it = (*sendAttributeList).begin(); it != (*sendAttributeList).end(); ++it)
    {
        cout << "Attribute id: " << it->attributeId << "\n";      
        cout << "Attribute type: " << it->attributeType << "\n";                     
        cout << "Attribute int value: " << it->attributeIntValue << "\n";                
        cout << "Attribute String value: " << it->attributeStringValue << "\n";        
        cout << "Attribute vendorpec: " << it->vendorpec << "\n";  
        cout << "\n";              
        /*
         * Fill in User-Name
         */
        switch (it->attributeType)
        {
            case PW_TYPE_INTEGER:
                if (rc_avpair_add(rh, &sendAttributes, it->attributeId, 
                              &(it->attributeIntValue), -1, it->vendorpec) == NULL) {
                    requestStatus = AGRC_FAIL;
                    return (requestStatus);  
                }

                break;

            case PW_TYPE_STRING:
                if (rc_avpair_add(rh, &sendAttributes, it->attributeId, 
                                it->attributeStringValue.c_str(), -1, it->vendorpec) == NULL) {
                    printf ("%d: code here\n", __LINE__);
                    requestStatus = AGRC_FAIL;
                    return (requestStatus);  
                }
                break;

            case PW_TYPE_IPADDR:

                break;

            default:
                break;

        }
    }

    result = rc_acct(rh, 0, sendAttributes);

    if (result == OK_RC) {
        fprintf(stderr, "RADIUS Accounting OK\n");
    } else {
        //fprintf(stderr, "\"%s\" RADIUS Authentication failure (RC=%i)\n", username, result);
        fprintf(stderr, "RADIUS Accounting failure (RC=%i)\n", result);
        cout << "RADIUS Accounting failure \n";
        requestStatus = AGRC_FAIL;
    }

    return (requestStatus);
}