#ifndef __CUSTOMER_ACCOUNT_H__
#define __CUSTOMER_ACCOUNT_H__
#include "simple_types.hpp"

namespace sep{
    struct CustomerAccountListLink : ListLink {};
    struct CustomerAccountLink : Link {};
    
    struct CustomerAccount : IdentifiedObject{
        UInt16 currency;
        String42 customer_account;
        CustomerAgreementListLink customer_agreement_list_link;
        String42 customer_name;
        PowerOfTenMultiplierType price_power_of_ten_multiplier;
        ServiceSupplierLink service_supplier_link;

    }
}

#endif // __CUSTOMER_ACCOUNT_H__