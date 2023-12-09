#ifndef __PREPAYMENT_H__
#define __PREPAYMENT_H__
#include "simple_types.hpp"

namespace sep {
struct PrepaymentListLink : ListLink {};
struct PrepaymentLink : Link {};

///
/// Prepayment (inherited from CIM SDPAccountingFunction)
///
struct Prepayment : IdentifiedObject {
  // TODO
};
} // namespace sep

#endif // __PREPAYMENT_H__
