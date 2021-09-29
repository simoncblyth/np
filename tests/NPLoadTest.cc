// gcc NPLoadTest.cc -std=c++11 -DNPU_DEBUG -I.. -lstdc++ -o /tmp/NPLoadTest && /tmp/NPLoadTest

#include <cstdlib>
#include "NP.hh"



int main(int argc, char** argv)
{
    const char* npath = getenv("NPATH"); 
    const char* path = argc > 1 ? argv[1] : (npath ? npath :  "/tmp/b.npy" ) ;  

    bool readable = NPU::is_readable(path) ; 
    if(!readable) 
    {
        std::cout << " non-readable path " << path << std::endl ; 
        return 0 ; 
    }


    NP* b = NP::Load(path) ; 
    b->dump(); 

    std::cout << " b->lpath " << b->lpath << std::endl ; 
    std::cout << " b->lfold " << b->lfold << std::endl ; 


    return 0 ; 
}

/**

epsilon:tests blyth$ NPATH=/tmp/blyth/opticks/CSG_GGeo/CSGFoundry/bnd.npy /tmp/NPLoadTest
Assertion failed: (hlen+10 == hdr.size()), function _parse_header_length, file ../NPU.hh, line 458.
Abort trap: 6


epsilon:tests blyth$ xxd /tmp/blyth/opticks/CSG_GGeo/CSGFoundry/bnd.npy  | head -10
00000000: 934e 554d 5059 0100 8600 7b27 6465 7363  .NUMPY....{'desc
00000010: 7227 3a20 273c 6638 272c 2027 666f 7274  r': '<f8', 'fort
00000020: 7261 6e5f 6f72 6465 7227 3a20 4661 6c73  ran_order': Fals
00000030: 652c 2027 7368 6170 6527 3a20 2833 362c  e, 'shape': (36,
00000040: 2034 2c20 322c 2037 3631 2c20 3429 2c20   4, 2, 761, 4), 
00000050: 7d20 2020 2020 2020 2020 2020 2020 2020  }               
00000060: 2020 2020 2020 2020 2020 2020 2020 2020                  
00000070: 2020 2020 2020 2020 2020 2020 2020 2020                  
00000080: 2020 2020 2020 2020 2020 2020 2020 200a                 .
00000090: 0000 0000 0000 f03f 0000 0000 8084 2e41  .......?.......A
epsilon:tests blyth$ 


epsilon:tests blyth$ NPATH=/tmp/blyth/opticks/CSG_GGeo/CSGFoundry/bnd.npy /tmp/NPLoadTest
 dlen 55 padding 62 hlen 118
 dlen 118
 len.c[0] v
 len.c[1] 
little_endian
 _parse_header_length  
 hdr               
.NUMPY....{'desc
r': '<f8', 'fort
ran_order': Fals
e, 'shape': (36,
 4, 2, 761, 4), 
}               
                
                
               .

 preamble          ?NUMPY
 hlen_lsb(hex)     ffffff86
 hlen_msb(hex)     0
 hlen(hex)         ffffff86
 hlen_lsb(dec)     -122
 hlen_msb(dec)     0
 hlen(dec)         -122
 hlen+10(dec)      -112
 (hlen+10)%16(dec) 0
 hdr.size() (dec)  144
 preamble.size()   8

Assertion failed: (hlen+10 == hdr.size()), function _parse_header_length, file ../NPU.hh, line 478.
Abort trap: 6
epsilon:tests blyth$ 






epsilon:tests blyth$ xxd /tmp/blyth/opticks/CSG_GGeo/CSGFoundry/icdf.npy  | head -10
00000000: 934e 554d 5059 0100 7600 7b27 6465 7363  .NUMPY..v.{'desc
00000010: 7227 3a20 273c 6638 272c 2027 666f 7274  r': '<f8', 'fort
00000020: 7261 6e5f 6f72 6465 7227 3a20 4661 6c73  ran_order': Fals
00000030: 652c 2027 7368 6170 6527 3a20 2833 2c20  e, 'shape': (3, 
00000040: 3430 3936 2c20 3129 2c20 7d20 2020 2020  4096, 1), }     
00000050: 2020 2020 2020 2020 2020 2020 2020 2020                  
00000060: 2020 2020 2020 2020 2020 2020 2020 2020                  
00000070: 2020 2020 2020 2020 2020 2020 2020 200a                 .
00000080: 764f 4f12 2fff 8840 0502 ef3a 2e8f 8840  vOO./..@...:...@
00000090: eaae 91d4 0723 8840 47f9 d4d3 89ba 8740  .....#.@G......@
epsilon:tests blyth$ 


epsilon:tests blyth$ NPATH=/tmp/blyth/opticks/CSG_GGeo/CSGFoundry/icdf.npy /tmp/NPLoadTest
 dlen 55 padding 62 hlen 118
 dlen 118
 len.c[0] v
 len.c[1] 
little_endian
 _parse_header_length  
 hdr               
.NUMPY..v.{'desc
r': '<f8', 'fort
ran_order': Fals
e, 'shape': (3, 
4096, 1), }     
                
                
               .

 preamble          ?NUMPY
 hlen_lsb(hex)     76
 hlen_msb(hex)     0
 hlen(hex)         76
 hlen_lsb(dec)     118
 hlen_msb(dec)     0
 hlen(dec)         118
 hlen+10(dec)      128
 (hlen+10)%16(dec) 0
 hdr.size() (dec)  128
 preamble.size()   8

[3] -> 3
[4096] -> 4096
[1] -> 1
 parse_tuple  sh  [3, 4096, 1] shape 3
 parse_header  
 hdr               
.NUMPY..v.{'desc
r': '<f8', 'fort
ran_order': Fals
e, 'shape': (3, 
4096, 1), }     
                
                
               .

 hlen(hex)         76
 hlen(dec)         118
 hlen+10(dec)      128
 (hlen+10)%16(dec) 0
 dict [{'descr': '<f8', 'fortran_order': False, 'shape': (3, 4096, 1), }                                                    .]
 p0( 51
 p1) 61
 shape 3, 4096, 1
 last(dec)         10
 newline(dec)      10
 hdr.size() (dec)  128
 dict.size() (dec) 118
 descr <f8 uifc f ebyte 8
NP  dtype <f8(3, 4096, 1, ) size 12288 uifc f ebyte 8 shape.size 3 data.size 98304 meta.size 0



**/

