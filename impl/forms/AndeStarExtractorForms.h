#pragma once
//TODO: what does it mean that ADDIW has w-oper=all and l-oper=all
//
// w-oper   word    32b or XLEN ? TODO: same Q: about assumed width
// l-oper   long    TODO: what does mavis assume for long? Is it XLEN dependent?
// s-oper   single  TODO: what is a single operand? Is it a flag to indicate there's just one? If so why is this needed?
// d-oper   float double  I assume
// q-oper   float quad  I assume
// v-oper   vector TODO: are there vector word/long etc assumptions needed in the encoding/meta data?
//
//TODO find out how fixed_field_mask_ is specified and why this isn't just a mask over RD bit range.
//
//TODO: confirm: fixed indicates register fields that are static, encoded as zeros, such as rd, rs1, rs2 in ecall
//TODO: is there a case where a named field is fixed but also not zero,
//
// TODO: the form defines this, what use does this function have, why doesn't it have an argument that specified
//       which immediate field? 
//
//    ImmediateType getImmediateType() const override
//    {
//        return ImmediateType::SIGNED;
//    }
//TODO:   is there any case where there are more than one immediate fields and one is unsigned/signed, 

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
        return ((1ull << REGISTER_ANDES_GP)); //X3 is implied source 
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
//THIS CODE NEEDS DETAILED TESTING -- See the form Form_C2_sp_store (yes store, it was easier to reference) C1 CI_sp
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

