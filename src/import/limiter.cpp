#include "./limiter.hpp"

#include <iostream>
#include <iomanip>

S_match::S_feature::S_disparity::Limiter::Limiter( ScalarType const& left, ScalarType const& right )
 {
  m_LimitLeft  = left;
  m_LimitRight = right;
 }

S_match::S_feature::S_disparity::Limiter::SizeType
S_match::S_feature::S_disparity::Limiter::process( EntanglerType & entangler )
 {
  SizeType result = 0;

  for( SizeType L = 0; L < entangler.width(); ++L )
   {

    if( false == entangler.tieL( L ) )
     {
      continue;
     }

    int R = (int)entangler.getR( L );
    int D = R - (int)L;
    if( D < m_LimitLeft )
     {
      entangler.spoilR( L );
      entangler.spoilL( R );
      continue;
     }
    if( m_LimitRight < D )
     {
      entangler.spoilR( L );
      entangler.spoilL( R );
      continue;
     }

   }

  return result;
 }
