#include "opencv2/opencv.hpp"
#include "./maskf.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"
#define MY_DEBUG 0

S_match::S_feature::S_disparity::S_Stacker::MaskF::MaskF( ExtractorType const& extractor, Size2DType const & size, ScalarType const & trash )
 {
  m_debug = true;
  m_size = size;
  m_trash = trash;
  m_extractor = extractor;
 }

bool S_match::S_feature::S_disparity::S_Stacker::MaskF::process( LasagnaType &lasagna, ImageType const& image )const
 {
  //if( true == m_debug )std::cout << PREFIX << "MaskF ..." << std::endl;

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
      for( SizeType index=0; index < m_size[0]*m_size[1]; ++index )
       {
        int xo =( (int)index %  (int)m_size[0] ) -  (int)m_size[0]/2;
        int yo =( (int)index /  (int)m_size[1] ) -  (int)m_size[1]/2;
        auto & layer = lasagna.layer()[ offset + index ];

        auto X = x + xo; if( X < 0 ) continue; if( width  <= X ) continue;
        auto Y = y + yo; if( Y < 0 ) continue; if( height <= Y ) continue;
        auto const c = m_extractor( image.get( { (SizeType)X, (SizeType)Y } ) );
        double distance = fabs( c - C ) ;
        if( distance < m_trash )
         {
          double weight = 1;
                 //weight  = 1 - distance;
                 //weight  = 1 - sqrt( xo*xo+yo*yo )/( m_size/2 ); 
                  //weight = math::function::any_to_any<ScalarType>( weight, 0, (ScalarType)m_size/2, 1, 0 ); if( weight < 0 ) weight = 0;
                 //weight = exp( - weight*weight );
                 //weight  = 1 - distance/m_trash;
                 //weight = 1;
          layer.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { weight * c  } ) );
#if 1 == MY_DEBUG
           /*debug*/if( true == m_debug ){ maskW.set( { xo + m_size[0]/2, yo + m_size[1]/2 }, color::rgb<double>( { weight,weight,weight } ) ); };
           /*debug*/if( true == m_debug ){ maskC.set( { xo + m_size[0]/2, yo + m_size[1]/2 }, color::rgb<double>( { weight*c[0],weight*c[1],weight*c[2] } ) ); };
#endif
         }
        else
         {
          layer.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
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

bool S_match::S_feature::S_disparity::S_Stacker::MaskF::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  process( disparity.m_left ,  left );
  process( disparity.m_right, right );
  return true;
 }
