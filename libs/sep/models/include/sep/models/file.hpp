#ifndef __FILE_H__
#define __FILE_H__
#include "simple_types.hpp"
#include "pen_type.hpp"

namespace sep{
    struct FileListLink : ListLink {};
    struct FileLink : Link {};
    
    // This resource contains various meta-data describing a file's 
    // characteristics.  The meta-data provides general file information 
    // and also is used to support filtered queries of file lists
    struct File : Resource {
        enum class Type : HexBinary16{
            SOFTWARE_IMAGE = 0x00,
            SECURITY_CREDENTIAL = 0x01,
            CONFIGURATION = 0x02,
            LOG = 0x03
        };

        TimeType activate_time;
        Link file_uri;
        HexBinary160 lfdi;
        String32 mf_hw_ver;
        PENType mf_id;
        String32 mf_model;
        String32 mf_ser_num;
        String16 mf_ver;
        UInt32 size;
        Type type;
    };
}

#endif // __FILE_H__