#ifndef Dh_ComputerVision_StereoMatch_Stacker_SegmentationL_HPP
#define Dh_ComputerVision_StereoMatch_Stacker_SegmentationL_HPP

//  S_match::S_feature::S_disparity::S_Stacker

#include "graphics/image/image.hpp"
#include "../lasagna.hpp"
#include "../disparity.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

    namespace S_Stacker
     {

      class SegmentationL
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;

          typedef ::graphics::image::rgb_double_t ImageType;
          typedef ::graphics::image::gray_double_t ImageGrayType;

          typedef S_match::S_feature::S_disparity::Lasagna   LasagnaType;
          typedef S_match::S_feature::S_disparity::Disparity   DisparityType;

          typedef ::graphics::image::gray_double_t LayerType;

        public:
          SegmentationL( SizeType const& precision=255, SizeType const& interval=12 );

        public:
          bool process( LasagnaType &lasagna, SizeType const& image )const;
          bool process( DisparityType &disparity, SizeType const& left, SizeType const& right )const;
        public:
          bool m_debug;
          SizeType m_precision;
          SizeType m_interval;
       };

       }
     }
   }
 }


#endif
