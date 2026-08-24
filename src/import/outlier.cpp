#include "outlier.hpp"

#include <iostream>
#include <iomanip>

S_match::S_feature::S_disparity::OutLier::OutLier( ScalarType const& trash  )
 : m_trash( trash )
 {
 }

S_match::S_feature::S_disparity::OutLier::SizeType
S_match::S_feature::S_disparity::OutLier::process( ImageType  & image  )
 {
  SizeType height0 = image.resolution()[1];

  SizeType result=0;
  for( SizeType y=0 ; y < height0; ++y  )
   {
    result += process( image, y );
   }
  return result;
 }

S_match::S_feature::S_disparity::OutLier::SizeType 
S_match::S_feature::S_disparity::OutLier::process( ImageType  & image, SizeType const& y )
 {
  SizeType width0 = image.resolution()[0];
  m_direction.set( -1, 1, 0 );
  process( m_direction,  width0 * ScalarType(2), image, y );
  process( m_direction, m_trash * ScalarType(2), image, y );

  int critical = 110;

   if( critical == y ) std::cout <<"-------------------{{{{{{{" << std::endl;
  SizeType result=0;
  ScalarType trash =  width0 * m_trash;
  for( SizeType x=0; x < width0; ++x )
   {
    auto & value = image.get( { x, y } ).get<0>();
    if( 0 == value )
     {
      if( critical == y ){ std::cout << -1 << std::endl; }
      continue;
     }

    Scalar2DType point{ (ScalarType)x , (ScalarType)x+ value }; 
    auto d = ::math::geometry::direction::distance( m_direction, point );
    if( critical == y ){ std::cout << d << std::endl; }
    if( d < trash )
     {
      continue;
     }
     ++result;
     image.set( {x,y}, gray_type({0}) );
   }
   if( critical == y ) std::cout << "}}}}}}--------------------" << std::endl;

  return result;
 }

S_match::S_feature::S_disparity::OutLier::SizeType
S_match::S_feature::S_disparity::OutLier::process( direction_type & direction, ScalarType const& trash, ImageType  const& image, SizeType const& y )
 {
  SizeType width0 = image.resolution()[0];
  ::math::statistic::average<ScalarType,1>   average_r;
  ::math::statistic::average<ScalarType,1>   average_a;

  for( SizeType x=0; x < width0; ++x )
   {
    auto const& value = image.get( { x, y } ).get<0>();
    if( 0 == value )
     {
      continue;
     }
    Scalar2DType point{ (ScalarType)x , (ScalarType)x+ value }; 
    auto d = ::math::geometry::direction::distance( direction, point );
    average_a.push( d );
    if( trash < d )
     {
      continue;
     }
    average_r.push( d );
    m_cloud.push_back( point );
   }
  //std::cout << "r: " << average_r.value() << std::endl;
  //std::cout << "A: " << average_a.value() << std::endl;

  ::math::geometry::direction::fit2D<ScalarType>::process( direction, m_cloud );
  direction.normalize();
  return width0 - m_cloud.size();
 }
