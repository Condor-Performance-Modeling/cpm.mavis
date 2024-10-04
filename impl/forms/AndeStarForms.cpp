#include "impl/forms/AndeStarForms.h"

namespace mavis {

// ----------------------------------------------------------------------
// Form_AndeStar_Custom_0 (see ADDIGP)
// ----------------------------------------------------------------------
const char * Form_AndeStar_Custom_0::name {"AndeStar_Custom_0"};

const FieldsType Form_AndeStar_Custom_0::fields
{
    Field("imm18", 14, 18),
    Field("func2", 12,  2),
    Field("rd",     7,  5),
    Field("opcode", 0,  7)
};

const std::map<std::string, const Field &> Form_AndeStar_Custom_0::fmap
{
    {"imm18", Form_AndeStar_Custom_0::fields[Form_AndeStar_Custom_0::idType::IMM18]},
    {"func2", Form_AndeStar_Custom_0::fields[Form_AndeStar_Custom_0::idType::FUNC2]},
    {"rd",    Form_AndeStar_Custom_0::fields[Form_AndeStar_Custom_0::idType::RD]},
    {"opcode",Form_AndeStar_Custom_0::fields[Form_AndeStar_Custom_0::idType::OPCODE]}
};

const std::map<std::string,Form_AndeStar_Custom_0::idType>
                                            Form_AndeStar_Custom_0::imap
{
    {"imm18", Form_AndeStar_Custom_0::idType::IMM18},
    {"func2", Form_AndeStar_Custom_0::idType::FUNC2},
    {"rd",    Form_AndeStar_Custom_0::idType::RD},
    {"opcode",Form_AndeStar_Custom_0::idType::OPCODE}
};

const FieldsType Form_AndeStar_Custom_0::opcode_fields
{
    Form_AndeStar_Custom_0::fields[Form_AndeStar_Custom_0::idType::OPCODE],
    Form_AndeStar_Custom_0::fields[Form_AndeStar_Custom_0::idType::FUNC2]
};

const ImmediateType Form_AndeStar_Custom_0::immediate_type = ImmediateType::SIGNED;

// ----------------------------------------------------------------------
// Form_AndeStar_Custom_1_LOAD (see LWGP)
// ----------------------------------------------------------------------
const char * Form_AndeStar_Custom_1_LOAD::name {"AndeStar_Custom_1_LOAD"};

const FieldsType Form_AndeStar_Custom_1_LOAD::fields
{
    Field("imm17",  15, 17),
    Field("func3",  12,  3),
    Field("rd",      7,  5),
    Field("opcode",  0,  7)
};

const std::map<std::string, const Field &> Form_AndeStar_Custom_1_LOAD::fmap
{
    {"imm17", Form_AndeStar_Custom_1_LOAD::fields[Form_AndeStar_Custom_1_LOAD::idType::IMM17]},
    {"func3", Form_AndeStar_Custom_1_LOAD::fields[Form_AndeStar_Custom_1_LOAD::idType::FUNC3]},
    {"rd",    Form_AndeStar_Custom_1_LOAD::fields[Form_AndeStar_Custom_1_LOAD::idType::RD]},
    {"opcode",Form_AndeStar_Custom_1_LOAD::fields[Form_AndeStar_Custom_1_LOAD::idType::OPCODE]}
};

const std::map<std::string,Form_AndeStar_Custom_1_LOAD::idType> Form_AndeStar_Custom_1_LOAD::imap
{
    {"imm17", Form_AndeStar_Custom_1_LOAD::idType::IMM17},
    {"func3", Form_AndeStar_Custom_1_LOAD::idType::FUNC3},
    {"rd",    Form_AndeStar_Custom_1_LOAD::idType::RD},
    {"opcode",Form_AndeStar_Custom_1_LOAD::idType::OPCODE}
};

const FieldsType Form_AndeStar_Custom_1_LOAD::opcode_fields
{
    Form_AndeStar_Custom_1_LOAD::fields[Form_AndeStar_Custom_1_LOAD::idType::OPCODE],
    Form_AndeStar_Custom_1_LOAD::fields[Form_AndeStar_Custom_1_LOAD::idType::FUNC3]
};

const ImmediateType Form_AndeStar_Custom_1_LOAD::immediate_type = ImmediateType::SIGNED;

// ----------------------------------------------------------------------
// Form_AndeStar_Custom_1_STORE (see SDGP)
// ----------------------------------------------------------------------
const char * Form_AndeStar_Custom_1_STORE::name {"AndeStar_Custom_1_STORE"};

const FieldsType Form_AndeStar_Custom_1_STORE::fields
{
    Field("imm7",   25,  7),  // 31:25, { imm[19],    imm[10:5]           }
    Field("rs2",    20,  5),
    Field("imm5a",  15,  5),  // 19:15, { imm[14:12], imm[16:15]          }
    Field("func3",  12,  3),
    Field("imm5b",  15,  5),  // 11:7,  { imm[4:3],   imm[18:17], imm[11] }
    Field("opcode",  0,  7)
};

const std::map<std::string, const Field &> Form_AndeStar_Custom_1_STORE::fmap
{
    {"imm7",  Form_AndeStar_Custom_1_STORE::fields[Form_AndeStar_Custom_1_STORE::idType::IMM7]},
    {"rs2",   Form_AndeStar_Custom_1_STORE::fields[Form_AndeStar_Custom_1_STORE::idType::RS2]},
    {"imm5a", Form_AndeStar_Custom_1_STORE::fields[Form_AndeStar_Custom_1_STORE::idType::IMM5A]},
    {"func3", Form_AndeStar_Custom_1_STORE::fields[Form_AndeStar_Custom_1_STORE::idType::FUNC3]},
    {"imm5b", Form_AndeStar_Custom_1_STORE::fields[Form_AndeStar_Custom_1_STORE::idType::IMM5B]},
    {"opcode",Form_AndeStar_Custom_1_STORE::fields[Form_AndeStar_Custom_1_STORE::idType::OPCODE]}
};

const std::map<std::string,Form_AndeStar_Custom_1_STORE::idType> 
                                            Form_AndeStar_Custom_1_STORE::imap
{
    {"imm7",  Form_AndeStar_Custom_1_STORE::idType::IMM7},
    {"rs2",   Form_AndeStar_Custom_1_STORE::idType::RS2},
    {"imm5a", Form_AndeStar_Custom_1_STORE::idType::IMM5A},
    {"func3", Form_AndeStar_Custom_1_STORE::idType::FUNC3},
    {"imm5b", Form_AndeStar_Custom_1_STORE::idType::IMM5B},
    {"opcode",Form_AndeStar_Custom_1_STORE::idType::OPCODE}
};

const FieldsType Form_AndeStar_Custom_1_STORE::opcode_fields
{
    Form_AndeStar_Custom_1_STORE::fields[Form_AndeStar_Custom_1_STORE::idType::OPCODE],
    Form_AndeStar_Custom_1_STORE::fields[Form_AndeStar_Custom_1_STORE::idType::FUNC3]
};

const ImmediateType Form_AndeStar_Custom_1_STORE::immediate_type = ImmediateType::SIGNED;



} // namespace mavis
