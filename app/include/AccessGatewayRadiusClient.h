
#include <iostream>
#include <string>
#include <list>
#include <radcli/radcli.h>

#ifndef ACCESS_GATEWAY_RADIUS_CLIENT
#define ACCESS_GATEWAY_RADIUS_CLIENT 

using namespace std;

#define RC_CONFIG_FILE "/etc/agrc/radiusclient.conf"

// Vendor id of Nomadix
#define  VENDOR_NOMADIX  3309

//Vendor id of Wireless Broadband Alliance 
#define  VENDOR_WBA      14122

enum rc_nomadix_attr_id {
    NOMADIX_BW_UP                        =   1,   //!< Its type is integer
    NOMADIX_BW_DOWN                      =   2,   //!< Its type is integer    
    NOMADIX_REDIRECTION                  =   3,   //!< Its type is string
    NOMADIX_IP_UPSELL                    =   4,   //!< Its type is integer   
    NOMADIX_EXPIRATION                   =   5,   //!< Its type is string    
    NOMADIX_SUBNET                       =   6,   //!< Its type is string    
    NOMADIX_MAXBYTES_UP                  =   7,   //!< Its type is integer           
    NOMADIX_MAXBYTES_DOWN                =   8,   //!< Its type is integer               
    NOMADIX_ENDOFSESSION                 =   9,   //!< Its type is integer   
    NOMADIX_LOGOFF_URL                   =  10,   //!< Its type is string                        
    NOMADIX_NET_VLAN                     =  11,   //!< Its type is integer       
    NOMADIX_CONFIG_URL                   =  12,   //!< Its type is string           
    NOMADIX_GOODBYE_URL                  =  13,   //!< Its type is string               
    NOMADIX_QOS_POLICY                   =  14,   //!< Its type is string                   
    NOMADIX_RESERVED_1                   =  15,   //!< Its type is integer  
    NOMADIX_RESERVED_2                   =  16,   //!< Its type is integer      
    NOMADIX_SMTP_REDIRECT                =  17,   //!< Its type is integer
    NOMADIX_CENTRALIZED_AUTH             =  18,   //!< Its type is string    
    NOMADIX_GROUP_BW_POLICY_ID           =  19,   //!< Its type is integer   
    NOMADIX_GROUP_BW_MAX_UP              =  20,   //!< Its type is integer       
    NOMADIX_GROUP_BW_MAX_DOWN            =  21,   //!< Its type is integer           
    NOMADIX_MAXGIGWORDS_UP               =  22,   //!< Its type is integer               
    NOMADIX_MAXGIGWORDS_DOWN             =  23,   //!< Its type is integer                   
    NOMADIX_PREFERRED_WAN                =  24,   //!< Its type is string                     
    NOMADIX_USER_DEFINABLE_1             =  25,   //!< Its type is string                     
    NOMADIX_USER_DEFINABLE_2             =  26,   //!< Its type is string                     
    NOMADIX_BW_CLASS_NAME                =  27,   //!< Its type is string                     
    NOMADIX_MAXBYTES_TOTAL               =  28,   //!< Its type is integer                     
    NOMADIX_MAXGIGAWORDS_TOTAL           =  29   //!< Its type is integer                                         
}; 

enum rc_wba_attr_id {
    WBA_WISPR_LOCATION_ID                =   1,   //!< Its type is string                                       
}; 


class AccessGatewayRadiusClient
{
    private:
        bool        initialized;
        rc_handle   *rh;

    public:       
        enum AgrcStatus {
            AGRC_SUCCESS,
            AGRC_FAIL
        };

        enum AgrcRequestType {
            AGRC_AUTH_REQUEST,
            AGRC_ACCT_REQUEST
        };

        typedef struct AgrcAttribute_ {
            int32_t              attributeId;
            string               attributeStringName;
            rc_attr_type         attributeType;
            uint32_t             attributeIntValue;
            string               attributeStringValue;
            int32_t              vendorpec;
        } AgrcAttribute;
      
        AccessGatewayRadiusClient();
        ~AccessGatewayRadiusClient();
        AgrcStatus sendAuthRequest(AgrcRequestType reqType, 
                                   list<AccessGatewayRadiusClient::AgrcAttribute>*  sendAttributeList,  
                                   list<AccessGatewayRadiusClient::AgrcAttribute>*  receiveAttributeList);

        AgrcStatus sendAcctRequest(AgrcRequestType reqType, 
                                   list<AccessGatewayRadiusClient::AgrcAttribute>*  sendAttributeList);
};

#endif // ACCESS_GATEWAY_RADIUS_CLIENT