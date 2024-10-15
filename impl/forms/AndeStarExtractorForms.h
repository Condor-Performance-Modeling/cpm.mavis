#pragma once
//TODO: what does it mean that ADDIW has w-oper=all and l-oper=all
//
// w-oper   word    32b or XLEN ? TODO: same Q: about assumed width
// l-oper   long    TODO: what does mavis assume for long? Is it XLEN dependent?
// s-oper   float   single  single precision?
// d-oper   float   double I assume
// q-oper   float   quad   I assume
// v-oper   vector  
//
//TODO: is there a case in RV-ISA where a named field is fixed but also not zero,
//
#include "mavis/Extractor.h"
#include "mavis/DecoderTypes.h"
#include "mavis/DecoderConsts.h"
#include "impl/forms/CommonForms.h"
#include "impl/forms/CompressedForms.h"
#include "impl/forms/VectorForms.h"
#include "impl/forms/AndeStarForms.h"

#include <cinttypes>
#include <cassert>

namespace mavis {

// --------------------------------------------------------------------------- 
// Form_AndeStar_Custom_0 - Form Extractor
//
//000 ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
//001 uint64_t getSourceRegs(const Opcode icode) const override
//002 uint64_t getDestRegs(const Opcode icode) const override
//003 uint64_t getSourceOperTypeRegs(const Opcode icode,
//004 uint64_t getDestOperTypeRegs(const Opcode icode,
//005 OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
//006 OperandInfo getDestOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
//007 ImmediateType getImmediateType() const override
//008 uint64_t getImmediate(const Opcode icode) const override
//009 int64_t getSignedOffset(const Opcode icode) const override
//010 std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
//011 std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta)
// --------------------------------------------------------------------------- 
template<>
class Extractor<Form_AndeStar_Custom_0> : public ExtractorBase<Form_AndeStar_Custom_0>
{
public:
    Extractor() = default;

//000
    ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
    {
        return ExtractorIF::PtrType(new Extractor<Form_AndeStar_Custom_0>(ffmask, fset));
    }

//001
    uint64_t getSourceRegs(const Opcode icode) const override
    {
        return (1ull << REGISTER_ANDES_GP); //implied global pointer
    }

//002
    uint64_t getDestRegs(const Opcode icode) const override
    {
        return 1ull << extract_(Form_AndeStar_Custom_0::idType::RD, icode & ~fixed_field_mask_);
    }

//003
    uint64_t getSourceOperTypeRegs(const Opcode icode,
                                   const InstMetaData::PtrType &meta, InstMetaData::OperandTypes kind) const override
    {
        if (meta->isNoneOperandType(kind)) {
            return 0;
        } else if (meta->isAllOperandType(kind)) {
            return getSourceRegs(icode);
        } else {
//THIS CODE NEEDS DETAILED TESTING -- See the form Form_C2_sp_store (yes store, it was easier to reference)
            uint64_t result = 0;
            //Using type of RS1 for the type of the implied GP aka X3
            if (meta->isOperandType(InstMetaData::OperandFieldID::RS1, kind)) {
                result |= (1ull << REGISTER_ANDES_GP);
            }
            return result;
        }
    }

//004
    uint64_t getDestOperTypeRegs(const Opcode icode,
                                 const InstMetaData::PtrType &meta, InstMetaData::OperandTypes kind) const override
    {
        if (meta->isNoneOperandType(kind)) {
            return 0;
        } else if (meta->isAllOperandType(kind)) {
            return getDestRegs(icode);
        } else {
            uint64_t result = 0;
            if (meta->isOperandType(InstMetaData::OperandFieldID::RD, kind)) {
                result |= extractUnmaskedIndexBit_(Form_AndeStar_Custom_0::idType::RD, icode, fixed_field_mask_);
            }
            return result;
        }
    }

//005
    OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
                                     bool suppress_x0 = false) const override
    {
        OperandInfo olist;
        //ADDIGP has implied global pointer, typ. X3, this is the only source
        //using RS1 as the type index
        olist.addElement(InstMetaData::OperandFieldID::RS1, meta->getOperandType(InstMetaData::OperandFieldID::RS1),
                         REGISTER_ANDES_GP, false);
        return olist;
    }

//006
    OperandInfo getDestOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
                                   bool suppress_x0 = false) const override
    {
        OperandInfo olist;
        appendUnmaskedOperandInfo_(olist, icode, meta, InstMetaData::OperandFieldID::RD,
                                   fixed_field_mask_, Form_AndeStar_Custom_0::idType::RD,
                                   false, suppress_x0);
        return olist;
    }

