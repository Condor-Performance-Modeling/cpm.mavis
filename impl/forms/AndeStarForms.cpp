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

// ----------------------------------------------------------------------
// Form_AndeStar_Custom_2 (DECODE ONLY FORM)
// ----------------------------------------------------------------------
const char * Form_AndeStar_Custom_2::name {"AndeStar_Custom_2"};

const FieldsType Form_AndeStar_Custom_2::fields
        {
                Field("func1a", 31,  1),
                Field("func1b", 30,  1),
                Field("func5",  25,  5),
                Field("func3",  12,  3),
                Field("opcode",  0,  7)
        };

const std::map<std::string, const Field &> Form_AndeStar_Custom_2::fmap
        {
                {"func1a",  Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::FUNC1A]},
                {"func1b",   Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::FUNC1B]},
                {"func5", Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::FUNC5]},
                {"func3", Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::FUNC3]},
                {"opcode",Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::OPCODE]}
        };

const std::map<std::string,Form_AndeStar_Custom_2::idType>
        Form_AndeStar_Custom_2::imap
        {
                {"func1a",  Form_AndeStar_Custom_2::idType::FUNC1A},
                {"func1b",   Form_AndeStar_Custom_2::idType::FUNC1B},
                {"func5", Form_AndeStar_Custom_2::idType::FUNC5},
                {"func3", Form_AndeStar_Custom_2::idType::FUNC3},
                {"opcode",Form_AndeStar_Custom_2::idType::OPCODE}
        };

const FieldsType Form_AndeStar_Custom_2::opcode_fields
        {
                Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::OPCODE],
                Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::FUNC3],
                Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::FUNC5],
                Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::FUNC1B],
                Form_AndeStar_Custom_2::fields[Form_AndeStar_Custom_2::idType::FUNC1A]
        };

const ImmediateType Form_AndeStar_Custom_2::immediate_type = ImmediateType::SIGNED;

// ----------------------------------------------------------------------
// Form_AndeStar_Custom_2_BBx (For EXTRACTION ONLY, "xform")
//
//      For BBC and BBS
// ----------------------------------------------------------------------
const char * Form_AndeStar_Custom_2_BBx::name {"AndeStar_Custom_2_BBx"};

const FieldsType Form_AndeStar_Custom_2_BBx::fields
        {
                Field("imm10", 31,  1),
                Field("imm9_5", 25,  5),
                Field("cimm4_0",  20,  5),
                Field("rs1",  15,  5),
                Field("imm4_1",  8,  4),
                Field("cimm5",  7,  1),
        };

const std::map<std::string, const Field &> Form_AndeStar_Custom_2_BBx::fmap
        {
                {"imm10",  Form_AndeStar_Custom_2_BBx::fields[Form_AndeStar_Custom_2_BBx::idType::IMM10]},
                {"imm9_5",   Form_AndeStar_Custom_2_BBx::fields[Form_AndeStar_Custom_2_BBx::idType::IMM9_5]},
                {"cimm4_0", Form_AndeStar_Custom_2_BBx::fields[Form_AndeStar_Custom_2_BBx::idType::CIMM4_0]},
                {"rs1", Form_AndeStar_Custom_2_BBx::fields[Form_AndeStar_Custom_2_BBx::idType::RS1]},
                {"imm4_1",Form_AndeStar_Custom_2_BBx::fields[Form_AndeStar_Custom_2_BBx::idType::IMM4_1]},
                {"cimm5",Form_AndeStar_Custom_2_BBx::fields[Form_AndeStar_Custom_2_BBx::idType::CIMM5]},
        };

const std::map<std::string,Form_AndeStar_Custom_2_BBx::idType>
        Form_AndeStar_Custom_2_BBx::imap
        {
                {"imm10",  Form_AndeStar_Custom_2_BBx::idType::IMM10},
                {"imm9_5",   Form_AndeStar_Custom_2_BBx::idType::IMM9_5},
                {"cimm4_0", Form_AndeStar_Custom_2_BBx::idType::CIMM4_0},
                {"rs1", Form_AndeStar_Custom_2_BBx::idType::RS1},
                {"imm4_1",Form_AndeStar_Custom_2_BBx::idType::IMM4_1},
                {"cimm5",Form_AndeStar_Custom_2_BBx::idType::CIMM5}
        };

const FieldsType Form_AndeStar_Custom_2_BBx::opcode_fields
        {};

const ImmediateType Form_AndeStar_Custom_2_BBx::immediate_type = ImmediateType::SIGNED;

// ----------------------------------------------------------------------
// Form_AndeStar_Custom_2_BxxC (For EXTRACTION ONLY, "xform")
//
//      For BEQC and BNEC
// ----------------------------------------------------------------------
const char * Form_AndeStar_Custom_2_BxxC::name {"AndeStar_Custom_2_BxxC"};

const FieldsType Form_AndeStar_Custom_2_BxxC::fields
        {
                Field("imm10", 31,  1),
                Field("cimm6", 30,  1),
                Field("imm9_5", 25,  5),
                Field("cimm4_0",  20,  5),
                Field("rs1",  15,  5),
                Field("imm4_1",  8,  4),
                Field("cimm5",  7,  1),
        };

