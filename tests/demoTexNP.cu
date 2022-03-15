/**
demoTexNP 
==========

Adapted from the below adding use of NP.hh rather than thrust 

* ~/intro_to_cuda/textures/demoTex.cu 
* https://bitbucket.org/simoncblyth/intro_to_cuda/src/master/textures/demoTex.cu

CUDA Docs
--------------

* http://on-demand.gputechconf.com/gtc-express/2011/presentations/texture_webinar_aug_2011.pdf
* https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#texture-fetching
* https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#table-lookup


Textures, Samples and the 0.5f offset
-----------------------------------------

Consider a 4x4 texture. The array elements would be addressed with integers::

   ix: 0,1,2,3 
   iy: 0,1,2,3 

BUT: in order to retrieve sample values, need to offset float texture coordinates by 0.5::

   x:0.5,1.5,2.5,3.5 
   y:0.5,1.5,2.5,3.5 

So to work with the texture need to realize that the sample values are mid-texel ones and arrange 
the contents of the array (the samples) accordingly.::

      +--------+--------+--------+--------+
      | .5 .5  | 1.5 .5 | 2.5 .5 | 3.5 .5 |
      |   +    |   +    |   +    |   +    | 
      |        |        |        |        |
      +--------+--------+--------+--------+
      | .5 1.5 | 1.5 1.5| 2.5 1.5| 3.5 1.5|
      |   +    |   +    |   +    |   +    |  
      |        |        |        |        |
      +--------+--------+--------+--------+
      | .5 2.5 | 1.5 2.5| 2.5 2.5| 3.5 2.5|
      |   +    |   +    |   +    |   +    |  
      |        |        |        |        |
      +--------+--------+--------+--------+
      | .5 3.5 | 1.5 3.5| 2.5 3.5| 3.5 3.5|
      |   +    |   +    |   +    |   +    |  
      |        |        |        |        |
      +--------+--------+--------+--------+


Top left origin is considered as that more naturally 
to the array serialization, with the first element 
in the array corresponding to texel at top left, 
and the last corresponding to the element at bottom right. 

Thus when creating arrays it is more natural to order 
dimensions (ni,nj) = (height, width) with height before width::

   NP* a = NP::Make<float>( height, width ) 

texture docs
---------------

https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#texture-memory

Whether texture coordinates are normalized or not. By default, textures are
referenced (by the functions of Texture Functions) using floating-point
coordinates in the range [0, N-1] where N is the size of the texture in the
dimension corresponding to the coordinate. For example, a texture that is 64x32
in size will be referenced with coordinates in the range [0, 63] and [0, 31]
for the x and y dimensions, respectively. Normalized texture coordinates cause
the coordinates to be specified in the range [0.0, 1.0-1/N] instead of [0,
N-1], so the same 64x32 texture would be addressed by normalized coordinates in
the range [0, 1-1/N] in both the x and y dimensions. Normalized texture
coordinates are a natural fit to some applications' requirements, if it is
preferable for the texture coordinates to be independent of the texture size.

The addressing mode. It is valid to call the device functions of Section B.8
with coordinates that are out of range. The addressing mode defines what
happens in that case. The default addressing mode is to clamp the coordinates
to the valid range: [0, N) for non-normalized coordinates and [0.0, 1.0) for
normalized coordinates. If the border mode is specified instead, texture
fetches with out-of-range texture coordinates return zero. For normalized
coordinates, the wrap mode and the mirror mode are also available. When using
the wrap mode, each coordinate x is converted to frac(x)=x - floor(x) where
floor(x) is the largest integer not greater than x. When using the mirror mode,
each coordinate x is converted to frac(x) if floor(x) is even and 1-frac(x) if
floor(x) is odd. The addressing mode is specified as an array of size three
whose first, second, and third elements specify the addressing mode for the
first, second, and third texture coordinates, respectively; the addressing mode
are cudaAddressModeBorder, cudaAddressModeClamp, cudaAddressModeWrap, and
cudaAddressModeMirror; cudaAddressModeWrap and cudaAddressModeMirror are only
supported for normalized texture coordinates


**/

#include "NP.hh"