//007
    ImmediateType getImmediateType() const override
    {
        return ImmediateType::SIGNED;
    }

//008
    uint64_t getImmediate(const Opcode icode) const override
    {
        const uint64_t imm18 = extract_(Form_AndeStar_Custom_0::idType::IMM18, icode & ~fixed_field_mask_);
        // Mapping:
        // src    17  16:7   6   5:3    2:1   0
        // dst    17  10:1  11  14:12  16:15  0
        //                 11111111----------
        //                 765432109876543210
        return ((imm18 & 0b100000000000000000) >>  0)  //17    -> 17
             | ((imm18 & 0b011111111110000000) >>  6)  //16:7  -> 10:1
             | ((imm18 & 0b000000000001000000) <<  5)  //6     -> 11    
             | ((imm18 & 0b000000000000111000) <<  9)  //5:3   -> 14:12
             | ((imm18 & 0b000000000000000110) << 14)  //2:1   -> 16:15
             | ((imm18 & 0b000000000000000001) <<  0); //0     -> 0    
    }

//009
    int64_t getSignedOffset(const Opcode icode) const override
    {
        return signExtend_(getImmediate(icode), 17);
    }

    using ExtractorIF::dasmString; // tell the compiler all dasmString
                                   // overloads are considered
//010
    std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
    {
        std::stringstream ss;
        ss << mnemonic
           << "\t" << extract_(Form_AndeStar_Custom_0::idType::RD, icode & ~fixed_field_mask_)
           << ", +0x" << std::hex << getSignedOffset(icode);
        return ss.str();
    }

//011
    std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta) const override
    {
        std::stringstream ss;
        ss << mnemonic << "\t"
           << dasmFormatRegList_(meta, icode, fixed_field_mask_,
                                 { { Form_AndeStar_Custom_0::idType::RD, InstMetaData::OperandFieldID::RD } })
           << ", +0x" << std::hex << getSignedOffset(icode);
        return ss.str();
    }

private:
    Extractor<Form_AndeStar_Custom_0>(const uint64_t ffmask, const uint64_t fset) :
        fixed_field_mask_(ffmask)
    {}

    uint64_t fixed_field_mask_ = 0;
};

// --------------------------------------------------------------------------- 
// Form_AndeStar_Custom_1_LOAD - Form Extractor
//
//000 ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
//001 uint64_t getSourceRegs(const Opcode icode) const override
//001.1 uint64_t getSourceAddressRegs(const Opcode icode) const override
//002 uint64_t getDestRegs(const Opcode icode) const override
//003 uint64_t getSourceOperTypeRegs(const Opcode icode,
//004 uint64_t getDestOperTypeRegs(const Opcode icode,
//005 OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
//006 OperandInfo getDestOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
//007 ImmediateType getImmediateType() const override
//008 uint64_t getImmediate(const Opcode icode) const override
//009 int64_t getSignedOffset(const Opcode icode) const override
//010 std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
//011 std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta)