const std::map<std::string, const Field &> Form_AndeStar_Custom_2_BxxC::fmap
        {
                {"imm10",  Form_AndeStar_Custom_2_BxxC::fields[Form_AndeStar_Custom_2_BxxC::idType::IMM10]},
                {"cimm6",  Form_AndeStar_Custom_2_BxxC::fields[Form_AndeStar_Custom_2_BxxC::idType::CIMM6]},
                {"imm9_5",   Form_AndeStar_Custom_2_BxxC::fields[Form_AndeStar_Custom_2_BxxC::idType::IMM9_5]},
                {"cimm4_0", Form_AndeStar_Custom_2_BxxC::fields[Form_AndeStar_Custom_2_BxxC::idType::CIMM4_0]},
                {"rs1", Form_AndeStar_Custom_2_BxxC::fields[Form_AndeStar_Custom_2_BxxC::idType::RS1]},
                {"imm4_1",Form_AndeStar_Custom_2_BxxC::fields[Form_AndeStar_Custom_2_BxxC::idType::IMM4_1]},
                {"cimm5",Form_AndeStar_Custom_2_BxxC::fields[Form_AndeStar_Custom_2_BxxC::idType::CIMM5]},
        };

const std::map<std::string,Form_AndeStar_Custom_2_BxxC::idType>
        Form_AndeStar_Custom_2_BxxC::imap
        {
                {"imm10",  Form_AndeStar_Custom_2_BxxC::idType::IMM10},
                {"cimm6",   Form_AndeStar_Custom_2_BxxC::idType::CIMM6},
                {"imm9_5",   Form_AndeStar_Custom_2_BxxC::idType::IMM9_5},
                {"cimm4_0", Form_AndeStar_Custom_2_BxxC::idType::CIMM4_0},
                {"rs1", Form_AndeStar_Custom_2_BxxC::idType::RS1},
                {"imm4_1",Form_AndeStar_Custom_2_BxxC::idType::IMM4_1},
                {"cimm5",Form_AndeStar_Custom_2_BxxC::idType::CIMM5}
        };

const FieldsType Form_AndeStar_Custom_2_BxxC::opcode_fields
        {};

const ImmediateType Form_AndeStar_Custom_2_BxxC::immediate_type = ImmediateType::SIGNED;

// ----------------------------------------------------------------------
// Form_AndeStar_Custom_2_BFOx (For EXTRACTION ONLY, "xform")
//
//      For BFOS and BFOZ
// ----------------------------------------------------------------------
const char * Form_AndeStar_Custom_2_BFOx::name {"AndeStar_Custom_2_BFOx"};

const FieldsType Form_AndeStar_Custom_2_BFOx::fields
        {
                Field("msb", 26,  6),
                Field("lsb", 20,  6),
                Field("rs1",  15,  5),
                Field("rd",  7,  5),
        };

const std::map<std::string, const Field &> Form_AndeStar_Custom_2_BFOx::fmap
        {
                {"msb",  Form_AndeStar_Custom_2_BFOx::fields[Form_AndeStar_Custom_2_BFOx::idType::MSB]},
                {"lsb",  Form_AndeStar_Custom_2_BFOx::fields[Form_AndeStar_Custom_2_BFOx::idType::LSB]},
                {"rs1", Form_AndeStar_Custom_2_BFOx::fields[Form_AndeStar_Custom_2_BFOx::idType::RS1]},
                {"rd", Form_AndeStar_Custom_2_BFOx::fields[Form_AndeStar_Custom_2_BFOx::idType::RD]},
        };

const std::map<std::string,Form_AndeStar_Custom_2_BFOx::idType>
        Form_AndeStar_Custom_2_BFOx::imap
        {
                {"msb",  Form_AndeStar_Custom_2_BFOx::idType::MSB},
                {"lsb",   Form_AndeStar_Custom_2_BFOx::idType::LSB},
                {"rs1", Form_AndeStar_Custom_2_BFOx::idType::RS1},
                {"rd", Form_AndeStar_Custom_2_BFOx::idType::RD},
        };

const FieldsType Form_AndeStar_Custom_2_BFOx::opcode_fields
        {};

const ImmediateType Form_AndeStar_Custom_2_BFOx::immediate_type = ImmediateType::NONE;


// ----------------------------------------------------------------------
// Form_AndeStar_Custom_2_LEA (For EXTRACTION ONLY, "xform")
//
//      For LEA* instructions
// ----------------------------------------------------------------------
const char * Form_AndeStar_Custom_2_LEA::name {"AndeStar_Custom_2_LEA"};

const FieldsType Form_AndeStar_Custom_2_LEA::fields
        {
                Field("rs2", 20,  5),
                Field("rs1",  15,  5),
                Field("rd",  7,  5),
        };

const std::map<std::string, const Field &> Form_AndeStar_Custom_2_LEA::fmap
        {
                {"rs2", Form_AndeStar_Custom_2_LEA::fields[Form_AndeStar_Custom_2_LEA::idType::RS2]},
                {"rs1", Form_AndeStar_Custom_2_LEA::fields[Form_AndeStar_Custom_2_LEA::idType::RS1]},
                {"rd", Form_AndeStar_Custom_2_LEA::fields[Form_AndeStar_Custom_2_LEA::idType::RD]},
        };

const std::map<std::string,Form_AndeStar_Custom_2_LEA::idType>
        Form_AndeStar_Custom_2_LEA::imap
        {
                {"rs2", Form_AndeStar_Custom_2_LEA::idType::RS2},
                {"rs1", Form_AndeStar_Custom_2_LEA::idType::RS1},
                {"rd", Form_AndeStar_Custom_2_LEA::idType::RD},
        };

const FieldsType Form_AndeStar_Custom_2_LEA::opcode_fields
        {};

const ImmediateType Form_AndeStar_Custom_2_LEA::immediate_type = ImmediateType::NONE;

} // namespace mavis
