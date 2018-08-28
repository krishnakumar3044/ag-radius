#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <list>
#include "AccessGatewayRadiusClient.h"

using namespace std;

int main(int argc, char** argv)
{
    AccessGatewayRadiusClient *agrc = new AccessGatewayRadiusClient();

    AccessGatewayRadiusClient::AgrcAttribute currAttribute;
    list<AccessGatewayRadiusClient::AgrcAttribute>*  sendAttributeList = NULL;
    list<AccessGatewayRadiusClient::AgrcAttribute>*  receiveAttributeList = NULL;  
    list<AccessGatewayRadiusClient::AgrcAttribute>::iterator sendIt;      
    list<AccessGatewayRadiusClient::AgrcAttribute>::iterator receiveIt;          

    sendAttributeList = new (list<AccessGatewayRadiusClient::AgrcAttribute>);
    receiveAttributeList = new (list<AccessGatewayRadiusClient::AgrcAttribute>);    

    currAttribute.attributeId          = PW_USER_NAME;
    currAttribute.attributeStringValue = "8675309867530900004_5a04e0";
    sendAttributeList->push_back(currAttribute);

    currAttribute.attributeId          = PW_USER_PASSWORD;
    currAttribute.attributeStringValue = "1";
    sendAttributeList->push_back(currAttribute);

    cout << "send size: " << sendAttributeList->size() << "\n";
    cout << "30: receive size: " << receiveAttributeList->size() << "\n";

    agrc->sendAuthRequest(AccessGatewayRadiusClient::AGRC_AUTH_REQUEST, 
                          sendAttributeList,
                          receiveAttributeList);
    cout << "35: receive size: " << receiveAttributeList->size() << "\n";                          

    // Process all the received attributes
    for (receiveIt = (*receiveAttributeList).begin(); receiveIt != (*receiveAttributeList).end(); ++receiveIt)
    {
        cout << "Attribute id: " << receiveIt->attributeId << "\n";
        cout << "Attribute String value: " << receiveIt->attributeStringValue << "\n";        
        cout << "Attribute Int value: " << receiveIt->attributeIntValue << "\n";                
    }

    //Delete all the send attributes
    //Delete all the receive attributes

    delete (sendAttributeList);
    delete (receiveAttributeList);

    return 0;
}