// --------------------------------------------------------------------------- 
template<>
class Extractor<Form_AndeStar_Custom_1_LOAD> : public ExtractorBase<Form_AndeStar_Custom_1_LOAD>
{
public:
    Extractor() = default;
//000
    ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
    {
        return ExtractorIF::PtrType(new Extractor<Form_AndeStar_Custom_1_LOAD>(ffmask, fset));
    }

//001
    uint64_t getSourceRegs(const Opcode icode) const override
    {
        return (1ull << REGISTER_ANDES_GP); //implied global pointer
    }

//001.1
    uint64_t getSourceAddressRegs(const Opcode icode) const override
    {
        return getSourceRegs(icode);
    }

//002
    uint64_t getDestRegs(const Opcode icode) const override
    {
        return 1ull << extract_(Form_AndeStar_Custom_1_LOAD::idType::RD, icode & ~fixed_field_mask_);
    }

//003
    uint64_t getSourceOperTypeRegs(const Opcode icode,
                                   const InstMetaData::PtrType &meta, InstMetaData::OperandTypes kind) const override
    {
        if (meta->isNoneOperandType(kind)) {
            return 0;
        } else if (meta->isAllOperandType(kind)) {
            return getSourceRegs(icode);
        } else {
            uint64_t result = 0;
            //Using type of RS1 for the type of the implied GP aka X3
            if (meta->isOperandType(InstMetaData::OperandFieldID::RS1, kind)) {
                result |= (1ull << REGISTER_ANDES_GP);
            }
            return result;
        }
    }

//004
    uint64_t getDestOperTypeRegs(const Opcode icode,
                                 const InstMetaData::PtrType &meta, InstMetaData::OperandTypes kind) const override
    {
        if (meta->isNoneOperandType(kind)) {
            return 0;
        } else if (meta->isAllOperandType(kind)) {
            return getDestRegs(icode);
        } else {
            uint64_t result = 0;
            if (meta->isOperandType(InstMetaData::OperandFieldID::RD, kind)) {
                result |= extractUnmaskedIndexBit_(Form_AndeStar_Custom_1_LOAD::idType::RD, icode, fixed_field_mask_);
            }
            return result;
        }
    }

//005
    OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
                                     bool suppress_x0 = false) const override
    {
        OperandInfo olist;
        //ADDIGP has implied global pointer, typ. X3, this is the only source
        //using RS1 as the type index
        olist.addElement(InstMetaData::OperandFieldID::RS1, meta->getOperandType(InstMetaData::OperandFieldID::RS1),
                         REGISTER_ANDES_GP, false);
        return olist;
    }


//006
    OperandInfo getDestOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
                                   bool suppress_x0 = false) const override
    {
        OperandInfo olist;
        appendUnmaskedOperandInfo_(olist, icode, meta, InstMetaData::OperandFieldID::RD,
                                   fixed_field_mask_, Form_AndeStar_Custom_1_LOAD::idType::RD,
                                   false, suppress_x0);
        return olist;
    }

//007
    ImmediateType getImmediateType() const override
    {
        return ImmediateType::SIGNED;
    }

//008 
    uint64_t getImmediate(const Opcode icode) const override
    {
        // Mapping:
        // 18 10:2 17 11 14:12 16:15
        // 1   9   1  1  3     2     = 17
        //
        // The encoded immediate field is 17b wide, the result is 19b wide, do the shift now
        const uint64_t imm19 = extract_(Form_AndeStar_Custom_1_LOAD::idType::IMM17, icode & ~fixed_field_mask_) << 2;
        // src    16 15:7  6  5    4:2    1:0   as encoded
        // src    18 17:9  8  7    6:4    3:2   after shift 
        // dst    18 10:2  17 11  14:12  16:15   
        //                 111111111----------
        //                 8765432109876543210
        return ((imm19 & 0b1000000000000000000) >>  0)   //18    -> 18
             | ((imm19 & 0b0111111111000000000) >>  7)   //17:9  -> 10:2
             | ((imm19 & 0b0000000000100000000) <<  9)   //8     -> 17    
             | ((imm19 & 0b0000000000010000000) <<  4)   //7     -> 11
             | ((imm19 & 0b0000000000001110000) <<  8)   //6:4   -> 14:12
             | ((imm19 & 0b0000000000000001100) << 13);  //3:2   -> 16:15
    }

//009
    int64_t getSignedOffset(const Opcode icode) const override
    {
        return signExtend_(getImmediate(icode), 18);
    }

    using ExtractorIF::dasmString; // tell the compiler all dasmString
                                   // overloads are considered
//010
    std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
    {
        std::stringstream ss;
        ss << mnemonic
           << "\t" << extract_(Form_AndeStar_Custom_1_LOAD::idType::RD, icode & ~fixed_field_mask_)
           << ", [+" << std::hex << getSignedOffset(icode) <<"]";
        return ss.str();
    }

