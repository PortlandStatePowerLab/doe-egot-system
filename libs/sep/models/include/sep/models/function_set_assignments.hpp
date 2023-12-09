#ifndef __FUNCTION_SET_ASSIGNMENTS_H__
#define __FUNCTION_SET_ASSIGNMENTS_H__
#include "function_set_assignments_base.hpp"
#include "simple_types.hpp"
#include "subscribable_type.hpp"

namespace sep {
struct FunctionSetAssignmentsListLink : ListLink {};
struct FunctionSetAssignmentsLink : Link {};

///
/// Provides an identifiable, subscribable collection of resources for
/// a particular device to consume.
///
struct FunctionSetAssignments : FunctionSetAssignmentsBase {
  mRIDType mrid;
  String32 description;
  VersionType version;
  SubscribableType subscribable;
};
} // namespace sep

#endif // __FUNCTION_SET_ASSIGNMENTS_H__
