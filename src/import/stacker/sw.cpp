#include "opencv2/opencv.hpp"
#include "./sw.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"
#define MY_DEBUG 0

S_match::S_feature::S_disparity::S_Stacker::SupportWeight::SupportWeight(  Size2DType const & size )
 {
  m_debug = false;

  extern int g_offset0;
  extern int g_offset1;
  extern int g_offset2;

  m_size = size;          //  1     2     3     4     5    6      7     8     9   10   11     12    13   14   15
  m_gammaC = 19;          //                         31    25    21    18    18   19   19
  m_gammaP = g_offset1*3;   //                                              24*3
 }

bool S_match::S_feature::S_disparity::S_Stacker::SupportWeight::process( LasagnaType &lasagna, ImageType const& image )const
 {
  SizeType width = image.resolution()[0];
  SizeType height = image.resolution()[1];
  SizeType offset = lasagna.layer().size();

  int W = (int)m_size[0];
  int H = (int)m_size[1];
  int total = (2*W+1)*(2*H+1) * 4;
  lasagna.layer().resize( offset +  total  );
  for( SizeType index=0; index < total; ++index )
   {
    auto & layer = lasagna.layer()[ offset + index ];
    layer.resolution( image.resolution(), color::gray<double>({0}) );
   }
#if 1 == MY_DEBUG
   /*debug*/::graphics::image::rgb_double_t maskC{ {2*(SizeType)W+1,2*(SizeType)H+1}, color::rgb<double>({0,0,0}) };
   /*debug*/::graphics::image::rgb_double_t maskW{ {2*(SizeType)W+1,2*(SizeType)H+1}, color::rgb<double>({0,0,0}) };
#endif

  for( int y=0; y < height; ++y )
   {
    for( int x=0; x < width; ++x )
     {

#if 1 == MY_DEBUG
        /*debug*/ if( ( ( 70 < x ) && ( x < 80 ) ) && ( 30 == y ) ) { m_debug = true; } else { m_debug = false; }
#endif
      color::lab<double>  C; C = image.get( {(SizeType)x,(SizeType)y} );

      for( int yP = -H; yP < H+1; yP++ )
       for( int xP = -W; xP < W+1; xP++ )
        {
         int index = (yP+H)*(2*W+1) + (xP+W);

         auto & layer_W = lasagna.layer()[ offset + 4*index + 0 + 0 ] ;
         auto & layer_r = lasagna.layer()[ offset + 4*index + 1 + 0 ];
         auto & layer_g = lasagna.layer()[ offset + 4*index + 1 + 1 ];
         auto & layer_b = lasagna.layer()[ offset + 4*index + 1 + 2 ];

         int xR = x + xP;   
         int yR = y + yP;    
         double weight = 1;
         double r   = 0;
         double g   = 0;
         double b   = 0;
         double difference = 1;
         double spatial = 1;

         if( ( xR < 0 ) || ( yR < 0 ) || ( width <= xR )|| ( height <= yR ) )
          {
          }
         else
          {
           color::lab<double> c;  c = image.get( { (SizeType)xR, (SizeType)yR } );
           difference = color::operation::distance( C, c );
           difference /= m_gammaC;
           spatial = sqrt( xP*xP + yP*yP );
           spatial /= m_gammaP;

           weight =  exp( - (  difference + spatial ) );

           r = image.get( { (SizeType)xR, (SizeType)yR } )[0];  
           g = image.get( { (SizeType)xR, (SizeType)yR } )[1];
           b = image.get( { (SizeType)xR, (SizeType)yR } )[2];

           //r = ::math::function::ramp( ::color::get::red<   ::color::get::constant::rgb::red::hsl_star_entity   >( image.get( { (SizeType)xR, (SizeType)yR } ) ) ); 
           //g = ::math::function::ramp( ::color::get::green< ::color::get::constant::rgb::green::hsl_star_entity >( image.get( { (SizeType)xR, (SizeType)yR } ) ) ); 
           //b = ::math::function::ramp( ::color::get::blue<  ::color::get::constant::rgb::blue::hsl_star_entity  >( image.get( { (SizeType)xR, (SizeType)yR } ) ) ); 
           //
           //r = c[0] / 100.0; 
           //g = c[1] / 100.0; 
           //b = c[2] / 100.0; 
          }
        
         layer_W.set( { (SizeType)x,(SizeType)y }, color::gray<double> ( { weight } ) );
         layer_r.set( { (SizeType)x,(SizeType)y }, color::gray<double> ( { r } ) ); 
         layer_g.set( { (SizeType)x,(SizeType)y }, color::gray<double> ( { g } ) ); 
         layer_b.set( { (SizeType)x,(SizeType)y }, color::gray<double> ( { b } ) ); 
#if 1 == MY_DEBUG
            /*debug*/ if( true == m_debug ) { maskW.set( { (SizeType)(xP+W), (SizeType)(yP+H) }, color::rgb<double> ( { difference, weight, spatial } ) ); };
            /*debug*/ if( true == m_debug ) { maskC.set( { (SizeType)(xP+W), (SizeType)(yP+H) }, color::rgb<double> ( { r,g,b } )  ); };
#endif
        }

#if 1 == MY_DEBUG
      /*debug*/if( true == m_debug ) graphics::image::save( "mask_" + m_side + "_"+ std::to_string(y)  +"-"+ std::to_string(x) +"_C"+ ".png", maskC );
      /*debug*/if( true == m_debug ) graphics::image::save( "mask_" + m_side + "_"+ std::to_string(y)  +"-"+ std::to_string(x) +"_W"+ ".png", maskW );
#endif
     }
   }

  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::SupportWeight::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  m_side = "L"; process( disparity.m_left ,  left );
  m_side = "R"; process( disparity.m_right, right );
  return true;
 }
