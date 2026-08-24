#ifndef Dh_ComputerVision_StereoMatch_Disparity_OutLier_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_OutLier_HPP

//  S_match::S_feature::S_disparity::OutLier.processX()

#include "graphics/image/image.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class OutLier
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef std::array<ScalarType,2> Scalar2DType;
          typedef ::color::gray<ScalarType> gray_type;
          typedef ::math::geometry::direction::ABC2D< ScalarType > direction_type;
      
          typedef ::graphics::image::gray_double_t ImageType;
          typedef ::graphics::image::convolve::filter::instance<ScalarType,1> FilterType;
      
        public:
          explicit OutLier( ScalarType const& trash );
        public:
          SizeType process( ImageType  & image );
          SizeType process( ImageType  & image, SizeType const& y );
          SizeType process( direction_type & direction, ScalarType const& trash, ImageType  const& image, SizeType const& y );
        public:
          ::math::geometry::direction::fit2D<double>::cloud_type m_cloud;
        private:
          ScalarType m_trash;
          direction_type m_direction;
       };

     }
   }
 }


#endif
