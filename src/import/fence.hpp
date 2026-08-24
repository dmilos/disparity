#ifndef Dh_ComputerVision_StereoMatch_Disparity_Fence_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_Fence_HPP

//  S_match::S_feature::S_disparity::Fence.process()

#include "graphics/image/image.hpp"
#include "./entangle/entangler.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Fence
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef std::array<ScalarType,2> Scalar2DType;
          typedef ::color::gray<ScalarType> gray_type;
       
          typedef std::vector<SizeType>  NearestType;

          typedef ::graphics::image::gray_double_t ImageType;
          typedef ::graphics::image::convolve::filter::instance<ScalarType,1> FilterType;
      
          typedef S_match::S_feature::S_disparity::Entangler EntanglerType;
        public:
          explicit Fence( SizeType const& space );
        public:
           // left fence
           // 
           // +xxxxx___L___Axxxx
           // +xxxxA___L___xxxxx
          SizeType processL( EntanglerType & entangler );
          
          // right fence
          // +xxxxA___L___xxxx
          // +xxxxx___L___Axxxx
          SizeType processR( EntanglerType & entangler );

        public:
          SizeType m_lenght;
        public:
          typedef std::pair<SizeType,SizeType>  ChunkType;
          static  ChunkType searchL( SizeType const& L, EntanglerType const& entangler );

          static  SizeType measureLL( SizeType  beginR, EntanglerType const& entangler );
          static  SizeType measureLR( SizeType  beginR, EntanglerType const& entangler );
          static  SizeType measureRL( SizeType  beginR, EntanglerType const& entangler );
          static  SizeType measureRR( SizeType  beginR, EntanglerType const& entangler );
       };

     }
   }
 }




#endif
