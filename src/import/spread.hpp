#ifndef Dh_ComputerVision_StereoMatch_Disparity_Spread_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_Spread_HPP

//  S_match::S_feature::S_disparity::Spread.process()

#include "graphics/image/image.hpp"
#include "./entangle/entangler.hpp"
#include "./lasagna.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class Spread
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef std::array<int,2> Integer2DType;
          typedef std::array<ScalarType,2> Scalar2DType;
          typedef ::color::gray<ScalarType> gray_type;

          typedef std::vector<SizeType>  NearestType;

          typedef ::graphics::image::gray_double_t ImageType;
          typedef ::graphics::image::convolve::filter::instance<ScalarType,1> FilterType;
          typedef std::vector<FilterType>  BankType;
          typedef S_match::S_feature::S_disparity::Lasagna  LasagnaType;

          typedef S_match::S_feature::S_disparity::Entangler EntanglerType;
          typedef S_match::S_feature::S_disparity::SquareBase       SquareType;

        public:
          explicit Spread( ScalarType const& epsilon = 0.001 );
        public:
          void prepare( SizeType const& lineno, BankType const& bank, ImageType const& image );
          void prepare( SizeType const& lineno, LasagnaType const& lasagna );
          ScalarType process( SizeType const& x );
          ScalarType dispersion( SizeType const& x );
          ScalarType process();

        public:
          ScalarType m_epsilon;
          std::vector< std::vector< ScalarType > >m_value;

       };

     }
   }
 }


#endif
