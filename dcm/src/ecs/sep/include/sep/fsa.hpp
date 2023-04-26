#ifndef __FSA_H__
#define __FSA_H__

#include <flecs.h>
#include <string>
#include "simple_types.hpp"

namespace sep {
namespace fsab {

struct FunctionSetAssignmentsBase : sep::Resource {};
    
struct CustomerAccountListLink : ListLink {};

struct DemandResponseProgramListLink : ListLink {};

struct DERProgramListLink : ListLink {};

struct FileListLink : ListLink {};

struct MessagingProgramListLink : ListLink {};

struct PrepaymentListLink : ListLink {};

struct ResponseSetListLink : ListLink {};

struct TariffProfileListLink : ListLink {};

struct UsagePointListLink : ListLink {};

struct Module {
    Module(flecs::world& world);
};

} // namespace fsab
} // namespace sep

#endif // __FSA_H__