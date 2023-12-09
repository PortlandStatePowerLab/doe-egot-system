#ifndef __SERVICE_SUPPLIER_H__
#define __SERVICE_SUPPLIER_H__
#include "simple_types.hpp"

namespace sep {
struct ServiceSupplierLink : Link {};

///
/// Organisation that provides services to Customers.
///
struct ServiceSupplier : IdentifiedObject {
  String32 email;
  String20 phone;
  UInt32 provider_id;
  String42 web;
};
} // namespace sep

#endif // __SERVICE_SUPPLIER_H__
