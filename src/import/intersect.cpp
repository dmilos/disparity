#include "./intersect.hpp"



S_match::S_feature::S_disparity::Intersect::Intersect()
 {
  m_trash = 5;

 }

bool S_match::S_feature::S_disparity::Intersect::process( ImageType & result, ImageType const& left, ImageType const& right )
 {
  auto width  = left.resolution( )[0];
  auto height = left.resolution( )[1];

  result.resolution( left.resolution(), color::gray<double>({0}) );

  for( SizeType y = 0; y < height; ++y )
   {
    for( SizeType x = 0; x < width; ++x )
     {
      auto const& l =  left.get( { x, y } );
      auto const& r = right.get( { x, y } );

      auto d = fabs( l[0] - r[0] );
      if( m_trash < d )
       {
        continue;
       }
      result.set( { x, y }, (l+r)/2 );
     }
   }

  return true;
 }
