
#include <iostream>
#include <string>
#include <list>
#include <radcli/radcli.h>

#ifndef ACCESS_GATEWAY_RADIUS_CLIENT
#define ACCESS_GATEWAY_RADIUS_CLIENT 

using namespace std;

#define RC_CONFIG_FILE "/etc/agrc/radiusclient.conf"

class AccessGatewayRadiusClient
{
    private:
        bool        initialized;
        rc_handle   *rh;

    public:

        const int32_t   AGRC_NOMADIX_VENDOR_ID = 3309;
        
        enum AgrcStatus {
            AGRC_SUCCESS,
            AGRC_FAIL
        };

        enum AgrcRequestType {
            AGRC_AUTH_REQUEST,
            AGRC_ACCT_REQUEST
        };

        enum AgrcAttributeList {
            AGRC
        };
        typedef struct {
            int32_t  attributeId;
            string   attributeStringValue;
            int32_t  attributeIntValue;
            int32_t  vendorpec;
        } AgrcAttribute;
      
        AccessGatewayRadiusClient();
        ~AccessGatewayRadiusClient();
        AgrcStatus sendAuthRequest(AgrcRequestType reqType, 
                                   list<AccessGatewayRadiusClient::AgrcAttribute>*  sendAttributeList,  
                                   list<AccessGatewayRadiusClient::AgrcAttribute>*  receiveAttributeList);
};

#endif // ACCESS_GATEWAY_RADIUS_CLIENT