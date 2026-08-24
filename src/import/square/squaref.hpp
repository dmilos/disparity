#ifndef Dh_ComputerVision_StereoMatch_Disparity_SquareFeature_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_SquareFeature_HPP

//  S_match::S_feature::S_disparity::Square

#include "../feature.hpp"
#include "./squareb.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Square
       : public S_match::S_feature::S_disparity::SquareBase
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;

          typedef  S_match::S_feature::S_disparity::Feature  FeatureType;
          typedef  S_match::S_feature::S_disparity::Feature::LineType LineType;

        public:
          explicit Square( );

        public:
          bool process( LineType const&left, LineType const&right );
        private:
          FeatureType m_feature;
       };

     }
   }
 }

#endif
