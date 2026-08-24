#include "too_far.hpp"

#include <iostream>
#include <iomanip>



S_match::S_feature::S_disparity::TooFar::TooFar( ScalarType const& epsilon  )
 : m_epsilon( epsilon )
 {
 }

S_match::S_feature::S_disparity::TooFar::SizeType
S_match::S_feature::S_disparity::TooFar::process( EntanglerType & entangler, SquareType const& square )
 {
  ::math::statistic::average<> average;
  auto width = square.resolution()[0];
  for( SizeType L=0; L < width; ++L )
   {
    if( false == entangler.tieL( L ) )
     {
      continue;
     }
    auto R = entangler.getR( L );

    average.push( square.get( { L, R } ) );
   }
  ::math::statistic::average<> right;
  for( SizeType L=0; L < width; ++L )
   {
    if( false == entangler.tieL( L ) )
     {
      continue;
     }
    auto R = entangler.getR( L );

    auto value = square.get( { L, R } );
    if( average.value( ) < value )
     {
      right.push( value );
     }
   }
  SizeType result = 0;
  for( SizeType L=0; L < width; ++L )
   {
    if( false == entangler.tieL( L ) )
     {
      continue;
     }
    auto R = entangler.getR( L );

    auto value = square.get( { L, R } );
    if( right.value( ) < value )
     {
      entangler.spoilR( L );
      ++result;
     }
   }

  return result;
 }
