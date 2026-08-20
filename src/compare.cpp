#include "./compare.hpp"

std::size_t compare( cv::Mat const& left, cv::Mat const& right, int tolerance )
 {
  std::size_t result = 0;
  const std::size_t count= 4;
  std::size_t segment = 1 + left.rows / count;

  std::array< std::size_t, count> partial; std::fill(partial.begin(), partial.end(), 0);
  for( int y=0; y< left.rows; ++y )
   {
    for( int x=0; x< left.cols; ++x )
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
          ++partial[ y / segment ];
         }
        continue;
       }
      if( L-R < tolerance )
       {
        ++result;
        ++partial[ y / segment ];
        continue;
       }
     }
   }
  //return *std::min_element( partial.begin(), partial.end());
  return result;
 }

std::size_t mask( cv::Mat& mask, cv::Mat const& left, cv::Mat const& right, int tolerance )
 {
  std::size_t result = 0;
  mask.setTo( cv::Scalar( 0 ) );
  for( int y=0; y< left.rows; ++y )
   {
    for( int x=0; x< left.cols; ++x )
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

