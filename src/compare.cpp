#include "./compare.hpp"

std::size_t compare( cv::Mat const& left, cv::Mat const& right, int tolerance )
 {
  std::size_t result = 0;
  for( int y=0; y< left.rows; ++y )
   {
    for( int x=0; x< left.rows; ++x )
     {
      auto const& L =  left.at<std::uint8_t>(y,x);
      auto const& R = right.at<std::uint8_t>(y,x);
      if( L < 3 ) continue;
      if( R < 3 ) continue;

      if( L < R )
       {
        if( R-L < tolerance )
         {
          ++result;
         }
        continue;
       }
      if( L-R < tolerance )
       {
        ++result;
        continue;
       }
     }
   }

  return result;
 }

std::size_t mask( cv::Mat& mask, cv::Mat const& left, cv::Mat const& right, int tolerance )
 {
  std::size_t result = 0;
  mask.setTo( cv::Scalar( 0 ) );
  for( int y=0; y< left.rows; ++y )
   {
    for( int x=0; x< left.rows; ++x )
     {
      auto const& L =  left.at<std::uint8_t>(y,x);
      auto const& R = right.at<std::uint8_t>(y,x);
      if( L < 3 ) continue;
      if( R < 3 ) continue;

      if( L < R )
       {
        if( R-L < tolerance )
         {
          ++result;  mask.at<std::uint8_t>(y,x) = 255;
         }
        continue;
       }
      if( L-R < tolerance )
       {
        ++result;  mask.at<std::uint8_t>(y,x) = 255;
        continue;
       }
     }
   }

  return result;
 }