//011 
    std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta) const override
    {
        std::stringstream ss;
        ss << mnemonic << "\t"
           << dasmFormatRegList_(meta, icode, fixed_field_mask_,
                                 { { Form_AndeStar_Custom_1_LOAD::idType::RD, InstMetaData::OperandFieldID::RD } })
           << ", +0x" << std::hex << getSignedOffset(icode);
        return ss.str();
    }

private:
    Extractor<Form_AndeStar_Custom_1_LOAD>(const uint64_t ffmask, const uint64_t fset) :
        fixed_field_mask_(ffmask)
    {}

    uint64_t fixed_field_mask_ = 0;
};

// --------------------------------------------------------------------------- 
// Form_AndeStar_Custom_1_STORE - Form Extractor
//
//x 000 ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
//x 001 uint64_t getSourceRegs(const Opcode icode) const override
//001.1 uint64_t getSourceAddressRegs(const Opcode icode) const override
//001.2 uint64_t getSourceDataRegs(const Opcode icode) const override
//002 uint64_t getDestRegs(const Opcode icode) const override
//003 uint64_t getSourceOperTypeRegs(const Opcode icode,
//004 uint64_t getDestOperTypeRegs(const Opcode icode,
//005 OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
//006 OperandInfo getDestOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
//007 ImmediateType getImmediateType() const override
//008 uint64_t getImmediate(const Opcode icode) const override
//009 int64_t getSignedOffset(const Opcode icode) const override
//010 std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
//011 std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta)

// --------------------------------------------------------------------------- 

template<>
class Extractor<Form_AndeStar_Custom_1_STORE> : public ExtractorBase<Form_AndeStar_Custom_1_STORE>
{
public:
    Extractor() = default;
//000
    ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
    {
        return ExtractorIF::PtrType(new Extractor<Form_AndeStar_Custom_1_STORE>(ffmask, fset));
    }

//001
    uint64_t getSourceRegs(const Opcode icode) const override
    {
        return extractUnmaskedIndexBit_(Form_AndeStar_Custom_1_STORE::idType::RS2, icode, fixed_field_mask_)
             | (1ull << REGISTER_ANDES_GP); //implied global pointer
    }

//001.1
    uint64_t getSourceAddressRegs(const Opcode icode) const override
    {
        return (1ull << REGISTER_ANDES_GP); //implied global pointer
    }

//001.2
    uint64_t getSourceDataRegs(const Opcode icode) const override
    {
        return extractUnmaskedIndexBit_(Form_AndeStar_Custom_1_STORE::idType::RS2, icode, fixed_field_mask_);
    }

//002 - STORE no getDestRegs()

//003
    uint64_t getSourceOperTypeRegs(const Opcode icode,
                                   const InstMetaData::PtrType &meta, InstMetaData::OperandTypes kind) const override
    {
        if (meta->isNoneOperandType(kind)) {
            return 0;
        } else if (meta->isAllOperandType(kind)) {
            return getSourceRegs(icode);
        } else {
            //Use RS1 for GP type
            uint64_t result = 0;
            if (meta->isOperandType(InstMetaData::OperandFieldID::RS1, kind)) {
                result |= (1ull << REGISTER_ANDES_GP);
            }
            if (meta->isOperandType(InstMetaData::OperandFieldID::RS2, kind)) {
                result |= extractUnmaskedIndexBit_(Form_AndeStar_Custom_1_STORE::idType::RS2, icode, fixed_field_mask_);
            }
            return result;
        }
    }

//004 - STORE no getDestOperTypeRegs()

//005 
    OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
                                     bool suppress_x0 = false) const override
    {
        //Use RS1 type for the implied GP
        OperandInfo olist;
        olist.addElement(InstMetaData::OperandFieldID::RS1,
                                   meta->getOperandType(InstMetaData::OperandFieldID::RS1),
                                   REGISTER_ANDES_GP, false);
        appendUnmaskedOperandInfo_(olist, icode, meta, InstMetaData::OperandFieldID::RS2,
                                   fixed_field_mask_, Form_AndeStar_Custom_1_STORE::idType::RS2,
                                   true, suppress_x0);
        return olist;
    }

