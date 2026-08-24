#include "opencv2/opencv.hpp"

#include "./base.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::Disparity::Disparity()
 {
  m_debug = false;
  m_iteration = 2;
 }

S_match::S_feature::S_disparity::Disparity::SizeType
S_match::S_feature::S_disparity::Disparity::process( ImageGrayType  & image, ImageRGBType const& left, ImageRGBType const& right )
 {
  auto start = std::chrono::system_clock::now();
  //std::cout<< __FUNCTION__<< "(" << __LINE__ << "):" << "start .." << std::endl;

  SizeType result = 0;
  SizeType width  = m_left.resolution()[0];
  SizeType height = m_left.resolution()[1];

  image.resolution( m_left.resolution(), ::color::constant::black_t{} );

 for( SizeType y = 0; y < height; y += 1 )
   {
    for( SizeType x=0; x < width; ++ x )
     {
      image.set( { x, y }, gray_type( { 0 } ) );
     }

    this->square( y );

    auto       & entangler = m_entangler;

    entangler.global( m_square );
    //S_match::S_feature::S_disparity::Crosser( 0 ).process( entangler );
    // //S_match::S_feature::S_disparity::Cluster( 1, 3 ).processL( entangler );

   for( int i=0; i < m_iteration; ++i )
    {
     entangler.local( m_square );
     //S_match::S_feature::S_disparity::Crosser( 0 ).process( entangler );
     //S_match::S_feature::S_disparity::Cluster( 1, 3 ).processL( entangler );
    }

    result += scale * this->process( image, y );
   }

  auto stop = std::chrono::system_clock::now();
  //std::cout<< __FUNCTION__<< "(" << __LINE__ << "):" << std::chrono::duration_cast< std::chrono::duration<double> >(stop-start).count() << "s" << std::endl;

  return result;
 }


void S_match::S_feature::S_disparity::Disparity::clear()
 {
 }


S_match::S_feature::S_disparity::Disparity::ScalarType
S_match::S_feature::S_disparity::Disparity::square( SizeType const& lineno )
 {
  ScalarType max = 0;
  SizeType width = m_square.resolution()[0];
   m_square.resolution( { width, width } )
  for( SizeType y=0; y < width; ++y )
   for( SizeType x=0; x < width; ++x )
   {
    // value = distance.process(  )
    m_square.set( {x,y}, value );
   }

  return max;
 }

S_match::S_feature::S_disparity::Disparity::SizeType
S_match::S_feature::S_disparity::Disparity::process( ImageType      & image, SizeType const& y )
 {
  SizeType result = 0;
  SizeType width = m_square.resolution()[0];

  for( SizeType L=0; L < width; ++ L )
   {
    auto const& R = m_entangler.getR( L );
    if( L != m_entangler.getL( R ) )
     {
      image.set( { L, y }, gray_type( { 0 } ) );
      continue;
     }
    ScalarType delta = ScalarType( R ) - ScalarType( L );
    image.set( { L, y }, gray_type( { delta } ) );
    ++result;
   }
  return result;
 }

S_match::S_feature::S_disparity::Disparity::SizeType
S_match::S_feature::S_disparity::Disparity::evaluate()const
 {
  SizeType width = m_square.resolution()[0];

  SizeType result = 0;
  for( SizeType L = 0; L < width; ++L )
   {
    if( true == m_entangler.tieL( L ) )
     {
      ++ result;
     }
   }
  return result;
 }
