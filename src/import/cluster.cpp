#include "cluster.hpp"

#include <iostream>
#include <iomanip>

S_match::S_feature::S_disparity::Cluster::Cluster( SizeType const& length, SizeType const& space )
 {
  m_lenght   = length;
  m_space    = space;
 }

S_match::S_feature::S_disparity::Cluster::SizeType
S_match::S_feature::S_disparity::Cluster::processL( EntanglerType & entangler )
 {
  SizeType result = 0;
  SizeType head  = 1;
  SizeType tail  = 1;

  for( SizeType pivotL = 0; pivotL + head + tail < entangler.width(); ++pivotL )
   {
    bool next = false;
    for( SizeType shift = 0; shift < head; ++shift )
     {
      if( true == entangler.tieL( pivotL + shift ) )
       {
        next = true;
        break;
       }
     }
    if( true == next )
     {
      continue;
     }

    if( false == entangler.tieL( pivotL + head + 0 ) )
     {
      continue;
     }
    next = false; 
    SizeType len = 1;
    for( ; len < m_lenght; ++len )
     {
      if( false == entangler.tieL( pivotL + head + len ) )
       {
        break;
       }
     }

    next = false;
    for( SizeType shift = 0; shift < tail; ++shift )
     {
      if( true == entangler.tieL( pivotL + head + len + shift ) )
       {
        next = true;
        break;
       }
     }
    if( true == next )
     {
      continue;
     }
    for( SizeType index = 0; index < len; ++index )
     {
      auto R =  entangler.getR( pivotL + head + index );
      entangler.spoilR( pivotL + head + index );
      entangler.spoilL( R );
      result += 2;
     }
   }

  return result;
 }

S_match::S_feature::S_disparity::Cluster::SizeType
S_match::S_feature::S_disparity::Cluster::processR( EntanglerType & entangler )
 {
  SizeType result = 0;
  SizeType head  = 1;
  SizeType tail  = 1;

  m_spoil.clear();
  m_spoil.reserve( entangler.width() );
  for( SizeType L = 0; L + 1 < entangler.width(); ++L )
   {
    if( false == entangler.tieL( L ) )
     {
      continue;
     }
    if( false == entangler.tieL( L + 1 ) )
     {
      continue;
     }
    if( entangler.getR( L ) + m_space < entangler.getR( L + 1 ))
     {
      m_spoil.push_back( L );
      m_spoil.push_back( L + 1 );
     }
   }

  for( auto const& L : m_spoil )
   {
    auto R =  entangler.getR( L );
    entangler.spoilR( L );
    entangler.spoilL( R );
    result += 2;
   }

  return result;
 }