//006 - STORE no getDestOperandInfo()

//007
    ImmediateType getImmediateType() const override
    {
        return ImmediateType::SIGNED;
    }

//008
    uint64_t getImmediate(const Opcode icode) const override
    {
        // Count bits - from docs and form
        // 18 10:5 14:12 16:15 4:3 18:17 11
        // 1   6     3     2    2    2   1   = 17
        // -imm7--|--imm5a----|--imm5b----
        //
        // The encoded immediate field is 17b wide in three fields,
        // the final immediate is 20b
        //
        // Extract the 17b from the 3 fields, and lsh to form the 20b
        const uint64_t imm20 = 
                ((extract_(Form_AndeStar_Custom_1_STORE::idType::IMM7,  icode & ~fixed_field_mask_) << 10)
              |  (extract_(Form_AndeStar_Custom_1_STORE::idType::IMM5A, icode & ~fixed_field_mask_) <<  5)
              |  (extract_(Form_AndeStar_Custom_1_STORE::idType::IMM5B, icode & ~fixed_field_mask_) >>  0)) << 3;
        // 
        // src    19 18:13 12:10  9:8   7:6 5:4   3
        // dst    19 10:5  14:12  16:15 4:3 18:17 11
        //                 1111111111----------
        //                 98765432109876543210
        return ((imm20 & 0b10000000000000000000) >>  0)   //19    -> 19
             | ((imm20 & 0b01111110000000000000) >>  8)   //18:13 -> 10:5
             | ((imm20 & 0b00000001110000000000) <<  2)   //12:10 -> 14:12
             | ((imm20 & 0b00000000001100000000) <<  7)   //9:8   -> 16:15
             | ((imm20 & 0b00000000000011000000) <<  6)   //7:6   -> 14:12
             | ((imm20 & 0b00000000000000110000) << 13)   //5:4   -> 18:17
             | ((imm20 & 0b00000000000000001000) <<  8);  //3     -> 11
    }

//009
    int64_t getSignedOffset(const Opcode icode) const override
    {
        return signExtend_(getImmediate(icode), 18);
    }

    using ExtractorIF::dasmString; // tell the compiler all dasmString
                                   // overloads are considered
//010
    std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
    {
        std::stringstream ss;
        ss << mnemonic
           << "\t" << extract_(Form_AndeStar_Custom_1_STORE::idType::RS2, icode)
           << ", [+" << std::dec << getImmediate(icode) << "]";
        return ss.str();
    }

//011
    std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta) const override
    {
        std::stringstream ss;
        ss << mnemonic << "\t"
           << dasmFormatRegList_(meta, icode, fixed_field_mask_,
                                 { { Form_AndeStar_Custom_1_STORE::idType::RS2, InstMetaData::OperandFieldID::RS2 } })
           << ", +0x" << std::dec << getImmediate(icode);
        return ss.str();
    }

private:
    Extractor<Form_AndeStar_Custom_1_STORE>(const uint64_t ffmask, const uint64_t fset) :
        fixed_field_mask_(ffmask)
    {}

    uint64_t fixed_field_mask_ = 0;


};

// ---------------------------------------------------------------------------
// AndeStar_Custom_2 (DECODE ONLY) form
// ---------------------------------------------------------------------------
template<>
class Extractor<Form_AndeStar_Custom_2> : public ExtractorBase<Form_AndeStar_Custom_2>
{
public:
    Extractor() = default;

    ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
    {
        return ExtractorIF::PtrType(new Extractor<Form_AndeStar_Custom_2>(ffmask, fset));
    }

    using ExtractorIF::dasmString; // tell the compiler all dasmString
    // overloads are considered

    std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
    {
        return mnemonic;
    }

private:
    Extractor<Form_AndeStar_Custom_2>(const uint64_t ffmask, const uint64_t fset) :
            fixed_field_mask_(ffmask)
    {}

    uint64_t fixed_field_mask_ = 0;
};

