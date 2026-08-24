#include "opencv2/opencv.hpp"

#include "./segmentationcq.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::S_Stacker::SegmentationCQ::SegmentationCQ( SizeType const& size )
 {
  m_debug = false;

  m_size = size;
  m_factor = 0.98;
 }


bool S_match::S_feature::S_disparity::S_Stacker::SegmentationCQ::process( LasagnaType &lasagna, ImageType const& image )const
 {
  if( true == m_debug )std::cout << PREFIX << "RGB ..." << std::endl;

  SizeType width = image.resolution()[0];
  SizeType height = image.resolution()[1];
  SizeType offset = lasagna.layer().size();

  lasagna.layer().resize( offset + 1 );

   {
    auto & layer = lasagna.layer().back();

    layer.resolution( image.resolution() );

    for( SizeType y=0; y < height; ++y )
     for( SizeType x=0; x < width; ++x )
      {
       auto const& c =  image.get( { x,y } );
       ScalarType v =      (ScalarType) int( c[0] * ( m_size -1) )
                        +  (ScalarType) int( c[1] * ( m_size -1) ) * m_size
                        +  (ScalarType) int( c[2] * ( m_size -1) ) * m_size * m_size;
        v /=  m_size * m_size * m_size;

       layer.set( { x,y }, color::model<color::category::gray_double> ( { v } ) );
      }

   }

  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::SegmentationCQ::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  process( disparity.m_left , left  );
  process( disparity.m_right, right );
  return true;
 }

