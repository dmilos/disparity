#ifndef Dh_ComputerVision_StereoMatch_Stacker_Census_HPP
#define Dh_ComputerVision_StereoMatch_Stacker_Census_HPP

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

      class Census
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;

          typedef ::graphics::image::rgb_double_t ImageType;

          typedef S_match::S_feature::S_disparity::Lasagna   LasagnaType;
          typedef S_match::S_feature::S_disparity::Disparity   DisparityType;

        public:
          Census( Size2DType const & size );

        public:
          bool process( LasagnaType &lasagna, ImageType const& image )const;
          bool process( DisparityType &disparity, ImageType const& left, ImageType const& right )const;
        public:
          mutable bool m_debug;
          Size2DType m_size;
          mutable std::string m_side;
       };

       }
     }
   }
 }


#endif
