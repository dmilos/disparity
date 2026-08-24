#ifndef Dh_ComputerVision_StereoMatch_Disparity_Limiter_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_Limiter_HPP

//  S_match::S_feature::S_disparity::Limiter.process()

#include "graphics/image/image.hpp"
#include "./entangle/entangler.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Limiter
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef std::array<ScalarType,2> Scalar2DType;
          typedef ::color::gray<ScalarType> gray_type;

          typedef std::vector<SizeType>  NearestType;

          typedef ::graphics::image::gray_double_t ImageType;
          typedef ::graphics::image::convolve::filter::instance<ScalarType,1> FilterType;

          typedef S_match::S_feature::S_disparity::Entangler EntanglerType;
        public:
          explicit Limiter( ScalarType const& left, ScalarType const& right );
        public:
          SizeType process( EntanglerType & entangler );

        public:
          ScalarType m_LimitLeft;
          ScalarType m_LimitRight;
       };

     }
   }
 }


#endif
