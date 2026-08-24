#include "opencv2/opencv.hpp"

#include "./disparity.hpp"
#include "./crosser.hpp"
#include "./cluster.hpp"
#include "./limiter.hpp"
#include "./too_far.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::Disparity::Disparity()
 {
  m_debug = false;
  m_iteration = 0;
  //m_dLm = 0.01;
  //m_trashCoordCount = 80;
 
 }

S_match::S_feature::S_disparity::Disparity::SizeType S_match::S_feature::S_disparity::Disparity::process( ImageType      & image )
 {
  auto start = std::chrono::system_clock::now();
  //std::cout<< __FUNCTION__<< "(" << __LINE__ << "):" << "start .." << std::endl;

  SizeType result = 0;
  if( 0 == m_left.layer().size() /* || ( m_left.layer().size() != m_right.layer().size() )*/)
   {
    return result;
   }
  SizeType width  = m_left.resolution()[0];
  SizeType height = m_left.resolution()[1];

  image.resolution( m_left.resolution(), ::color::constant::black_t{} );

   //for( SizeType y= 5; y < 45; ++ y )
  //for( SizeType y= 30; y < 90; ++ y )
  int y_step = 1;
  int scale = 1;
 //for( SizeType y = 25; y < 90; y += y_step )
 for( SizeType y = 0; y < height; y += y_step )
   {
    //if(  50 < y ) { y_step = 1; scale = 5; } if(  60 < y ) { y_step = 3; scale = 1; }
    //if( 135 < y ) { y_step = 1; scale = 5; } if( 155 < y ) { y_step = 3; scale = 1; }
    //if( 200 < y ) { y_step = 1; scale = 5; } if( 210 < y ) { y_step = 3; scale = 1; }
    //if( 390 < y ) { y_step = 1; scale = 5; } if( 420 < y ) { y_step = 3; scale = 1; }
    //if( 500 < y ) { y_step = 1; scale = 5; } if( 530 < y ) { y_step = 3; scale = 1; }
    for( SizeType x=0; x < width; ++ x )
     {
      image.set( { x, y }, gray_type( { 0 } ) );
     }

    this->square( y );

    //extern int g_option;
    auto       & entangler = m_entangler;

    entangler.global( m_square );
   S_match::S_feature::S_disparity::Limiter( (-0.5) * entangler.width(), 0 ).process( entangler );
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



S_match::S_feature::S_disparity::Disparity::SizeType S_match::S_feature::S_disparity::Disparity::process_restricted( ImageType      & image )
 {
  auto start = std::chrono::system_clock::now();  //std::cout<< __FUNCTION__<< "(" << __LINE__ << "):" << "start .." << std::endl;

  SizeType result = 0;
  if( 0 == m_left.layer().size() /* || ( m_left.layer().size() != m_right.layer().size() )*/)
   {
    return result;
   }
  SizeType width  = m_left.resolution()[0];
  SizeType height = m_left.resolution()[1];

  image.resolution( m_left.resolution(), ::color::constant::black_t{} );
  {  
   m_leftLineRestrict.resize( m_left.resolution()[0] );
   m_rightLineRestrict.resize( m_right.resolution()[0] );
   for( int x = 0; x < width; ++x )
    {
     m_leftLineRestrict[x].resize(  m_restriction.size() );
     m_rightLineRestrict[x].resize(  m_restriction.size() );
    }
  }

  int y_step = 1;
  int scale = 1;
 for( SizeType y = 0; y < height; y += y_step )
   {
    //if(  50 < y ) { y_step = 1; scale = 5; } if(  60 < y ) { y_step = 3; scale = 1; }
    //if( 135 < y ) { y_step = 1; scale = 5; } if( 155 < y ) { y_step = 3; scale = 1; }
    //if( 200 < y ) { y_step = 1; scale = 5; } if( 210 < y ) { y_step = 3; scale = 1; }
    //if( 390 < y ) { y_step = 1; scale = 5; } if( 420 < y ) { y_step = 3; scale = 1; }
    //if( 500 < y ) { y_step = 1; scale = 5; } if( 530 < y ) { y_step = 3; scale = 1; }
    for( SizeType x=0; x < width; ++ x )
     {
      image.set( { x, y }, gray_type( { 0 } ) );
     }

    this->square_restricted( y );

    //extern int g_option;
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
  m_left.clear(  );
  m_right.clear( );
  m_restriction.clear();
 }

bool S_match::S_feature::S_disparity::Disparity::append( LayerType const& left, LayerType const& right )
 {
  m_left.append( left );
  m_right.append( right );
  return true;
 }


S_match::S_feature::S_disparity::Disparity::ScalarType
S_match::S_feature::S_disparity::Disparity::square( SizeType const& lineno )
 {
  ScalarType max = 0;

  m_left.get( m_leftLine, lineno );
  m_right.get( m_rightLine, lineno );
  m_square.process( m_leftLine, m_rightLine );

  return max;
 }

void S_match::S_feature::S_disparity::Disparity::prepare_cube()
 {
  SizeType width   = m_left.resolution()[0];
  SizeType height  = m_left.resolution()[1];

  m_cube.resize( height );
  for( SizeType y = 0; y < height; ++y )
   {
    m_cube[ y ].process( y, m_left, m_right );
   }
 }


void
S_match::S_feature::S_disparity::Disparity::square_cube( SizeType const& lineno )
 {
  SizeType width  =  m_left.resolution()[0];
  SizeType height = m_right.resolution()[0];

  auto & cube = m_cube[lineno];

  for( SizeType L = 0; L < width; ++L )
   {
    auto H = std::min( L, height )+1;
    for( SizeType R = 0; R < H; ++R )
     {
      auto d =  cube.distance( m_restriction, L, R ) / m_restriction.size();
      m_square.set( { L, R }, d );
      m_square.set( { R, L }, d );
     }
   }
 }

void
S_match::S_feature::S_disparity::Disparity::square_restricted( SizeType const& lineno )
 {
  restriction( m_leftLineRestrict,  m_left,  lineno );
  restriction( m_rightLineRestrict, m_right, lineno );

  m_square.process( m_leftLineRestrict, m_rightLineRestrict );
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

S_match::S_feature::S_disparity::Disparity::RestrictionType const& S_match::S_feature::S_disparity::Disparity::restriction()const
 {
  return m_restriction;
 }

bool S_match::S_feature::S_disparity::Disparity::restriction( RestrictionType const& r )
 {
  m_restriction = r;
  return true;
 }


void S_match::S_feature::S_disparity::Disparity::restriction( LineType &line, LasagnaType const& lasagna, SizeType const& lineno )const
 {  
  for( int x = 0; x < line.size(); ++x )
   {
    for( int index = 0; index < m_restriction.size(); ++index )
     {
      line[x][index] = lasagna.get( { (std::size_t)x, lineno, m_restriction[index] } );
     }
   }
 }

