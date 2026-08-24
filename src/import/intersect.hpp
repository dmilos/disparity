#ifndef Dh_ComputerVision_StereoMatch_Intersect_HPP
#define Dh_ComputerVision_StereoMatch_Intersect_HPP

//  S_match::S_feature::S_disparity::Intersect

#include "graphics/image/image.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Intersect
       {
        public:
          typedef std::size_t SizeType;
          typedef double ScalarType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef ::color::gray<ScalarType> gray_type;

          typedef ::graphics::image::gray_double_t ImageType;


        public:
          Intersect();

        public:
          bool process( ImageType & result, ImageType const& left, ImageType const& right );

          ScalarType m_trash;
       };

     }
   }
 }


#endif