__global__ void demoTexNP(float* output, cudaTextureObject_t texObj, unsigned width, unsigned height)
{   
    unsigned ix = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned iy = blockIdx.y * blockDim.y + threadIdx.y;

    if( ix >= width || iy >= height ) return ; 

    // adding 0.5 avoids interpolation giving directly the mid-texel sample value
    float x = float(ix) + 0.5f ;
    float y = float(iy) + 0.5f ;

    //float v = x ; 
    //float v = y ; 
    float v = tex2D<float>(texObj, x, y ); 

    output[iy * width + ix] = v  ; 

    printf("//demoTexNP : Thread index: (ix,iy) (%i, %i) (x,y) (%10.4f, %10.4f)    v = %f\n", ix, iy, x, y, v ); 
}


/**
uploadTexture
---------------

* ~/opticks/sysrap/tests/SIMGStandaloneTest.cu
* https://docs.nvidia.com/cuda/cuda-runtime-api/structcudaTextureDesc.html

Wrap
Mirror
    cudaAddressModeWrap and cudaAddressModeMirror are only supported 
    for normalized texture coordinates

Clamp

Border

**/

cudaTextureObject_t uploadTexture( const NP* a )
{
    unsigned height = a->shape[0] ; 
    unsigned width = a->shape[1] ; 

    cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(32, 0, 0, 0, cudaChannelFormatKindFloat);
    cudaArray* cuArray;
    cudaMallocArray(&cuArray, &channelDesc, width, height);
    cudaMemcpyToArray(cuArray, 0, 0, a->bytes(), a->arr_bytes(), cudaMemcpyHostToDevice);
    
    struct cudaResourceDesc resDesc;
    memset(&resDesc, 0, sizeof(resDesc));
    resDesc.resType = cudaResourceTypeArray;
    resDesc.res.array.array = cuArray; 

    struct cudaTextureDesc texDesc;
    memset(&texDesc, 0, sizeof(texDesc));

    cudaTextureAddressMode x_addressMode = cudaAddressModeClamp ;  
    cudaTextureAddressMode y_addressMode = cudaAddressModeClamp ;  

    texDesc.addressMode[0] = x_addressMode ;
    texDesc.addressMode[1] = y_addressMode ;

    cudaTextureFilterMode filterMode = cudaFilterModeLinear ;  
    //cudaTextureFilterMode filterMode = cudaFilterModePoint ;    // do not interpolate 
    texDesc.filterMode = filterMode ; 

    // specifies whether integer data should be converted to floating point or not.
    // Note that this applies only to 8-bit and 16-bit integer formats. 
    // 32-bit integer format would not be promoted, regardless of whether or not this is set 
    //cudaTextureReadMode readMode = cudaReadModeNormalizedFloat ; 
    cudaTextureReadMode readMode = cudaReadModeElementType ;  // return data of the type of the underlying buffer

    texDesc.readMode = readMode ;  

    //texDesc.normalizedCoords = 1 ;            // addressing into the texture with floats in range 0:1
    texDesc.normalizedCoords = 0 ;         
    
    cudaTextureObject_t texObj = 0; 
    cudaCreateTextureObject(&texObj, &resDesc, &texDesc, NULL);

    return texObj ; 
}

int main()
{
    NP* a = NP::Make<float>(4, 4); 
    a->fillIndexFlat();  

    unsigned height = a->shape[0] ; 
    unsigned width = a->shape[1] ; 

    cudaTextureObject_t texObj = uploadTexture(a); 

    NP* b = NP::Make<float>(4, 4);  
    // not necessarily the same dimension as *a* (that is the point of interpolation)

    float* d_output;
    cudaMalloc(&d_output, b->arr_bytes() );

    dim3 block(16,16); 
    dim3 grid((width + block.x - 1)/block.x, (height + block.y - 1)/block.y);
    printf(" block (%d, %d) grid (%d, %d) \n", block.x, block.y, grid.x, grid.y ); 

    demoTexNP<<<grid, block>>>(d_output, texObj, width, height);    
    cudaMemcpy(b->bytes(), d_output, b->arr_bytes(),  cudaMemcpyDeviceToHost);

    const char* FOLD = "/tmp/demoTexNP" ; 
    cudaDeviceSynchronize();  // without Synchronize the process terminates before printf output appears 

    a->save(FOLD, "a.npy"); 
    b->save(FOLD, "b.npy"); 

    return 0 ; 
}

