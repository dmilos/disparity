#include "opencv2/opencv.hpp"

#include "./lasagna.hpp"
#include "./crosser.hpp"
#include "./cluster.hpp"
#include "./too_far.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::Lasagna::Lasagna()
 {
  m_debug = false;
  //m_trash = 10;
 }

S_match::S_feature::S_disparity::Lasagna::SizeType
S_match::S_feature::S_disparity::Lasagna::depth() const
 {
  return m_container.size();
 }

S_match::S_feature::S_disparity::Lasagna::Size2DType const&
S_match::S_feature::S_disparity::Lasagna::resolution() const
 {
  if( 0 == m_container.size() )
   {
    static Size2DType s_result{0,0};
    return s_result;
   }
  return m_container[0].resolution();
 }

void S_match::S_feature::S_disparity::Lasagna::clear(  )
 {
  m_container.clear();
 }
 
bool S_match::S_feature::S_disparity::Lasagna::append( LayerType const& layer )
 {
  if( 0 != m_container.size() )
   {
    if( layer.resolution() != m_container[0].resolution() )
     {
      return false;
     }
   }
  m_container.push_back( layer );
  return true;
 }

bool S_match::S_feature::S_disparity::Lasagna::get( FeatureType &feature, Size2DType const& coord )const
 {
  feature.resize( m_container.size() );

  for( SizeType index=0; index < m_container.size(); ++index )
   {
    feature[ index ] = m_container[index].get( coord ).get<0>();
   }
  return true;
 }

S_match::S_feature::S_disparity::Lasagna::ScalarType
S_match::S_feature::S_disparity::Lasagna::get( Size3DType const& coord )const
 {
  if( coord[2] < m_container.size() )
   {
    return m_container[coord[2]].get( { coord[0], coord[1] } ).get<0>();
   }

  return 0;
 }

bool S_match::S_feature::S_disparity::Lasagna::get( LineType &line, SizeType const& y )const
 {
  auto width = resolution()[0];
  line.resize( width );

  for( SizeType x=0; x < width; ++x )
   {
    get( line[x], {x,y} );
   }
  return true;
 }


bool       S_match::S_feature::S_disparity::Lasagna::set( Size3DType const& coord, ScalarType const& v )
 {
  return set( coord[0], coord[1], coord[2], v );
 }

bool       S_match::S_feature::S_disparity::Lasagna::set( Size2DType const& coord, SizeType const& level, ScalarType const& v ) 
 {
  return set( level, coord[0], coord[1], v );
 }

bool       S_match::S_feature::S_disparity::Lasagna::set( SizeType const& x, SizeType const& y, SizeType const& level, ScalarType const& v )
 {
  if( m_container.size() <= level )
   {
    return false;
   }
   m_container[level].set( { x, y }, color::gray<ScalarType>( { v } )  );
  return true;
 }
