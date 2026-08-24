#ifndef Dh_ComputerVision_StereoMatch_Chef_HPP
#define Dh_ComputerVision_StereoMatch_Chef_HPP

//  S_match::S_feature::S_disparity::Chef

#include "graphics/image/image.hpp"
#include "./pure.hpp"
#include "./disparity.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Chef
       : public S_match::S_feature::S_disparity::Pure
       {
        public:
          typedef  std::size_t SizeType;
          typedef  double ScalarType;

          typedef S_match::S_feature::S_disparity::Pure    PureType;
          typedef PureType::SizeType           SizeType;
          typedef PureType::ImageGrayType ImageGrayType;
          typedef PureType::ImageRGBType   ImageRGBType;

        public:
          Chef();
        public:
          SizeType process( ImageGrayType  & image, ImageRGBType const& left, ImageRGBType const& right )const;

        private:
          typedef S_match::S_feature::S_disparity::Disparity    DisparityType;

         typedef graphics::image::convolve::filter::instance<ScalarType,1> filter_type;
         typedef std::vector< filter_type > bank_type;
         mutable DisparityType m_disparity;
         mutable ImageGrayType m_leftG, m_rightG;

         static filter_type single_gabor( SizeType size, ScalarType angle, ScalarType frequency, ScalarType shift, std::array<ScalarType,2> const& scale );
         static void make_bank( bank_type & bank );
       };

     }
   }
 }


#endif
