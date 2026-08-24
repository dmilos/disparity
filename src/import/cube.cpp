#include "cube.hpp"

#include <iostream>
#include <iomanip>



S_match::S_feature::S_disparity::Cube::Cube(  )
 {
 }


void
S_match::S_feature::S_disparity::Cube::process( SizeType    const& y, LasagnaType const& left, LasagnaType const& right )
 {
  SizeType width  =  left.resolution()[0];
  SizeType height = right.resolution()[0];
  SizeType depth  = left.layer().size();

  VectorType V; V.resize( depth );
  WallType W; W.resize( width, V );
  m_block.resize( height, W );

  for( SizeType xR=0; xR< width; ++xR )
   {
    for( SizeType xL=0; xL< height; ++xL )
     {
      for( SizeType z=0; z< depth; ++z )
       {
        auto const& L =  left.get( { xL, y, z } );
        auto const& R = right.get( { xR, y, z } );

        m_block[xR][xL][ z ] = fabs( L - R );
       }
     }
   }
 }

void
S_match::S_feature::S_disparity::Cube::square( SquareType & square, RestrictionType const& restriction )const
 {
  auto width  = m_block[0].size();
  auto height = m_block.size( );

  square.resolution( {width,height} );

  for( SizeType l = 0; l < width; ++l )
   {
    for( SizeType r = 0; r < width; ++r )
     {
      auto d = distance( restriction, l, r );
      square.set( { l, r }, d );
     }
   }
 }

S_match::S_feature::S_disparity::Cube::ScalarType
S_match::S_feature::S_disparity::Cube::distance( RestrictionType const& restriction, SizeType    const& left, SizeType    const& right )const
 {
  ScalarType result = 0;
  for( auto const& z: restriction )
   {
    result += m_block[right][left][ z ];
   }
  return result;
 }

