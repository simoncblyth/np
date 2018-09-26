// clang NPUTest.cc -lc++ -o /tmp/NPUTest && /tmp/NPUTest
// gcc NPUTest.cc -lstdc++ -o /tmp/NPUTest && /tmp/NPUTest

#include <vector>
#include <string>
#include <fstream>
#include "NPU.hh"

int main(int argc, char** argv)
{
    std::vector<float> v ;
    for( int i=0 ; i < 10 ; i++ ) v.push_back(float(i)) ;


    std::vector<int> shape ;
    shape.push_back(v.size()) ; 

    std::string hdr = NPU::make_header<float>( shape ) ; 

    std::cout << hdr << std::endl ; 

  
    const char* path = "/tmp/a.npy" ; 

    std::ofstream stream(path, std::ios::out|std::ios::binary);
    stream << hdr ; 

    int size = 1;
    for(int i=0; i<shape.size(); ++i) size *= shape[i] ;

    stream.write(reinterpret_cast<const char*>(v.data()), sizeof(float)*size);

    std::cout << " writing " << path << std::endl ; 


    /**
    np.save("/tmp/b.npy", np.linspace(0,9,10, dtype=np.float32) )

    **/


    return 0 ; 
}
