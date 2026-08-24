#include "fence.hpp"

#include <iostream>
#include <iomanip>

S_match::S_feature::S_disparity::Fence::Fence( SizeType const& length )
 {
  m_lenght   = length;
 }

S_match::S_feature::S_disparity::Fence::SizeType
S_match::S_feature::S_disparity::Fence::processL( EntanglerType & entangler )
 {
  SizeType result = 0;
  auto const width = entangler.width();

  for( SizeType L = 0; L < entangler.width(); ++L )
   {
    auto chunkLR= searchL( L, entangler );
    if( 0 == chunkLR.second )
     {
      return result;
     }
    ++result;
    //auto R = entangler.getR( L );
    //if( 0 != R )
    // {
    //  auto chunkLRL_size = measureRL( R-1, entangler );
    //
    //  if( ( m_lenght <= chunkLR.second ) && ( m_lenght <= chunkLRL_size ) )
    //   {
    //    entangler.untieL( L )
    //   }
    // }
   }

  return result;
 }

S_match::S_feature::S_disparity::Fence::SizeType
S_match::S_feature::S_disparity::Fence::processR( EntanglerType & entangler )
 {
  return 0;
 }

S_match::S_feature::S_disparity::Fence::ChunkType
S_match::S_feature::S_disparity::Fence::searchL( SizeType const& beginL, EntanglerType const& entangler )
 {
  ChunkType result{ beginL, 0 };
  auto const width = entangler.width();
  for( /*empty*/; result.first < width; ++result.first  )
   {
    if( true == entangler.tieL( result.first ) )
     {
      continue;
     }
    result.second = 1;
    auto tail = result.first+1;

    for( /*empty*/; tail < width; ++tail )
     {
      if( true == entangler.tieL( tail ) )
       {
        return result;
       }
      ++result.second;
     }
   }
  return result;
 }

S_match::S_feature::S_disparity::Fence::SizeType 
S_match::S_feature::S_disparity::Fence::measureLL( SizeType  beginL, EntanglerType const& entangler )
 {
  SizeType result = 0;
  
  while( true )
   {
    if( true == entangler.tieL( beginL ) )
     {
      return result;
     }
    ++result;
    if( 0 ==  beginL )
     {
      return result;
     }
    --beginL;
   }
  return result;
 }

S_match::S_feature::S_disparity::Fence::SizeType 
S_match::S_feature::S_disparity::Fence::measureLR( SizeType  beginL, EntanglerType const& entangler )
 {
  SizeType result = 0;
  auto width = entangler.width();
  for( ;beginL < width; ++beginL )
   {
    if( true == entangler.tieL( beginL ) )
     {
      return result;
     }
    ++result;
   }
  return result;
 }

S_match::S_feature::S_disparity::Fence::SizeType 
S_match::S_feature::S_disparity::Fence::measureRL( SizeType  beginR, EntanglerType const& entangler )
 {
  SizeType result = 0;

  while( true )
   {
    if( true == entangler.tieR( beginR ) )
     {
      return result;
     }
    ++result;
    if( 0 ==  beginR )
     {
      return result;
     }
    --beginR;
   }
  return result;
 }

S_match::S_feature::S_disparity::Fence::SizeType 
S_match::S_feature::S_disparity::Fence::measureRR( SizeType beginR, EntanglerType const& entangler )
 {
  SizeType result = 0;
  auto height = entangler.height();
  for( ;beginR < height; ++beginR )
   {
    if( true == entangler.tieR( beginR ) )
     {
      return result;
     }
    ++result;
   }
  return result;
 }
