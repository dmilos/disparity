#include "noise.hpp"

#include <iostream>
#include <iomanip>

S_match::S_feature::S_disparity::Noise::Noise()
 {
  m_zero = color::constant::black_t{};
 }

S_match::S_feature::S_disparity::Noise::SizeType
S_match::S_feature::S_disparity::Noise::process( ImageType  & target, ImageType  const& source )const
 {
  SizeType height0 = source.resolution()[1];
  SizeType height1 = height0 - 1;
  SizeType width0 = source.resolution()[0];
  SizeType width1 = width0 - 1;

  SizeType result = 0;

  for( int Y=1 ; Y < height1; ++Y  )
   {
    for( int X=1 ; X < width1; ++X  )
     {
      ScalarType M = m_zero.get<0>();
      ScalarType m = m_zero.get<0>();

      auto const& p = source.get( { (SizeType) X , (SizeType)Y } );
      target.set( { (SizeType)X , (SizeType)Y }, p );

      if( m_zero == p ) continue;

      for( int y=-1 ; y < +1; ++y  )
       {
        for( int x=-1 ; x < +1; ++x  )
         {
          if( ( 0 == x ) && ( 0 == y ) ) continue;
          auto const& p = source.get( {(SizeType)(X+x),(SizeType)(Y+y)} );
          if( p == m_zero ) continue;
          M = std::max( M, p.get<0>() );
          m = std::min( m, p.get<0>() );
         }
       }
      if( m_zero.get<0>() == M )continue;

      if( ( m <= p.get<0>() ) && ( p.get<0>() < M ) )
       {
        continue;
       }
      target.set( { (SizeType)X , (SizeType)Y }, m_zero );
      ++result;
     }
   }

  return result;
 }
/*
S_match::S_feature::S_disparity::Noise::SizeType
S_match::S_feature::S_disparity::Noise::processX( ImageType  & image  )
 {
  SizeType result =0;
  return result;
 }

S_match::S_feature::S_disparity::Noise::SizeType
S_match::S_feature::S_disparity::Noise::processY( ImageType  & image  )
 {
  SizeType result =0;
  return result;
 }
*/