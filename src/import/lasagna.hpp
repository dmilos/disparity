#ifndef Dh_ComputerVision_StereoMatch_Lasagna_HPP
#define Dh_ComputerVision_StereoMatch_Lasagna_HPP

//  S_match::S_feature::S_disparity::Lasagna

#include "graphics/image/image.hpp"
#include "./feature.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Lasagna
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef std::array<std::size_t,3> Size3DType;
          typedef ::color::gray<ScalarType> gray_type;

          typedef ::graphics::image::gray_double_t ImageType, LayerType;
          typedef  std::vector<LayerType>     ContainerType;
          typedef ::graphics::image::convolve::filter::instance<ScalarType,1> FilterType;
          typedef std::vector<FilterType>  BankType;
          typedef S_match::S_feature::S_disparity::Feature::TypeType  FeatureType;
          typedef S_match::S_feature::S_disparity::Feature::LineType  LineType;

        public:
          Lasagna();

        public:
          SizeType  depth() const;
          Size2DType const& resolution() const;
        public:
          void clear(  );
          bool append( LayerType const& image );

        public:
          bool       get( FeatureType &feature, Size2DType const& coord )const;
          ScalarType get( Size3DType const& coord )const;
          bool       get( LineType &line, SizeType const& y )const;
        public:
          bool       set( Size3DType const& coord, ScalarType const& v );
          bool       set( Size2DType const& coord, SizeType const& level, ScalarType const& v );
          bool       set( SizeType const& x, SizeType const& y, SizeType const& level, ScalarType const& v );

          ContainerType const& layer()const{ return m_container; }
          ContainerType      & layer() { return m_container; }
        private:
          ContainerType m_container;
          bool m_debug;
       };

     }
   }
 }


#endif
