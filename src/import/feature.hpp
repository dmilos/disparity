#ifndef Dh_ComputerVision_StereoMatch_Disparity_Feature_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_Feature_HPP

//  S_match::S_feature::S_disparity::Feature

#include <vector>
#include "graphics/image/image.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      struct Feature
       {
        public:
          typedef std::size_t                 SizeType;
          typedef double                    ScalarType;

          typedef std::vector<ScalarType>     TypeType;
          typedef std::vector<TypeType>       LineType;

        public:
          Feature();

          ScalarType distance( TypeType const& left, TypeType const& right );

          ScalarType dot_abs( TypeType const& left, TypeType const& right );
          ScalarType euclid( TypeType const& left, TypeType const& right );
          ScalarType euclid_normed( TypeType const& left, TypeType const& right );
          ScalarType correlation( TypeType const& left, TypeType const& right );
          ScalarType vector_angle( TypeType const& left, TypeType const& right );
          ScalarType absolute( TypeType const& left, TypeType const& right );
          ScalarType average_minimum( TypeType const& left, TypeType const& right );
          ScalarType average_maximum( TypeType const& left, TypeType const& right );
          ScalarType partial_maximum( TypeType const& left, TypeType const& right );
          ScalarType hamming( TypeType const& left, TypeType const& right );
          ScalarType absolute_trim( TypeType const& left, TypeType const& right );
          ScalarType absolute_truncate( TypeType const& left, TypeType const& right );
          ScalarType suport_weight( TypeType const& left, TypeType const& right );

        private:
         std::vector<ScalarType> m_temp;

       };

     }
   }
 }


#endif
