#ifndef __DER_PROGRAM_H__
#define __DER_PROGRAM_H__
#include "der_control.hpp"
#include "der_curve.hpp"
#include "primacy_type.hpp"
#include "subscribable_identified_object.hpp"

namespace sep {
struct DERProgramListLink : ListLink {};
struct DERProgramLink : Link {};

struct AssociatedDERProgramListLink : ListLink {};
struct AssociatedDERProgramLink : Link {};

struct CurrentDERProgramLink : Link {};

///
/// Distributed Energy Resource program
///
struct DERProgram : SubscribableIdentifiedObject {
  ActiveDERControlListLink active_der_control_list_link;
  DefaultDERControlLink default_der_control_link;
  DERControlListLink der_control_list_link;
  DERCurveListLink der_curve_list_link;
  PrimacyType primacy;
};

} // namespace sep

#endif // __DER_PROGRAM_H__
