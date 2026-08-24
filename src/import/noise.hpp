#ifndef Dh_ComputerVision_StereoMatch_Disparity_Noise_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_Noise_HPP

//  S_match::S_feature::S_disparity::Filler().processX()

#include "graphics/image/image.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Noise
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef ::color::gray<ScalarType> gray_type;
      
          typedef ::graphics::image::gray_double_t ImageType;
          typedef ::graphics::image::convolve::filter::instance<ScalarType,1> FilterType;
      
        public:
          Noise();
        public:
          SizeType process( ImageType  & target, ImageType  const& source  )const;
          //SizeType processX( ImageType  & image  );
          //SizeType processY( ImageType  & image  );
        public:
          gray_type m_zero;
       };

     }
   }
 }


#endif
