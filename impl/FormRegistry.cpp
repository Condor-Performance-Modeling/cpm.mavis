
#include "mavis/FormRegistry.h"
#include "impl/forms/CommonForms.h"
#include "impl/forms/CompressedForms.h"
#include "impl/forms/VectorForms.h"
#include "impl/forms/AndeStarForms.h"
#include <iostream>

namespace mavis
{

    static const std::map<std::string, const FormBase*> form_registry_ = {
        {Form_AMO::name,        new Form<Form_AMO>()       },
        {Form_B::name,          new Form<Form_B>()         },
        {Form_C0::name,         new Form<Form_C0>()        },
        {Form_C1::name,         new Form<Form_C1>()        },
        {Form_C2::name,         new Form<Form_C2>()        },
        {Form_CA::name,         new Form<Form_CA>()        },
        {Form_CB::name,         new Form<Form_CB>()        },
        {Form_CI::name,         new Form<Form_CI>()        },
        {Form_CI_rD_only::name, new Form<Form_CI_rD_only>()},
        {Form_CIW::name,        new Form<Form_CIW>()       },
        {Form_CIX::name,        new Form<Form_CIX>()       },
        {Form_CJ::name,         new Form<Form_CJ>()        },
        {Form_CJR::name,        new Form<Form_CJR>()       },
        {Form_CMPP::name,       new Form<Form_CMPP>()      },
        {Form_CMJT::name,       new Form<Form_CMJT>()      },
        {Form_CSR::name,        new Form<Form_CSR>()       },
        {Form_CSRI::name,       new Form<Form_CSRI>()      },
        {Form_FENCE::name,      new Form<Form_FENCE>()     },
        {Form_I::name,          new Form<Form_I>()         },
        {Form_ISH::name,        new Form<Form_ISH>()       },
        {Form_ISHW::name,       new Form<Form_ISHW>()      },
        {Form_J::name,          new Form<Form_J>()         },
        {Form_R::name,          new Form<Form_R>()         },
        {Form_Rfloat::name,     new Form<Form_Rfloat>()    },
        {Form_R4::name,         new Form<Form_R4>()        },
        {Form_S::name,          new Form<Form_S>()         },
        {Form_U::name,          new Form<Form_U>()         },
        {Form_V::name,          new Form<Form_V>()         },
        {Form_VF_mem::name,     new Form<Form_VF_mem>()    },
        {Form_V_vsetvl::name,   new Form<Form_V_vsetvl>()  },
        {Form_V_vsetvli::name,  new Form<Form_V_vsetvli>() },
        {Form_V_vsetivli::name, new Form<Form_V_vsetivli>()},
        {Form_V_uimm6::name,    new Form<Form_V_uimm6>()   },
        {Form_AndeStar_Custom_0::name,       new Form<Form_AndeStar_Custom_0>()},
        {Form_AndeStar_Custom_0_LBYTE::name, new Form<Form_AndeStar_Custom_0_LBYTE>()},
        {Form_AndeStar_Custom_0_SBYTE::name, new Form<Form_AndeStar_Custom_0_SBYTE>()},
        {Form_AndeStar_Custom_1::name,       new Form<Form_AndeStar_Custom_1>()},
        {Form_AndeStar_Custom_1_LOAD::name,  new Form<Form_AndeStar_Custom_1_LOAD>()},
        {Form_AndeStar_Custom_1_LHALFGP::name,  new Form<Form_AndeStar_Custom_1_LHALFGP>()},
        {Form_AndeStar_Custom_1_LWORDGP::name,  new Form<Form_AndeStar_Custom_1_LWORDGP>()},
        {Form_AndeStar_Custom_1_LDOUBLEGP::name,  new Form<Form_AndeStar_Custom_1_LDOUBLEGP>()},
        {Form_AndeStar_Custom_1_STORE::name, new Form<Form_AndeStar_Custom_1_STORE>()},
        {Form_AndeStar_Custom_1_SHALFGP::name, new Form<Form_AndeStar_Custom_1_SHALFGP>()},
        {Form_AndeStar_Custom_1_SWORDGP::name, new Form<Form_AndeStar_Custom_1_SWORDGP>()},
        {Form_AndeStar_Custom_1_SDOUBLEGP::name, new Form<Form_AndeStar_Custom_1_SDOUBLEGP>()},
        {Form_AndeStar_Custom_2::name,       new Form<Form_AndeStar_Custom_2>()},
        {Form_AndeStar_Custom_2_BBx::name,   new Form<Form_AndeStar_Custom_2_BBx>()},
        {Form_AndeStar_Custom_2_BxxC::name,  new Form<Form_AndeStar_Custom_2_BxxC>()},
        {Form_AndeStar_Custom_2_BFOx::name,  new Form<Form_AndeStar_Custom_2_BFOx>()},
        {Form_AndeStar_Custom_2_XDEF::name,  new Form<Form_AndeStar_Custom_2_XDEF>()},
    };

    const FormBase* FormRegistry::findFormWrapper(const std::string & fname)
    {
        const auto itr = form_registry_.find(fname);
        if (itr != form_registry_.end())
        {
            return itr->second;
        }
        else
        {
            return nullptr;
        }
    }

    const FormBase* FormRegistry::getFormWrapper(const std::string & fname)
    {
        const auto itr = form_registry_.find(fname);
        if (itr == form_registry_.end())
        {
            throw BuildErrorUnknownForm(fname);
        }
        return itr->second;
    }

} // namespace mavis
