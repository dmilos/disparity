#ifndef Dh_ComputerVision_StereoMatch_Disparity_SquareBase_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_SquareBase_HPP

//  S_match::S_feature::S_disparity::SquareBase

#include "graphics/image/image.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class SquareBase
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef ::color::gray<ScalarType> gray_type;

          typedef ::graphics::image::gray_double_t ImageType;
          
          typedef  ImageType TableType;

        public:
          explicit SquareBase( );

        public:
          ScalarType        get( Size2DType const& point )const;
          bool              set( Size2DType const& point, ScalarType const& value );
          bool              valid( Size2DType const& point )const;
          Size2DType const& resolution()const;
          bool              resolution( Size2DType const& r );

        public:
           TableType const& table()const{ return m_table; }
        protected:
           TableType  & table() { return m_table; }
        protected:
           TableType m_table;
       };

     }
   }
 }


#endif
