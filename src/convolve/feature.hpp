#ifndef Dh_ComputerVision_StereoMatch_Disparity_Feature_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_Feature_HPP

//  Feature

#include <vector>

 

      struct Feature
       {
        public:
          typedef std::size_t                 SizeType;
          typedef double                    ScalarType;

          typedef std::vector<ScalarType>     ContainerType;

        public:
          Feature();

          ScalarType distance( ContainerType const& left, ContainerType const& right );

          ScalarType dot_abs( ContainerType const& left, ContainerType const& right );
          ScalarType euclid( ContainerType const& left, ContainerType const& right );
          ScalarType euclid_normed( ContainerType const& left, ContainerType const& right );
          ScalarType correlation( ContainerType const& left, ContainerType const& right );
          ScalarType vector_angle( ContainerType const& left, ContainerType const& right );
          ScalarType absolute( ContainerType const& left, ContainerType const& right );
          ScalarType average_minimum( ContainerType const& left, ContainerType const& right );
          ScalarType average_maximum( ContainerType const& left, ContainerType const& right );
          ScalarType partial_maximum( ContainerType const& left, ContainerType const& right );
          ScalarType hamming( ContainerType const& left, ContainerType const& right );
          ScalarType absolute_trim( ContainerType const& left, ContainerType const& right );
          ScalarType absolute_truncate( ContainerType const& left, ContainerType const& right );
          ScalarType suport_weight( ContainerType const& left, ContainerType const& right );

        private:
         std::vector<ScalarType> m_temp;

       };

#endif
