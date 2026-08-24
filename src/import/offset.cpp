#include "opencv2/opencv.hpp"

#include "./offset.hpp"

S_match::S_feature::S_disparity::Offset::Offset()
 {
 }

void S_match::S_feature::S_disparity::Offset::process( LasagnaType & lasagna, SizeType const& index, Int2DType const& offset ) const
 {
  auto width  = lasagna.layer()[ 0 ].resolution()[0];
  auto height = lasagna.layer()[ 0 ].resolution()[1];

  {
   auto tmp = lasagna.layer()[ index ];
   lasagna.append( tmp );
  }

  auto const& source = lasagna.layer()[ index ];
  auto      & target = lasagna.layer().back();

  for( SizeType y=0; y < height; ++y )
   for( SizeType x=0; x <  width; ++x )
    {
     int X = (int)x + offset[0];
     int Y = (int)y + offset[1];

     if( X < 0 ) continue;
     if( Y < 0 ) continue;
     if( width <= X ) continue;
     if( height <= Y ) continue;

     target.set( {x,y},  source.get( { (SizeType)X,(SizeType)Y } ) );
    }

 }