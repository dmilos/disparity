#include "opencv2/opencv.hpp"

#include "./windowc.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::S_Stacker::WindowC::WindowC( Size2DType const& size )
 {
  m_debug = false;
  m_size = size;
 }


bool S_match::S_feature::S_disparity::S_Stacker::WindowC::process( LasagnaType &lasagna, ImageType const& image )const
 {
  if( true == m_debug )std::cout << PREFIX << "RGB ..." << std::endl;

  SizeType width = image.resolution()[0];
  SizeType height = image.resolution()[1];
  SizeType offset = lasagna.layer().size();

  lasagna.layer().resize( offset + 3*m_size[0]*m_size[1] );

  auto R = rand();

  double scale = 1.0;// /( m_size[0] * m_size[1] );

  for( SizeType index=0; index < m_size[0]*m_size[1]; ++index )
   {
    auto & layerR = lasagna.layer()[ offset + 3*index + 0 ];
    auto & layerG = lasagna.layer()[ offset + 3*index + 1 ];
    auto & layerB = lasagna.layer()[ offset + 3*index + 2 ];

    layerR.resolution( image.resolution() );
    layerG.resolution( image.resolution() );
    layerB.resolution( image.resolution() );

    int xo =( (int)index % (int)m_size[0] ) -  (int)m_size[0]/2;
    int yo =( (int)index / (int)m_size[1] ) -  (int)m_size[1]/2;

    for( int y=0; y < height; ++y )
     for( int x=0; x < width; ++x )
      {
       layerR.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
       layerG.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );
       layerB.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { 0 } ) );

       auto X = x + xo; if( X < 0 ) continue;  if( width  <= X ) continue;
       auto Y = y + yo; if( Y < 0 ) continue;  if( height <= Y ) continue;
       auto const& c = image.get( { (SizeType)X, (SizeType)Y } );

       layerR.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { scale * c[0] } ) );
       layerG.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { scale * c[1] } ) );
       layerB.set( { (SizeType)x,(SizeType)y }, color::model<color::category::gray_double> ( { scale * c[2] } ) );
      }

    //graphics::image::save( "layer-Chroma" + std::to_string( R )+"_"+ std::to_string( index )+ "_" + std::to_string( 0 ) +".png", layerR ); 
    //graphics::image::save( "layer-Chroma" + std::to_string( R )+"_"+ std::to_string( index )+ "_" + std::to_string( 1 ) +".png", layerG ); 
    //graphics::image::save( "layer-Chroma" + std::to_string( R )+"_"+ std::to_string( index )+ "_" + std::to_string( 2 ) +".png", layerB ); 
   }

  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::WindowC::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  process( disparity.m_left , left );
  process( disparity.m_right, right );
  return true;
 }

