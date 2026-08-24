#ifndef Dh_ComputerVision_StereoMatch_Stacker_SegmentationCQ_HPP
#define Dh_ComputerVision_StereoMatch_Stacker_SegmentationCQ_HPP

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

      class SegmentationCQ
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;

          typedef ::graphics::image::rgb_double_t ImageType;

          typedef S_match::S_feature::S_disparity::Lasagna   LasagnaType;
          typedef S_match::S_feature::S_disparity::Disparity   DisparityType;

        public:
          SegmentationCQ( SizeType const& size = 12 );

        public:
          bool process( LasagnaType &lasagna, ImageType const& image )const;
          bool process( DisparityType &disparity, ImageType const& left, ImageType const& right )const;

        public:
          bool m_debug;
          SizeType m_size;
        private:
          ScalarType m_factor;

       };

       }
     }
   }
 }


#endif
