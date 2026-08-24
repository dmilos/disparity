#ifndef Dh_ComputerVision_StereoMatch_Disparity_Filler_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_Filler_HPP

//  S_match::S_feature::S_disparity::Filler().processX()

#include "graphics/image/image.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Filler
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef ::color::gray<ScalarType> gray_type;
      
          typedef ::graphics::image::gray_double_t ImageType;
          typedef ::graphics::image::convolve::filter::instance<ScalarType,1> FilterType;
      
        public:
          Filler();
        public:
          SizeType process( ImageType   & image  );
          SizeType processX( ImageType  & image  );
          SizeType processX2( ImageType  & image, SizeType const& gap  );
          SizeType processY( ImageType  & image  );
          SizeType processY2( ImageType  & image, SizeType const& gap  );
        gray_type m_zero;
       };

     }
   }
 }


#endif
