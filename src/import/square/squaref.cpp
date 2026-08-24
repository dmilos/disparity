#include "squaref.hpp"

#include <iostream>
#include <iomanip>

S_match::S_feature::S_disparity::Square::Square( )
 {
 }

bool S_match::S_feature::S_disparity::Square::process( LineType const&left, LineType const &right )
 {
  table().resolution( { left.size(), right.size() } );

  for( SizeType L=0; L < left.size(); ++L )
   {
    for( SizeType R=0; R< right.size(); ++R )
     {
      auto & pixel = table().get( { L, R } );

      pixel[0] = m_feature.distance( left[L], right[R] );
     }
   }
  return true;
 }
