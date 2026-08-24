#ifndef Dh_ComputerVision_StereoMatch_Disparity_pure_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_pure_HPP

//  S_match::S_feature::S_disparity::Pure

#include "graphics/image/image.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Pure
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef ::color::gray<ScalarType> gray_type;

          typedef ::graphics::image::gray_double_t ImageGrayType;
          typedef ::graphics::image::rgb_double_t ImageRGBType;
          typedef ::graphics::image::lab_double_t ImageLABType;

        public:
          Pure();

        public:
          virtual SizeType process( ImageGrayType  & image, ImageRGBType const& left, ImageRGBType const& right )const=0;

       };

     }
   }
 }


#endif
