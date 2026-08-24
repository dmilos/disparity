#ifndef Dh_ComputerVision_StereoMatch_Stacker_Convolve_HPP
#define Dh_ComputerVision_StereoMatch_Stacker_Convolve_HPP

//  S_match::S_feature::S_disparity::S_Stacker

#include "graphics/image/image.hpp"
#include "../lasagna.hpp"
#include "../disparity.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

    namespace S_Stacker
     {

      class Convolve
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array< std::size_t,2 > Size2DType;

          typedef ::graphics::image::convolve::filter::instance<ScalarType,1> FilterType;
          typedef std::vector<FilterType>  BankType;

          typedef ::graphics::image::gray_double_t ImageType;
          typedef ::graphics::image::rgb_double_t ImageRgbType;

          typedef S_match::S_feature::S_disparity::Lasagna   LasagnaType;
          typedef S_match::S_feature::S_disparity::Disparity   DisparityType;

        public:
          Convolve();

        public:
          bool process( LasagnaType &lasagna, BankType const& bank, ImageType const& image )const;
          bool process( LasagnaType &lasagna, BankType const& bank, ImageRgbType const& image )const;

          bool process( DisparityType &lasagna, BankType const& bank, ImageType const& left, ImageType const& right )const;
          bool process( DisparityType &lasagna, BankType const& bank, ImageRgbType const& left, ImageRgbType const& right )const;
        public:
          bool m_debug;
        private:
          typedef std::vector< std::vector< FilterType > > MaskType;

        public:
          mutable int m_side;
          void makeMask( MaskType &  maskVector, Size2DType const& size, ImageRgbType const& image )const;
          mutable MaskType m_maskLeft, m_maskRight; 
       };

       }
     }
   }
 }


#endif
