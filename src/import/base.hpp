#ifndef Dh_ComputerVision_StereoMatch_Disparity_base_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_base_HPP

//  S_match::S_feature::S_disparity::Pure

#include "graphics/image/image.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Base : public S_match::S_feature::S_disparity::Pure
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef ::color::gray<ScalarType> gray_type;

          typedef ::graphics::image::gray_double_t ImageGrayType;
          typedef ::graphics::image::rgb_double_t ImageRGBType;


          typedef S_match::S_feature::S_disparity::Entangler  EntanglerType;
          typedef  S_match::S_feature::S_disparity::SquareBase      SquareType;

        public:
          Pure();

        public:
          SizeType process( ImageGrayType  & image, ImageRGBType const& left, ImageRGBType const& right )const;

        public:
          LasagnaType    m_left;
          LasagnaType    m_right;
          SquareType     m_square;
          EntanglerType  m_entangler;
       };

     }
   }
 }


#endif
