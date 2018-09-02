#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <list>
#include <arpa/inet.h>
#include "AccessGatewayRadiusClient.h"

using namespace std;

void 
sendAuthRequest()
{
    AccessGatewayRadiusClient *agrc = new AccessGatewayRadiusClient();

    AccessGatewayRadiusClient::AgrcAttribute currAttribute;
    list<AccessGatewayRadiusClient::AgrcAttribute>*  sendAttributeList = NULL;
    list<AccessGatewayRadiusClient::AgrcAttribute>*  receiveAttributeList = NULL;  
    list<AccessGatewayRadiusClient::AgrcAttribute>::iterator sendIt;      
    list<AccessGatewayRadiusClient::AgrcAttribute>::iterator receiveIt;          
    AccessGatewayRadiusClient::AgrcStatus result;

    sendAttributeList = new (list<AccessGatewayRadiusClient::AgrcAttribute>);
    receiveAttributeList = new (list<AccessGatewayRadiusClient::AgrcAttribute>);    

    currAttribute.attributeId          = PW_USER_NAME;
    currAttribute.attributeType        = PW_TYPE_STRING;
    currAttribute.attributeStringValue = "8675309867530900004_5a04e0";
    currAttribute.vendorpec            = VENDOR_NONE;      
    sendAttributeList->push_back(currAttribute);

    currAttribute.attributeId          = PW_USER_PASSWORD;
    currAttribute.attributeType        = PW_TYPE_STRING;
    currAttribute.attributeStringValue = "1";
    currAttribute.vendorpec            = VENDOR_NONE;      
    sendAttributeList->push_back(currAttribute);

    currAttribute.attributeId          = PW_SERVICE_TYPE;
    currAttribute.attributeType        = PW_TYPE_INTEGER;    
    currAttribute.attributeIntValue    = PW_LOGIN;
    sendAttributeList->push_back(currAttribute);

    currAttribute.attributeId          = PW_NAS_IP_ADDRESS;
    currAttribute.attributeType        = PW_TYPE_INTEGER;
    uint32_t intValue = 0;
    inet_pton(AF_INET, "10.12.13.14", &intValue);
    uint32_t  intNorder = htonl(intValue);
    currAttribute.attributeIntValue = intNorder;
    sendAttributeList->push_back(currAttribute);    

    currAttribute.attributeId          = PW_NAS_PORT;
    currAttribute.attributeType        = PW_TYPE_INTEGER;    
    currAttribute.attributeIntValue    = 0;
    sendAttributeList->push_back(currAttribute);

    currAttribute.attributeId          = PW_CALLED_STATION_ID;
    currAttribute.attributeType        = PW_TYPE_STRING;
    currAttribute.attributeStringValue = "00-50-E8-00-99-20";
    currAttribute.vendorpec            = VENDOR_NONE;      
    sendAttributeList->push_back(currAttribute);

    currAttribute.attributeId          = PW_CALLING_STATION_ID;
    currAttribute.attributeType        = PW_TYPE_STRING;
    currAttribute.attributeStringValue = "E0-B5-2D-AF-1C-50";
    currAttribute.vendorpec            = VENDOR_NONE;      
    sendAttributeList->push_back(currAttribute);

    currAttribute.attributeId          = NOMADIX_LOGOFF_URL;
    currAttribute.attributeType        = PW_TYPE_STRING;    
    currAttribute.attributeStringValue = "http://1.1.1.1";
    currAttribute.vendorpec            = VENDOR_NOMADIX;    
    sendAttributeList->push_back(currAttribute);   

    currAttribute.attributeId          = PW_NAS_IDENTIFIER;
    currAttribute.attributeType        = PW_TYPE_STRING;    
    currAttribute.attributeStringValue = "AG2400";
    currAttribute.vendorpec            = VENDOR_NONE;    
    sendAttributeList->push_back(currAttribute);   

    result = agrc->sendAuthRequest(AccessGatewayRadiusClient::AGRC_AUTH_REQUEST, 
                                   sendAttributeList,
                                   receiveAttributeList);
    cout << "result: " << result << "\n";                          

    cout << "Number of received attributes: " << receiveAttributeList->size() << "\n";                          

    // Process all the received attributes
    for (receiveIt = (*receiveAttributeList).begin(); receiveIt != (*receiveAttributeList).end(); ++receiveIt)
    {
        cout << "Receive Attribute id           : " << receiveIt->attributeId << "\n";
        cout << "Receive Attribute name         : " << receiveIt->attributeStringName << "\n";               
        cout << "Receive Attribute type         : " << receiveIt->attributeType << "\n";           
        cout << "Receive Attribute int value    : " << receiveIt->attributeIntValue << "\n";                        
        cout << "Receive Attribute String value : " << receiveIt->attributeStringValue << "\n";        
        cout << "Receive Attribute vendorpec    : " << receiveIt->vendorpec << "\n";                
        cout << "\n";           
    }

    //Delete all the send attributes
    sendAttributeList->erase(sendAttributeList->begin(), sendAttributeList->end());
    delete (sendAttributeList);

    //Delete all the receive attributes
    receiveAttributeList->erase(receiveAttributeList->begin(), receiveAttributeList->end());
    delete (receiveAttributeList);
}

void 
sendAcctRequest()
{
    AccessGatewayRadiusClient *agrc = new AccessGatewayRadiusClient();

    AccessGatewayRadiusClient::AgrcAttribute currAttribute;
    list<AccessGatewayRadiusClient::AgrcAttribute>*  sendAttributeList = NULL;
    list<AccessGatewayRadiusClient::AgrcAttribute>*  receiveAttributeList = NULL;  
    list<AccessGatewayRadiusClient::AgrcAttribute>::iterator sendIt;      
    list<AccessGatewayRadiusClient::AgrcAttribute>::iterator receiveIt;          
    AccessGatewayRadiusClient::AgrcStatus result;

    sendAttributeList = new (list<AccessGatewayRadiusClient::AgrcAttribute>);
    receiveAttributeList = new (list<AccessGatewayRadiusClient::AgrcAttribute>);    

    currAttribute.attributeId          = PW_ACCT_STATUS_TYPE;
    currAttribute.attributeType        = PW_TYPE_INTEGER;
    currAttribute.attributeIntValue    = 1;
    currAttribute.vendorpec            = VENDOR_NONE;      
    sendAttributeList->push_back(currAttribute);

    currAttribute.attributeId          = NOMADIX_SMTP_REDIRECT;
    currAttribute.attributeType        = PW_TYPE_INTEGER;    
    currAttribute.attributeIntValue    = 1;
    currAttribute.vendorpec            = VENDOR_NOMADIX;    
    sendAttributeList->push_back(currAttribute);                     

    result = agrc->sendAcctRequest(AccessGatewayRadiusClient::AGRC_ACCT_REQUEST, 
                                   sendAttributeList);
    cout << "result: " << result << "\n";                          

    //Delete all the send attributes
    sendAttributeList->erase(sendAttributeList->begin(), sendAttributeList->end());
    delete (sendAttributeList);

}

int main(int argc, char** argv)
{
    rc_openlog("AGRC");

    // Send auth request
    sendAuthRequest();

    // Send acct request
    sendAcctRequest();

    return 0;
}


