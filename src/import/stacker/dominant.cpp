#include "opencv2/opencv.hpp"
#include "./dominant.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

#define MY_DEBUG  1

S_match::S_feature::S_disparity::S_Stacker::Dominant::Dominant( Size2DType const & size  )
 {
  m_debug = true;
  m_size = size;
  //m_trash = trash;
 }

bool S_match::S_feature::S_disparity::S_Stacker::Dominant::process( LasagnaType &lasagna, ImageType const& image )const
 {
  //if( true == m_debug )std::cout << PREFIX << "Dominant ..." << std::endl;

  SizeType width = image.resolution()[0];
  SizeType height = image.resolution()[1];
  SizeType offset = lasagna.layer().size();

  lasagna.layer().resize( offset + 3*m_size[0]*m_size[1] );
  for( SizeType index=0; index < 3*m_size[0]*m_size[1]; ++index )
   {
    auto & layer = lasagna.layer()[ offset + index ];
    layer.resolution( image.resolution(), color::gray<double>({0}) );
   }
#if 1 == MY_DEBUG
   /*debug*/::graphics::image::rgb_double_t maskC{ { m_size[0], m_size[1] }, color::rgb<double>({0,0,0}) };
#endif

  for( int y=0; y < height; ++y )
   {
    for( int x=0; x < width; ++x )
     {
#if 1 == MY_DEBUG
       /*debug*/ if( ( x == x ) && ( 30 == y ) )
        {
         m_debug = true;
         //graphics::image::save( "the_image_" + m_side + ".png", image );
        } else { m_debug = false; }
#endif
      auto const&   C = image.get( {(SizeType)x,(SizeType)y} );
      auto E = extract( C );

      for( SizeType index=0; index < m_size[0]*m_size[1]; ++index )
       {
        int xo =( (int)index %  (int)m_size[0] ) -  (int)m_size[0]/2;
        int yo =( (int)index /  (int)m_size[1] ) -  (int)m_size[1]/2;
        auto & layerR = lasagna.layer()[ offset + 3*index + 0 ];
        auto & layerG = lasagna.layer()[ offset + 3*index + 1 ];
        auto & layerB = lasagna.layer()[ offset + 3*index + 2 ];

        auto X = x + xo; if( X < 0 ) continue; if( width  <= X ) continue;
        auto Y = y + yo; if( Y < 0 ) continue; if( height <= Y ) continue;

        auto const& c = image.get( { (SizeType)X, (SizeType)Y } );
        auto e = extract( c );

        if( compare( e, E ) )
         {
          layerR.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { e[0] } ) );
          layerG.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { e[1] } ) );
          layerB.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { e[2] } ) );
#if 1 == MY_DEBUG
            /*debug*/if( true == m_debug ){ maskC.set( { xo + m_size[0]/2, yo + m_size[1]/2 }, color::rgb<double>( { e[0], e[1], e[2] } ) ); };
#endif
         }
        else
         {
          layerR.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
          layerG.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
          layerB.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
#if 1 == MY_DEBUG
            /*debug*/ if( true == m_debug ) { maskC.set( { xo + m_size[0]/2, yo + m_size[1]/2 }, ::color::constant::black_t{} ); };
#endif
         }
       }

#if 1 == MY_DEBUG
        std::stringstream ss; ss << std::setfill('0')<< std::setw(3)<< x << "x" << std::setw(3) << y;

        /*debug*/if( true == m_debug ) graphics::image::save( "mask_" + m_side + "_C" + ss.str() + ".png", maskC );
#endif
     }
   }
 /*debug*/if( true == m_debug ) graphics::image::save( "the_image" + m_side + ".png", image );

  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::Dominant::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  m_side = "L"; process( disparity.m_left ,  left );
  m_side = "R"; process( disparity.m_right, right );
  return true;
 }


S_match::S_feature::S_disparity::S_Stacker::Dominant::ColorType 
S_match::S_feature::S_disparity::S_Stacker::Dominant::extract( ColorType const& value )
 {
  ColorType result;
  double m_graTrash = 16.0 / 256.0;

  double grayMax = std::max( { value[0], value[1], value[2] } );
  double grayMin = std::min( { value[0], value[1], value[2] } );

  if( grayMax - grayMin < m_graTrash )
   {
    result[0] = color::get::gray( value );
    result[1] = color::get::gray( value );
    result[2] = color::get::gray( value );
    return result;
   }

  auto r = ::color::get::red<     ::color::get::constant::rgb::red::hsl_star_entity     >( value ); 
  auto g = ::color::get::green<   ::color::get::constant::rgb::green::hsl_star_entity   >( value ); 
  auto b = ::color::get::blue<    ::color::get::constant::rgb::blue::hsl_star_entity    >( value );
 
  auto c = ::color::get::cyan<    ::color::get::constant::rgb::cyan::hsl_star_entity    >( value ); 
  auto y = ::color::get::yellow<  ::color::get::constant::rgb::yellow::hsl_star_entity  >( value ); 
  auto m = ::color::get::magenta< ::color::get::constant::rgb::magenta::hsl_star_entity >( value );

  result[0] = 0;  result[1] = 0;  result[2] = 0;
  double M = -1.0; 

  if( M < r ) { result[0] = r; M = r; }
  if( M < g ) { result[1] = g; M = g; }
  if( M < b ) { result[2] = b; M = b; }

  if( M < c ) {                 result[1] = c; result[2] = c;     M = c; }
  if( M < y ) { result[0] = y;  result[1] = y;                    M = y; }
  if( M < m ) { result[0] = m;                 result[2] = m;     M = m; }

 
  return result;
 }

bool      
S_match::S_feature::S_disparity::S_Stacker::Dominant::compare( ColorType const& l, ColorType const& r )
 {
  auto d = color::operation::distance( l, r );
 
  return d < 32.0/256.0;
 }