//// --------------------------------------------------------------------------- 
//// Form_AndeStar_Custom_1_LOAD - Form Extractor
////
////000 ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
////001 uint64_t getSourceRegs(const Opcode icode) const override
////001.1 uint64_t getSourceAddressRegs(const Opcode icode) const override
////002 uint64_t getDestRegs(const Opcode icode) const override
////003 uint64_t getSourceOperTypeRegs(const Opcode icode,
////004 uint64_t getDestOperTypeRegs(const Opcode icode,
////005 OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
////006 OperandInfo getDestOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
////007 ImmediateType getImmediateType() const override
////008 uint64_t getImmediate(const Opcode icode) const override
////009 int64_t getSignedOffset(const Opcode icode) const override
////010 std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
////011 std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta)
//
//// --------------------------------------------------------------------------- 
//template<>
//class Extractor<Form_AndeStar_Custom_1_LOAD> : public ExtractorBase<Form_AndeStar_Custom_1_LOAD>
//{
//public:
//    Extractor() = default;
////000
//    ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
//    {
//        return ExtractorIF::PtrType(new Extractor<Form_AndeStar_Custom_1_LOAD>(ffmask, fset));
//    }
//
////001
//    uint64_t getSourceRegs(const Opcode icode) const override
//    {
//        return extractUnmaskedIndexBit_((1ull << REGISTER_X3)); //X3 is implied source 
//    }
//
////001.1
//    uint64_t getSourceAddressRegs(const Opcode icode) const override
//    {
//        return extractUnmaskedIndexBit_((1ull << REGISTER_X3)); //X2 is implied base addr register
//    }
//
////002
//    uint64_t getDestRegs(const Opcode icode) const override
//    {
//        return 1ull << extract_(Form_AndeStar_Custom_1_LOAD::idType::RD, icode & ~fixed_field_mask_);
//    }
//
////003
//    uint64_t getSourceOperTypeRegs(const Opcode icode,
//                                   const InstMetaData::PtrType &meta, InstMetaData::OperandTypes kind) const override
//    {
//        if (meta->isNoneOperandType(kind)) {
//            return 0;
//        } else if (meta->isAllOperandType(kind)) {
//            return getSourceRegs(icode) |
//        } else {
////THIS CODE IS WRONG
//cout<<"HERE unimplemented 003"<<endl;
//            assert(1==0);
//            //uint64_t result = 0;
////            if (meta->isOperandType(InstMetaData::OperandFieldID::RS1, kind)) { //HERE
////                result |= extractUnmaskedIndexBit_(Form_AndeStar_Custom_0::idType::RS1, icode, fixed_field_mask_); //HERE
////            }
//            return result;
//        }
//    }
//
////004
//    uint64_t getDestOperTypeRegs(const Opcode icode,
//                                 const InstMetaData::PtrType &meta, InstMetaData::OperandTypes kind) const override
//    {
//        if (meta->isNoneOperandType(kind)) {
//            return 0;
//        } else if (meta->isAllOperandType(kind)) {
//            return getDestRegs(icode);
//        } else {
//            uint64_t result = 0;
//            if (meta->isOperandType(InstMetaData::OperandFieldID::RD, kind)) {
//                result |= extractUnmaskedIndexBit_(Form_AndeStar_Custom_1_LOAD::idType::RD, icode, fixed_field_mask_);
//            }
//            return result;
//        }
//    }
//
////005
//    OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
//                                     bool suppress_x0 = false) const override
//    {
//        OperandInfo olist;
////THIS CODE IS WRONG
//cout<<"HERE unimplemented 005"<<endl;
//            assert(1==0);
////        appendUnmaskedOperandInfo_(olist, icode, meta, InstMetaData::OperandFieldID::RS1, //THIS CODE IS WRONG implied X3
////                                   fixed_field_mask_, Form_AndeStar_Custom_0::idType::RS1,
////                                   false, suppress_x0);
//        return olist;
//    }
//
//
////006
//    OperandInfo getDestOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
//                                   bool suppress_x0 = false) const override
//    {
//        OperandInfo olist;
//        appendUnmaskedOperandInfo_(olist, icode, meta, InstMetaData::OperandFieldID::RD,
//                                   fixed_field_mask_, Form_AndeStar_Custom_1_LOAD::idType::RD,
//                                   false, suppress_x0);
//        return olist;
//    }
//
////007
//    ImmediateType getImmediateType() const override
//    {
//        return ImmediateType::SIGNED;
//    }
//
////008
//    uint64_t getImmediate(const Opcode icode) const override
//    {
//        // Mapping:
//        // 18 10:2 17 11 14:12 16:15
//        // 1   9   1  1  3     2     = 17
//        //
//        // The encoded immediate field is 17b wide, the result is 19b wide, do the shift now
//        const uint64_t imm19 = extract_(Form_AndeStar_Custom_1_LOAD::idType::IMM17, icode & ~fixed_field_mask_) << 2;
//        // src    16 15:7  6  5    4:2    1:0   as encoded
//        // src    18 17:9  8  7    6:4    3:2   after shift 
//        // dst    18 10:2  17 11  14:12  16:15   
//        //                 111111111----------
//        //                 8765432109876543210
//        return ((imm17 & 0b1000000000000000000) >>  0)   //18    -> 18
//             | ((imm18 & 0b0111111111000000000) >>  7)   //17:9  -> 10:2
//             | ((imm18 & 0b0000000000100000000) <<  9)   //8     -> 17    
//             | ((imm18 & 0b0000000000010000000) <<  4)   //7     -> 11
//             | ((imm18 & 0b0000000000001110000) <<  8)   //6:4   -> 14:12
//             | ((imm18 & 0b0000000000000001100) << 13);  //3:2   -> 16:15
//
//    }
//
////009
//    int64_t getSignedOffset(const Opcode icode) const override
//    {
//        return signExtend_(getImmediate(icode), 18);
//    }
//
//    using ExtractorIF::dasmString; // tell the compiler all dasmString
//                                   // overloads are considered
////010
//    std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
//    {
//        std::stringstream ss;
//        ss << mnemonic
//           << "\t" << extract_(Form_AndeStar_Custom_1_LOAD::idType::RD, icode & ~fixed_field_mask_)
//           << ", +0x" << std::hex << getSignedOffset(icode);
//        return ss.str();
//    }
//
////011
//    std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta) const override
//    {
//        std::stringstream ss;
//        ss << mnemonic << "\t"
//           << dasmFormatRegList_(meta, icode, fixed_field_mask_,
//                                 { { Form_AndeStar_Custom_1_LOAD::idType::RD, InstMetaData::OperandFieldID::RD } })
//           << ", +0x" << std::hex << getSignedOffset(icode);
//        return ss.str();
//    }
//
//private:
//    Extractor<Form_AndeStar_Custom_1_LOAD>(const uint64_t ffmask, const uint64_t fset) :
//        fixed_field_mask_(ffmask)
//    {}
//
//    uint64_t fixed_field_mask_ = 0;
//};
//
//// --------------------------------------------------------------------------- 
//// Form_AndeStar_Custom_1_STORE - Form Extractor
////
////000 ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
////001 uint64_t getSourceRegs(const Opcode icode) const override
////001.1 uint64_t getSourceAddressRegs(const Opcode icode) const override
////001.2 uint64_t getSourceDataRegs(const Opcode icode) const override
////002 uint64_t getDestRegs(const Opcode icode) const override
////003 uint64_t getSourceOperTypeRegs(const Opcode icode,
////004 uint64_t getDestOperTypeRegs(const Opcode icode,
////005 OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
////006 OperandInfo getDestOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
////007 ImmediateType getImmediateType() const override
////008 uint64_t getImmediate(const Opcode icode) const override
////009 int64_t getSignedOffset(const Opcode icode) const override
////010 std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
////011 std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta)
//
//// --------------------------------------------------------------------------- 
//
//template<>
//class Extractor<Form_AndeStar_Custom_1_STORE> : public ExtractorBase<Form_AndeStar_Custom_1_STORE>
//{
//public:
//    Extractor() = default;
////000
//    ExtractorIF::PtrType specialCaseClone(const uint64_t ffmask, const uint64_t fset) const override
//    {
//        return ExtractorIF::PtrType(new Extractor<Form_AndeStar_Custom_1_STORE>(ffmask, fset));
//    }
//
////001
//    uint64_t getSourceRegs(const Opcode icode) const override
//
////001.1
//    uint64_t getSourceAddressRegs(const Opcode icode) const override
//    {
//        return extractUnmaskedIndexBit_((1ull << REGISTER_X3)); //X2 is implied base addr register
//    }
//
////002 - STORE no getDestRegs()
//
////003
//    uint64_t getSourceOperTypeRegs(const Opcode icode,
//                                   const InstMetaData::PtrType &meta, InstMetaData::OperandTypes kind) const override
//    {
//        if (meta->isNoneOperandType(kind)) {
//            return 0;
//        } else if (meta->isAllOperandType(kind)) {
//            return getSourceRegs(icode) |
//        } else {
////THIS CODE IS WRONG
//cout<<"HERE unimplemented 003"<<endl;
//            assert(1==0);
//            //uint64_t result = 0;
////            if (meta->isOperandType(InstMetaData::OperandFieldID::RS1, kind)) { //HERE
////                result |= extractUnmaskedIndexBit_(Form_AndeStar_Custom_0::idType::RS1, icode, fixed_field_mask_); //HERE
////            }
//            return result;
//        }
//    }
//
////004 - STORE no getDestOperTypeRegs()
//
////005
//    OperandInfo getSourceOperandInfo(Opcode icode, const InstMetaData::PtrType& meta,
//                                     bool suppress_x0 = false) const override
//    {
//        OperandInfo olist;
////THIS CODE IS WRONG
//cout<<"HERE unimplemented 005"<<endl;
//            assert(1==0);
////        appendUnmaskedOperandInfo_(olist, icode, meta, InstMetaData::OperandFieldID::RS1, //THIS CODE IS WRONG implied X3
////                                   fixed_field_mask_, Form_AndeStar_Custom_0::idType::RS1,
////                                   false, suppress_x0);
//        return olist;
//    }
//
////006 - STORE no getDestOperandInfo()
//
////007
//    ImmediateType getImmediateType() const override
//    {
//        return ImmediateType::SIGNED;
//    }
//
////008
//    uint64_t getImmediate(const Opcode icode) const override
//    {
////WRONG
//    }
//
////009
//    int64_t getSignedOffset(const Opcode icode) const override
//    {
//        return signExtend_(getImmediate(icode), 18);
//    }
//
//    using ExtractorIF::dasmString; // tell the compiler all dasmString
//                                   // overloads are considered
////010
//    std::string dasmString(const std::string &mnemonic, const Opcode icode) const override
//    {
////WRONG
//    }
//
////011
//    std::string dasmString(const std::string &mnemonic, const Opcode icode, const InstMetaData::PtrType& meta) const override
//    {
////WRONG
//    }
//
//private:
//    Extractor<Form_AndeStar_Custom_1_STORE>(const uint64_t ffmask, const uint64_t fset) :
//        fixed_field_mask_(ffmask)
//    {}
//
//    uint64_t fixed_field_mask_ = 0;
//
//
//}
//0x8645128b addigp  0xee87930b
//0x8305128b 

}
