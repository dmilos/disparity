#include "crosser.hpp"

#include <iostream>
#include <iomanip>

S_match::S_feature::S_disparity::Crosser::Crosser( SizeType const& tolerance )
 {
  m_tolerance = tolerance;
 }

S_match::S_feature::S_disparity::Crosser::SizeType
S_match::S_feature::S_disparity::Crosser::process( ImageType  & image  )
 {
  SizeType height0 = image.resolution()[1];

  SizeType result=0;
  for( SizeType y=0 ; y < height0; ++y  )
   {
    result += process( image, y );
   }
  return result;
 }

S_match::S_feature::S_disparity::Crosser::SizeType
S_match::S_feature::S_disparity::Crosser::process( ImageType  & image, SizeType const& y )
 {
  SizeType result = 0;
  SizeType width = image.resolution()[0];

  while( true )
   {
    SizeType worst_x = 0;
    SizeType worst_value = process( image, 0, y );
    for( SizeType x= 1 ; x < width; ++x )
     {
      auto current_value = process( image, x, y );
      if( current_value < worst_value )
       {
        continue;
       }

      worst_x = x;
      worst_value = current_value;
     }

    if( m_tolerance < worst_value )
     {
      image.set( {worst_x,y }, gray_type({0}) );
      ++result;
      continue;
     }
    break;
   }

  return result;
 }

S_match::S_feature::S_disparity::Crosser::SizeType
S_match::S_feature::S_disparity::Crosser::process( ImageType const& image, SizeType const& x, SizeType const& y )
 {
  SizeType result = 0;
  SizeType width0 = image.resolution()[0];

  ScalarType move = image.get( {x,y } )[0];
  if( 0 == move )
   {
    return result ;
   }

  SizeType source = x;
  SizeType right = x + (SizeType)move;
  for( SizeType index = 0  ; index < x ; ++index )
   {
    ScalarType current = image.get( { index, y } )[0];

    if( 0 == current )
     {
      continue;
     }

    if( current + index < right )
     {
      continue;
     }
    ++result;
   }

  for( SizeType index = x+1  ; index < width0; ++index )
   {
    ScalarType current = image.get( { index, y } )[0];

    if( 0 == current )
     {
      continue;
     }

    if( right < current + index )
     {
      continue;
     }
    ++result;
   }

  return result;
 }

S_match::S_feature::S_disparity::Crosser::SizeType 
S_match::S_feature::S_disparity::Crosser::process( EntanglerType & entangler )
 {
  SizeType result = 0;
  while( true )
   {
    SizeType worstL_index = 0;
    SizeType worstL_value = 0;
    for( SizeType L = 0; L < entangler.width(); ++L )
     {
      auto current_value = degree( L, entangler );
      if( worstL_value < current_value )
       {
        worstL_index = L;
        worstL_value = current_value;
       }
     }
    if( m_tolerance < worstL_value )
     {
      auto const& R = entangler.getR( worstL_index );
      entangler.spoilR( worstL_index );
      entangler.spoilL( R );
      ++result;
      continue;
     }
    break;
   }
  return result;
 }

S_match::S_feature::S_disparity::Crosser::SizeType 
S_match::S_feature::S_disparity::Crosser::degree(  SizeType const& L, EntanglerType const& entangler )
 {
  SizeType result = 0;
  if( false == entangler.tieL( L ) )
   {
    return 0;
   }

  SizeType R = entangler.getR( L );

  for( SizeType l = L+1 ; l < entangler.width(); l++ )
   {
    if( false == entangler.tieL( l ) )
     {
      continue;
     }
    auto r = entangler.getR( l );
    if( r < R )
     {
      ++result;
     }
   }

  for( SizeType r = R+1 ; r < entangler.height(); r++ )
   {
    if( false == entangler.tieR( r ) )
     {
      continue;
     }
    auto l = entangler.getL( r );
    if( l < L )
     {
      ++result;
     }
   }

  return result;
 }
