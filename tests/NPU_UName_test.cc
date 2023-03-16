// name=NPU_UName_test ; gcc $name.cc -std=c++11 -lstdc++ -I.. -o /tmp/$name && /tmp/$name

#include "NPU.hh"

int main()
{
    UName un ; 

    un.add("Water/Pyrex:Water_lv_pv/AroundCircle1"); 
    un.add("Pyrex/Pyrex:AroundCircle1/nnvt_body_phys");
    un.add("Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys");
    un.add("Vacuum/Pyrex:nnvt_inner2_phys/nnvt_body_phys");
    un.add("Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys");
    un.add("Vacuum/Steel:nnvt_inner2_phys/nnvt_tube_phy");
    un.add("Vacuum/Steel:nnvt_inner2_phys/nnvt_edge_phy");
    un.add("Vacuum/Steel:nnvt_inner2_phys/nnvt_plate_phy");
    un.add("Vacuum/Steel:nnvt_inner2_phys/nnvt_mcp_phy");
    un.add("Water/Rock:Water_lv_pv/Rock_lv_pv"); 

    const char* spec = "Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner1_phys" ; 
    int idx = un.add(spec); 

    std::cout << " idx " << idx << std::endl ; 

    std::cout << un.desc() ; 

    std::string str = un.as_str(); 

    std::cout << "[" << str << "]" << std::endl ; 

    return 0 ; 
}

