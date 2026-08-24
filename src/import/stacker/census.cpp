#include "opencv2/opencv.hpp"
#include "./census.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

#define MY_DEBUG  0

S_match::S_feature::S_disparity::S_Stacker::Census::Census( Size2DType const & size )
 {
  m_debug = true;
  m_size = size;
 }

bool S_match::S_feature::S_disparity::S_Stacker::Census::process( LasagnaType &lasagna, ImageType const& image )const
 {
  //if( true == m_debug )std::cout << PREFIX << "MaskC ..." << std::endl;
#if 1 == MY_DEBUG
 graphics::image::save( "the_image-Census-" + m_side + ".png", image );
#endif

  SizeType width = image.resolution()[0];
  SizeType height = image.resolution()[1];
  SizeType offset = lasagna.layer().size();

  lasagna.layer().resize( offset +  m_size[0]*m_size[1] );
  for( SizeType index=0; index <  m_size[0]*m_size[1]; ++index )
   {
    auto & layer = lasagna.layer()[ offset + index ];
    layer.resolution( image.resolution(), color::gray<double>({0}) );
   }
#if 1 == MY_DEBUG
   /*debug*/::graphics::image::rgb_double_t maskC{ { m_size[0], m_size[1] }, color::rgb<double>({0,0,0}) };
   /*debug*/::graphics::image::rgb_double_t maskW{ { m_size[0], m_size[1] }, color::rgb<double>({0,0,0}) };
#endif

  for( int y=0; y < height; ++y )
   {
    for( int x=0; x < width; ++x )
     {
#if 1 == MY_DEBUG
       /*debug*/ if( ( 90 == x ) && ( 17 == y ) ) 
        {
         m_debug = true;
        } else { m_debug = false; }
#endif
      auto const&   C = image.get( {(SizeType)x,(SizeType)y} );

      for( SizeType index=0; index < m_size[0]*m_size[1]; ++index )
       {
        int xo =( (int)index %  (int)m_size[0] ) - (int)m_size[0]/2;
        int yo =( (int)index /  (int)m_size[1] ) - (int)m_size[1]/2;
        auto & layer = lasagna.layer()[ offset + index ];

        auto X = x + xo; if( X < 0 ) continue; if( width  <= X ) continue;
        auto Y = y + yo; if( Y < 0 ) continue; if( height <= Y ) continue;
        auto const& c = image.get( { (SizeType)X, (SizeType)Y } );

        auto  diff = fabs( color::get::gray( C )  - color::get::gray( c ) ) ;
        if(  color::get::gray( c ) < color::get::gray( C ) )
         {
          layer.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { diff } ) );
#if 1 == MY_DEBUG
            /*debug*/ if( true == m_debug ) { maskW.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, ::color::constant::white_t{} ); };
            /*debug*/ if( true == m_debug ) { maskC.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, ::color::rgb<double>( {diff,diff,diff} ) ); };
#endif
         }
        else
         {
          layer.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { diff } ) );
#if 1 == MY_DEBUG
            /*debug*/ if( true == m_debug ) { maskW.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, ::color::constant::black_t{} ); };
            /*debug*/ if( true == m_debug ) { maskC.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, ::color::constant::black_t{} ); };
            /*debug*/ if( true == m_debug ) { maskC.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, ::color::rgb<double>( {diff, diff, diff} ) ); };
#endif
         }
       }

#if 1 == MY_DEBUG
        std::stringstream ss; ss << std::setfill('0')<< std::setw(3)<< x << "x" << std::setw(3) << y; 
        
        /*debug*/if( true == m_debug ) graphics::image::save( "census_" + m_side + "_C" + ss.str() + ".png", maskC );
        /*debug*/if( true == m_debug ) graphics::image::save( "census_" + m_side + "_W" + ss.str() + ".png", maskW );
#endif
     }
   }
  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::Census::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  m_side = "L"; process( disparity.m_left ,  left );
  m_side = "R"; process( disparity.m_right, right );
  return true;
 }
