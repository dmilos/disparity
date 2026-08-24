#ifndef Dh_ComputerVision_StereoMatch_Stacker_WT97_HPP
#define Dh_ComputerVision_StereoMatch_Stacker_WT97_HPP

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

        class WT97
         {
          public:
            typedef double ScalarType;
            typedef std::size_t SizeType;

            typedef ::color::gray<double> ColorType;
            typedef ::graphics::image::rgb_double_t ImageType;

            typedef S_match::S_feature::S_disparity::Lasagna   LasagnaType;
            typedef S_match::S_feature::S_disparity::Disparity   DisparityType;

          public:
            WT97( SizeType const& size, ScalarType const& trash );

          public:
            bool process( LasagnaType &lasagna, ImageType const& image )const;
            bool process( DisparityType &disparity, ImageType const& left, ImageType const& right )const;
          public:
            bool m_debug;
            SizeType m_size;
            ScalarType m_trash;
         };

       }
     }
   }
 }


#endif