// ---------------------------------------------------------------------------
// AndeStar_Custom_2_BBx (EXTRACTION ONLY) "xform"
//
//      For BBC and BBS
// ---------------------------------------------------------------------------
template<>
class Extractor<Form_AndeStar_Custom_2_BBx> : public ExtractorBase<Form_AndeStar_Custom_2_BBx>
{
public:
    Extractor() = default;

    ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
    {
        return ExtractorIF::PtrType(new Extractor<Form_AndeStar_Custom_2_BBx>(ffmask, fset));
    }

    uint64_t getSourceRegs(const Opcode icode) const override
    {
        return extractUnmaskedIndexBit_(Form_AndeStar_Custom_2_BBx::idType::RS1, icode, fixed_field_mask_);
    }

    uint64_t getSourceOperTypeRegs(const Opcode icode,
                                   const InstMetaData::PtrType &meta,
                                   InstMetaData::OperandTypes kind) const override
    {
        if (meta->isNoneOperandType(kind)) {
            return 0;
        } else if (meta->isAllOperandType(kind)) {
            return getSourceRegs(icode);
        } else {
            uint64_t result = 0;
            if (meta->isOperandType(InstMetaData::OperandFieldID::RS1, kind)) {
                result |= extractUnmaskedIndexBit_(Form_AndeStar_Custom_2_BBx::idType::RS1, icode, fixed_field_mask_);
            }
            return result;
        }
    }

    OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
                                     bool suppress_x0 = false) const override
    {
        OperandInfo olist;
        appendUnmaskedOperandInfo_(olist, icode, meta, InstMetaData::OperandFieldID::RS1,
                                   fixed_field_mask_, Form_AndeStar_Custom_2_BBx::idType::RS1,
                                   false, suppress_x0);
        return olist;
    }

    ImmediateType getImmediateType() const override
    {
        return ImmediateType::SIGNED;
    }

    uint64_t getImmediate(const Opcode icode) const override
    {
        return (extract_(Form_AndeStar_Custom_2_BBx::idType::IMM10, icode) << 9ull) |
               (extract_(Form_AndeStar_Custom_2_BBx::idType::IMM9_5, icode) << 4ull) |
                extract_(Form_AndeStar_Custom_2_BBx::idType::IMM4_1, icode);
    }

    uint64_t getCIMM(const Opcode icode) const
    {
        return (extract_(Form_AndeStar_Custom_2_BBx::idType::CIMM5, icode) << 5ull) |
                extract_(Form_AndeStar_Custom_2_BBx::idType::CIMM4_0, icode);
    }

    uint64_t getSpecialField(SpecialField sfid, Opcode icode) const override
    {
        switch(sfid) {
            case SpecialField::CIMM:
                return getCIMM(icode);
            default:
                return ExtractorBase::getSpecialField(sfid, icode);
        }
    }

    int64_t getSignedOffset(const Opcode icode) const override
    {
        return signExtend_(getImmediate(icode), 9);
    }

    using ExtractorIF::dasmString; // tell the compiler all dasmString
    // overloads are considered
    std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
    {
        std::stringstream ss;
        ss << mnemonic
           << "\t" << extract_(Form_AndeStar_Custom_2_BBx::idType::RS1, icode & ~fixed_field_mask_)
           << ", 0x" << std::hex << getCIMM(icode)
           << ", 0x" << std::hex << getSignedOffset(icode);
        return ss.str();
    }

    std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta) const override
    {
        std::stringstream ss;
        ss << mnemonic << "\t"
           << dasmFormatRegList_(meta, icode, fixed_field_mask_,
                                 { { Form_AndeStar_Custom_2_BBx::idType::RS1, InstMetaData::OperandFieldID::RS1 } })
           << ", 0x" << std::hex << getCIMM(icode)
           << ", 0x" << std::hex << getSignedOffset(icode);
        return ss.str();
    }

private:
    Extractor<Form_AndeStar_Custom_2_BBx>(const uint64_t ffmask, const uint64_t fset) :
            fixed_field_mask_(ffmask)
    {}

    uint64_t fixed_field_mask_ = 0;
};

