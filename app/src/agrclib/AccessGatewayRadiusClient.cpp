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

    std::cout << "Access Gateway Radius Client initialization\n";

    rc_openlog("AccessGatewayRadiusClient");    
    cout << "config file: " << RC_CONFIG_FILE;

    FILE *configFile = fopen(RC_CONFIG_FILE, "r");

    if (configFile == NULL) {
        cout << "Config file does not exist\n";
        return;
    } else {
        cout << "Config file  exist\n";
        fclose(configFile);
    }

    rh = rc_read_config(RC_CONFIG_FILE);
    if (rh == NULL)
    {
        rc_log(LOG_INFO, "Initialization not successful");
    } else {
        initialized = true;
    }
}

AccessGatewayRadiusClient::~AccessGatewayRadiusClient()
{
    rc_log(LOG_INFO, "Closing the handle, rh: %p", rh); 
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

/*
    attributeId = PW_USER_NAME;
    stringAttributeValue = "8675309867530900004_5a04e0";
    stringAttributeValue = "1";

    cout << "Attribute Id: " << attributeId << "\n";
    cout << "Attribute value(string): " << stringAttributeValue << "\n";
*/    

    list<AccessGatewayRadiusClient::AgrcAttribute>::iterator it;

    for (it = (*sendAttributeList).begin(); it != (*sendAttributeList).end(); ++it)
    {
        cout << "Attribute id: " << it->attributeId << "\n";
        cout << "Attribute String value: " << it->attributeStringValue << "\n";        
        cout << "Attribute Int value: " << it->attributeIntValue << "\n";                
    }

    receiveAttribute.attributeId          = 995;
    receiveAttribute.attributeStringValue = "receiveAttribute_005";
    receiveAttributeList->push_back(receiveAttribute);

    /*
     * Fill in User-Name

    if (rc_avpair_add(rh, &sendAttributes, PW_USER_NAME, stringAttributeValue.c_str(), -1, 0) == NULL) {
        printf ("%d: code here\n", __LINE__);
        requestStatus = AGRC_FAIL;
        return (requestStatus);  
    }
     */

    return (requestStatus);
    //strcpy(username, "my-username");
    //strcpy(username, "bob");
    //strcpy(username, "8675309867530900004_5a04e0");
	//printf ("%d: username: %s", __LINE__, username);

    //strcpy(passwd, "my-password");
    //strcpy(passwd, "hello");
    //strcpy(passwd, "1");
    //strcpy(passwd, "wrong-pasword");
}