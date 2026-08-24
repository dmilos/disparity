#include "opencv2/opencv.hpp"
#include "./maskv.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"
#define MY_DEBUG 0

S_match::S_feature::S_disparity::S_Stacker::MaskV::MaskV( ExtractorType const& extractor, Size2DType const & size, ScalarType const & trash )
 {
  m_debug = true;
  m_size = size;
  m_trash = trash;
  m_extractor = extractor;
 }

bool S_match::S_feature::S_disparity::S_Stacker::MaskV::process( LasagnaType &lasagna, ImageType const& image )const
 {
  //if( true == m_debug )std::cout << PREFIX << "MaskV ..." << std::endl;

  SizeType width = image.resolution()[0];
  SizeType height = image.resolution()[1];
  SizeType offset = lasagna.layer().size();

  SizeType total = 3*m_size[0]*m_size[1];
  lasagna.layer().resize( offset + total );
  for( SizeType index=0; index < total; ++index )
   {
    auto & layer = lasagna.layer()[ offset + index ];
    layer.resolution( image.resolution(), color::gray<double>({0}) );
   }
#if 1 == MY_DEBUG
   /*debug*/::graphics::image::rgb_double_t maskC{ { m_size[0], m_size[1] }, color::rgb<double>({0,0,0}) } };
   /*debug*/::graphics::image::rgb_double_t maskW{ { m_size[0], m_size[1] }, color::rgb<double>({0,0,0}) } };
#endif

  for( int y=0; y < height; ++y )
   {
    for( int x=0; x < width; ++x )
     {
#if 1 == MY_DEBUG
        /*debug*/ if( ( ( 260 < x ) && ( x < 330 ) ) && ( 146 == y ) ) { m_debug = true; } else { m_debug = false; }
#endif
      auto const C = m_extractor( image.get( {(SizeType)x,(SizeType)y} ) );
      for( SizeType index=0; index < total/3; ++index    )
       {
        int xo =( (int)index %  (int)m_size[0] ) -  (int)m_size[0]/2;
        int yo =( (int)index /  (int)m_size[1] ) -  (int)m_size[1]/2;
        auto & layer0 = lasagna.layer()[ offset + 3*index + 0 ];
        auto & layer1 = lasagna.layer()[ offset + 3*index + 1 ];
        auto & layer2 = lasagna.layer()[ offset + 3*index + 2 ];

        auto X = x + xo; if( X < 0 ) continue; if( width  <= X ) continue;
        auto Y = y + yo; if( Y < 0 ) continue; if( height <= Y ) continue;
        auto const c = m_extractor( image.get( { (SizeType)X, (SizeType)Y } ) );
        double vector_distance = math::linear::vector::distance( c, C ) ;
        if( vector_distance < m_trash )
         {
          double weight = 1;
        //double pixel_distance = sqrt( xo*xo+yo*yo )/( m_size/2.0 );
          //weight  = 1 - vector_distance;
          //weight  =  ::math::function::ramp<ScalarType>( 1 - pixel_distance ); 
          //weight =  ::math::function::ramp<ScalarType>( ::math::function::any_to_any<ScalarType>( pixel_distance/sqrt(2), 0, (ScalarType)m_size/2, 1, 0 ) ); 
          //weight =  ::math::function::ramp<ScalarType>( ::math::function::any_to_any<ScalarType>( vector_distance, 15.0 / 100.0, 3.0 / 100.0, 0.0 ,1.0 ) );
          //weight = exp( - pixel_distance*pixel_distance );
          //weight  = 1 - vector_distance/m_trash;

          layer0.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { weight * c[0]  } ) );
          layer1.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { weight * c[1]  } ) );
          layer2.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { weight * c[2]  } ) );
#if 1 == MY_DEBUG
           /*debug*/if( true == m_debug ){ maskW.set( { xo + m_size[0]/2, yo + m_size[1]/2 }, color::rgb<double>( { weight,weight,weight } ) ); };
           /*debug*/if( true == m_debug ){ maskC.set( { xo + m_size[0]/2, yo + m_size[1]/2 }, color::rgb<double>( { weight*c[0],weight*c[1],weight*c[2] } ) ); };
#endif
         }
        else
         {
          layer0.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
          layer1.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
          layer2.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
#if 1 == MY_DEBUG
            /*debug*/ if( true == m_debug ) { maskW.set( { xo + m_size[0]/2, yo + m_size[1]/2 }, ::color::constant::black_t{} ); };
            /*debug*/ if( true == m_debug ) { maskC.set( { xo + m_size[0]/2, yo + m_size[1]/2 }, ::color::constant::black_t{} ); };
#endif
         }
       }

#if 1 == MY_DEBUG
        /*debug*/if( true == m_debug ) graphics::image::save( "maskC_" + std::to_string(y)  +"-"+ std::to_string(x) + ".png", maskC );
        /*debug*/if( true == m_debug ) graphics::image::save( "maskW_" + std::to_string(y)  +"-"+ std::to_string(x) + ".png", maskW );
#endif
     }
   }

  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::MaskV::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  process( disparity.m_left ,  left );
  process( disparity.m_right, right );
  return true;
 }
