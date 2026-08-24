#include "opencv2/opencv.hpp"
#include "./maskc.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

#define MY_DEBUG  0

S_match::S_feature::S_disparity::S_Stacker::MaskC::MaskC( Size2DType const & size, ScalarType const & trash  )
 {
  m_debug = true;
  m_size = size;
  m_trash = trash;
  m_trashGray = 16/256.0; 
  m_trashRGB  = 16/256.0; 
 }

bool S_match::S_feature::S_disparity::S_Stacker::MaskC::process( LasagnaType &lasagna, ImageType const& image )const
 {
  //if( true == m_debug )std::cout << PREFIX << "MaskC ..." << std::endl;
#if 1 == MY_DEBUG
 graphics::image::save( "the_image-maskc-" + m_side + ".png", image );
#endif


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
      ::color::hsl<double>   Chsl { C };

      double xC = 1 * cos( math::geometry::deg2rad( Chsl[0] ) ) * Chsl[1] * ( 100 - fabs( 100 - Chsl[2] ) )/ (100*50);
      double yC = 1 * sin( math::geometry::deg2rad( Chsl[0] ) ) * Chsl[1] * ( 100 - fabs( 100 - Chsl[2] ) )/ (100*50);

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

        double distanceE = color::operation::distance( c, C ) / sqrt(3);            int pass_RGB  = 0; if( distanceE < 0 ) pass_RGB  = -1; if( m_trashRGB  < distanceE ) pass_RGB  = +1; 
        double distanceG = fabs( color::get::gray( c ) - color::get::gray( C ) ) ;  int pass_Gray = 0; if( distanceG < 0 ) pass_Gray = -1; if( m_trashGray < distanceG ) pass_Gray = +1;
        if( ( +1 == pass_Gray ) || ( +1 == pass_RGB ) )
         {
          layerR.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
          layerG.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
          layerB.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
#if 1 == MY_DEBUG
            /*debug*/ if( true == m_debug ) { maskW.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, ::color::constant::black_t{} ); };
            /*debug*/ if( true == m_debug ) { maskC.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, ::color::constant::black_t{} ); };
#endif
          continue;
         }

        ::color::hsl<double>   chsl { c };
        // (bicone)
        double xc = cos( math::geometry::deg2rad( chsl[0] ) ) * chsl[1] * ( 100 - fabs( 100 - chsl[2] ) ) / (100*50);
        double yc = sin( math::geometry::deg2rad( chsl[0] ) ) * chsl[1] * ( 100 - fabs( 100 - chsl[2] ) ) / (100*50);
        double distanceHLS = sqrt( ( xc - xC )*( xc - xC ) +  ( yc - yC )*( yc - yC ) );

        if(  distanceHLS < m_trash )
         {
          double weight = 1;
                 //weight *= distanceHLS;
                 //weight *= 1 - sqrt( xo*xo+yo*yo )/( m_size/2 ); 
                  //weight = math::function::any_to_any<ScalarType>( weight, 0, (ScalarType)m_size/2, 1, 0 ); if( weight < 0 ) weight = 0;
                 //weight = exp( - weight*weight );
                 //weight *= 1 - distance/m_trash;
                 //weight = 1;
          layerR.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { c[0] } ) );
          layerG.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { c[1] } ) );
          layerB.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { c[2] } ) );
#if 1 == MY_DEBUG
            /*debug*/if( true == m_debug ){ maskW.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, color::rgb<double>( { weight,weight,weight } ) ); };
            /*debug*/if( true == m_debug ){ maskC.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, color::rgb<double>( { c[0],c[1],c[2] } ) ); };
#endif
         }
        else
         {
          layerR.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
          layerG.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
          layerB.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
#if 1 == MY_DEBUG
            /*debug*/ if( true == m_debug ) { maskW.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, ::color::constant::black_t{} ); };
            /*debug*/ if( true == m_debug ) { maskC.set( { (std::size_t)(xo +(int)m_size[0]/2) , (std::size_t)( yo+(int)m_size[1]/2) }, ::color::constant::black_t{} ); };
#endif
         }
       }

#if 1 == MY_DEBUG
        std::stringstream ss; ss << std::setfill('0')<< std::setw(3)<< x << "x" << std::setw(3) << y; 
        
        /*debug*/if( true == m_debug ) graphics::image::save( "mask_" + m_side + "_C" + ss.str() + ".png", maskC );
        /*debug*/if( true == m_debug ) graphics::image::save( "mask_" + m_side + "_W" + ss.str() + ".png", maskW );
#endif
     }
   }
  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::MaskC::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  m_side = "L"; process( disparity.m_left ,  left );
  m_side = "R"; process( disparity.m_right, right );
  return true;
 }
