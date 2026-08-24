#ifndef Dh_ComputerVision_StereoMatch_Disparity_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_HPP

//  S_match::S_feature::S_disparity::Disparity

#include "graphics/image/image.hpp"
#include "./feature.hpp"
#include "./square/squaref.hpp"
#include "./cube.hpp"
#include "./entangle/entangler.hpp"
#include "./lasagna.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Disparity
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef ::color::gray<ScalarType> gray_type;

          typedef ::graphics::image::gray_double_t ImageType;
          typedef std::vector<SizeType>  RestrictionType;
          typedef std::vector<SizeType>  NearestType;

          typedef S_match::S_feature::S_disparity::Feature::TypeType  FeatureType;
          typedef S_match::S_feature::S_disparity::Feature::LineType  LineType;
          typedef S_match::S_feature::S_disparity::Square      SquareType;
          typedef S_match::S_feature::S_disparity::Cube       CubeType;
          typedef S_match::S_feature::S_disparity::Entangler  EntanglerType;
          typedef S_match::S_feature::S_disparity::Lasagna  LasagnaType;

          typedef LasagnaType::LayerType  LayerType;

        public:
          Disparity();
        public:
          void clear();
          bool append(    LayerType const& left, LayerType const& right );
          SizeType process( ImageType  & image );
          SizeType process_restricted( ImageType  & image );

        public:
         void prepare_cube( );
        public:
          ScalarType square( SizeType const& y );
          void       square_cube( SizeType const& y );
          void       square_restricted( SizeType const& y );
          ImageType const& square( )const{ return m_square.table(); }
          void   besting( ){ m_entangler.global( m_square ); }

        public:
          std::vector<CubeType>       m_cube;
          SquareType     m_square;
          EntanglerType  m_entangler;
        public:
          SizeType     process( ImageType & image, SizeType const& y );
        public:
          SizeType evaluate()const;

        public:
          RestrictionType const& restriction()const;
          bool                   restriction( RestrictionType const& r );
        public:
          void restriction( LineType &rest, LasagnaType const& lasagna, SizeType const& lineno )const;
          RestrictionType m_restriction;
        public:

        public:
          SizeType m_iteration;
          LasagnaType m_left;
          LineType m_leftLine, m_leftLineRestrict; //!< temporal ??
          LasagnaType m_right;
          LineType m_rightLine, m_rightLineRestrict; //!< temporal ??
        private:

          bool m_debug;
       };

     }
   }
 }


#endif
