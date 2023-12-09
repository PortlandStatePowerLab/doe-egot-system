#ifndef __DEMAND_RESPONSE_H__
#define __DEMAND_RESPONSE_H__
#include "simple_types.hpp"

namespace sep {
struct DemandResponseProgramListLink : ListLink {};
struct DemandResponseProgramLink : Link {};

///
/// Demand response program.
///
struct DemandResponseProgram : IdentifiedObject {
  // TODO
};
} // namespace sep

#endif // __DEMAND_RESPONSE_H__
