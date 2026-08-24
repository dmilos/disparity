#ifndef Dh_ComputerVision_StereoMatch_Offset_HPP
#define Dh_ComputerVision_StereoMatch_Offset_HPP

//  S_match::S_feature::S_disparity::Offset().process()

#include "graphics/image/image.hpp"
#include "./feature.hpp"
#include "./lasagna.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Offset
       {
        public:
          typedef std::size_t SizeType;
          typedef std::array<int,2> Int2DType;
          typedef S_match::S_feature::S_disparity::Lasagna  LasagnaType;

        public:
          Offset();

         void process( LasagnaType & lasagna, SizeType const& index, Int2DType const& offset )const;

       };

     }
   }
 }


#endif