// ---------------------------------------------------------------------------
// AndeStar_Custom_2_BxxC (EXTRACTION ONLY) "xform"
//
//      For BEQC and BNEC
// ---------------------------------------------------------------------------
template<>
class Extractor<Form_AndeStar_Custom_2_BxxC> : public ExtractorBase<Form_AndeStar_Custom_2_BxxC>
{
public:
    Extractor() = default;

    ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
    {
        return ExtractorIF::PtrType(new Extractor<Form_AndeStar_Custom_2_BxxC>(ffmask, fset));
    }

    uint64_t getSourceRegs(const Opcode icode) const override
    {
        return extractUnmaskedIndexBit_(Form_AndeStar_Custom_2_BxxC::idType::RS1, icode, fixed_field_mask_);
    }

    uint64_t getSourceOperTypeRegs(const Opcode icode,
                                   const InstMetaData::PtrType &meta,
                                   InstMetaData::OperandTypes kind) const override
    {
        if (meta->isNoneOperandType(kind)) {
            return 0;
        } else if (meta->isAllOperandType(kind)) {
            return getSourceRegs(icode);
        } else {
            uint64_t result = 0;
            if (meta->isOperandType(InstMetaData::OperandFieldID::RS1, kind)) {
                result |= extractUnmaskedIndexBit_(Form_AndeStar_Custom_2_BxxC::idType::RS1, icode, fixed_field_mask_);
            }
            return result;
        }
    }

    OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
                                     bool suppress_x0 = false) const override
    {
        OperandInfo olist;
        appendUnmaskedOperandInfo_(olist, icode, meta, InstMetaData::OperandFieldID::RS1,
                                   fixed_field_mask_, Form_AndeStar_Custom_2_BxxC::idType::RS1,
                                   false, suppress_x0);
        return olist;
    }

    ImmediateType getImmediateType() const override
    {
        return ImmediateType::SIGNED;
    }

    uint64_t getImmediate(const Opcode icode) const override
    {
        return (extract_(Form_AndeStar_Custom_2_BxxC::idType::IMM10, icode) << 9ull) |
               (extract_(Form_AndeStar_Custom_2_BxxC::idType::IMM9_5, icode) << 4ull) |
               extract_(Form_AndeStar_Custom_2_BxxC::idType::IMM4_1, icode);
    }

    uint64_t getCIMM(const Opcode icode) const
    {
        return (extract_(Form_AndeStar_Custom_2_BxxC::idType::CIMM6, icode) << 6ull) |
               (extract_(Form_AndeStar_Custom_2_BxxC::idType::CIMM5, icode) << 5ull) |
                extract_(Form_AndeStar_Custom_2_BxxC::idType::CIMM4_0, icode);
    }

    uint64_t getSpecialField(SpecialField sfid, Opcode icode) const override
    {
        switch(sfid) {
            case SpecialField::CIMM:
                return getCIMM(icode);
            default:
                return ExtractorBase::getSpecialField(sfid, icode);
        }
    }

    int64_t getSignedOffset(const Opcode icode) const override
    {
        return signExtend_(getImmediate(icode), 9);
    }

    using ExtractorIF::dasmString; // tell the compiler all dasmString
    // overloads are considered
    std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
    {
        std::stringstream ss;
        ss << mnemonic
           << "\t" << extract_(Form_AndeStar_Custom_2_BxxC::idType::RS1, icode & ~fixed_field_mask_)
           << ", 0x" << std::hex << getCIMM(icode)
           << ", 0x" << std::hex << getSignedOffset(icode);
        return ss.str();
    }

    std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta) const override
    {
        std::stringstream ss;
        ss << mnemonic << "\t"
           << dasmFormatRegList_(meta, icode, fixed_field_mask_,
                                 { { Form_AndeStar_Custom_2_BxxC::idType::RS1, InstMetaData::OperandFieldID::RS1 } })
           << ", 0x" << std::hex << getCIMM(icode)
           << ", 0x" << std::hex << getSignedOffset(icode);
        return ss.str();
    }

private:
    Extractor<Form_AndeStar_Custom_2_BxxC>(const uint64_t ffmask, const uint64_t fset) :
            fixed_field_mask_(ffmask)
    {}

    uint64_t fixed_field_mask_ = 0;
};
}
