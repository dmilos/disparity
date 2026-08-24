#ifndef Dh_ComputerVision_StereoMatch_Disparity_Crosser_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_Crosser_HPP

//  S_match::S_feature::S_disparity::Crosser.processX()

#include "graphics/image/image.hpp"
#include "./entangle/entangler.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Crosser
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
          explicit Crosser( SizeType const& tolerance );
        public:
          SizeType process( ImageType  & image );
          SizeType process( ImageType  & image, SizeType const& y );
          SizeType process( ImageType const& image, SizeType const& x, SizeType const& y );

          SizeType process( EntanglerType & entangler );

          static SizeType degree(  SizeType const& x, EntanglerType const& entangler );
        public:
          SizeType m_tolerance;
       };

     }
   }
 }


#endif
