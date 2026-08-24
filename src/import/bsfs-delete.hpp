#ifndef Dh_ComputerVision_StereoMatch_BSFS_HPP
#define Dh_ComputerVision_StereoMatch_BSFS_HPP

//  S_match::S_feature::S_disparity::BSFS

#include "graphics/image/image.hpp"
#include "./feature.hpp"
#include "./lasagna.hpp"
#include "./pure.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class BSFS
       : public S_match::S_feature::S_disparity::Pure
       {
        public:
          typedef std::size_t SizeType;
          typedef double ScalarType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef ::color::gray<ScalarType> gray_type;

          using Pure::ImageGrayType;
          using Pure::ImageRGBType;
          typedef ::graphics::image::convolve::filter::instance<ScalarType,1> FilterType;
          typedef std::vector<FilterType>  BankType;

          typedef S_match::S_feature::S_disparity::Feature::TypeType  FeatureType;
          typedef S_match::S_feature::S_disparity::Lasagna  LasagnaType;

        public:
          BSFS();

        public:
          SizeType process( ImageGrayType  & image, ImageRGBType const& left, ImageRGBType const& right )const;
        public:
          void clear();
          void bank( BankType const& B );

        private:
          SizeType process( ImageGrayType  & image )const;

        private:
          mutable std::vector< std::vector< double> > m_cost;
          double m_occlusion;
          double m_coefficient;

        public:
          BankType m_bank;

        public:
          mutable LasagnaType m_left;
          mutable LasagnaType m_right;

        public:
          bool m_debug;
        private:
          ScalarType distance( SizeType const& line, SizeType const& L, SizeType const& R )const;
          static ScalarType min( ScalarType a, ScalarType b, ScalarType c );
          static ScalarType sqr( ScalarType a );
       };

     }
   }
 }


#endif
