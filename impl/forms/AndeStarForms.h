#pragma once
// ------------------------------------------------------------------
// Mavis forms for AndeStar V5 extensions
// (c) 2024 Condor Computing Corp
//
// TODO: These are marked specifically AndeStar, in future see if
//       these can be inherited from a 'custom' base class and 
//       specialized for the AS instructions
// ------------------------------------------------------------------
#include "mavis/Form.h"
#include <map>
#include <cinttypes>

namespace mavis {

// ------------------------------------------------------------------
// AndeStar Form Custom 0
//
//   This form has a non-contiguous 18b immediate field
//   named as simply IMM, bit re-ordering is handled in
//   the extractor
//
//   There is a 2bit opcode extension FUNC2.
//   The opcode is the predefined custom opcode (0x0b)
//
//   e.g. see ADDIGP
// ------------------------------------------------------------------
class Form_AndeStar_Custom_0
{
public:
    enum idType : uint32_t
    {
        IMM18 = 0,
        FUNC2,
        RD,
        OPCODE,
        __N
    };

    static const char * name;
    static const FieldsType fields;
    static const std::map<std::string, const Field &> fmap;
    static const std::map<std::string, idType> imap;
    static const FieldsType opcode_fields;
    static const ImmediateType immediate_type;
};

//// ------------------------------------------------------------------
//// AndeStar Form Custom 1_LOAD
////
////   This form has a non-contiguous 17b immediate field
////   named as simply IMM, bit re-ordering is handled in
////   the extractor.
////
////   There is a 3bit opcode extension FUNC3.
////   This is the load form, RD is present
////   The opcode is the predefined custom opcode (0x2b)
////
////   e.g. see LWGP
//// ------------------------------------------------------------------
//class Form_AndeStar_Custom_1_LOAD
//{
//public:
//    enum idType : uint32_t
//    {
//        IMM17 = 0,
//        FUNC3,
//        RD,
//        OPCODE,
//        __N
//    };
//
//    static const char * name;
//    static const FieldsType fields;
//    static const std::map<std::string, const Field &> fmap;
//    static const std::map<std::string, idType> imap;
//    static const FieldsType opcode_fields;
//    static const ImmediateType immediate_type;
//};
//
//// ------------------------------------------------------------------
//// AndeStar Form Custom 1_STORE
////
////   This form has a non-contiguous 17b immediate field
////   named as simply IMM, bit re-ordering is handled in
////   the extractor.
////
////   There is a 3bit opcode extension FUNC3.
////   This is the store form, RS2 is present
////   The opcode is the predefined custom opcode (0x2b)
////
////   e.g. see SDGP
//// ------------------------------------------------------------------
//class Form_AndeStar_Custom_1_STORE
//{
//public:
//    enum idType : uint32_t
//    {
//        IMM7=0,      // 31:25, { imm[19], imm[10:5]  }
//        RS2,
//        IMM5A,       // 19:15, { imm[14:12], imm[16:15] }
//        FUNC3,
//        IMM5B,       // 11:7,  { imm[4:3], imm[18:17], imm[11] }
//        OPCODE,
//        __N
//    };
//
//    static const char * name;
//    static const FieldsType fields;
//    static const std::map<std::string, const Field &> fmap;
//    static const std::map<std::string, idType> imap;
//    static const FieldsType opcode_fields;
//    static const ImmediateType immediate_type;
//};

} // namespace mavis
