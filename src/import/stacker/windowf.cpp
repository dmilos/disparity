#include "opencv2/opencv.hpp"
#include "./windowf.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"
#define MY_DEBUG 0

S_match::S_feature::S_disparity::S_Stacker::WindowF::WindowF( ExtractorType const& extractor, Size2DType const & size )
 {
  m_extractor = extractor;
  m_debug = true;
  m_size = size;
 }


bool S_match::S_feature::S_disparity::S_Stacker::WindowF::process( LasagnaType &lasagna, ImageType const& image )const
 {
  //if( true == m_debug )std::cout << PREFIX << "WindowF ..." << std::endl;

  SizeType width = image.resolution()[0];
  SizeType height = image.resolution()[1];
  SizeType offset = lasagna.layer().size();

  lasagna.layer().resize( offset +  m_size[0]*m_size[1] );
  for( SizeType index=0; index < m_size[0]*m_size[1]; ++index )
   {
    auto & layer = lasagna.layer()[ offset + index ];
    layer.resolution( image.resolution(), color::gray<double>({0}) );
   }
#if 1 == MY_DEBUG
   /*debug*/::graphics::image::gray_double_t mask{ { m_size[0], m_size[1] }, color::rgb<double>({0,0,0}) } };
#endif

  for( int y=0; y < height; ++y )
   {
    for( int x=0; x < width; ++x )
     {
#if 1 == MY_DEBUG
        /*debug*/ if( ( ( 260 < x ) && ( x < 330 ) ) && ( 146 == y ) ) { m_debug = true; } else { m_debug = false; }
#endif
      for( SizeType index=0; index < m_size[0]*m_size[1]; ++index )
       {
        int xo =( (int)index %  (int)m_size[0] ) -  (int)m_size[0]/2;
        int yo =( (int)index /  (int)m_size[1] ) -  (int)m_size[1]/2;
        auto & layer = lasagna.layer()[ offset + index ];

        auto X = x + xo; if( X < 0 ) continue; if( width  <= X ) continue;
        auto Y = y + yo; if( Y < 0 ) continue; if( height <= Y ) continue;
        auto const c = m_extractor( image.get( { (SizeType)X, (SizeType)Y } ) );

        layer.set( { (SizeType)x,(SizeType)y }, color::gray<double> ( { c } ) );
#if 1 == MY_DEBUG
        /*debug*/ if( true == m_debug ) { mask.set( { xo + m_size[0]/2, yo + m_size[1]/2 }, ::color::constant::black_t{} ); };
#endif
       }

#if 1 == MY_DEBUG
      /*debug*/if( true == m_debug ) graphics::image::save( "maskC_" + std::to_string(y)  +"-"+ std::to_string(x) + ".png", mask );
      /*debug*/if( true == m_debug ) graphics::image::save( "maskW_" + std::to_string(y)  +"-"+ std::to_string(x) + ".png", mask );
#endif
     }
   }

  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::WindowF::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  process( disparity.m_left ,  left );
  process( disparity.m_right, right );
  return true;
 }
