#include "./bsfs.hpp"
#include "./stacker/convolve.hpp"
#include <iostream>
#include <iomanip>
#include "opencv2/opencv.hpp"

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::BSFS::BSFS()
 {
  m_debug = false;
  m_coefficient = 10;
  m_occlusion  = 0.5;
 }

S_match::S_feature::S_disparity::BSFS::SizeType 
S_match::S_feature::S_disparity::BSFS::process( ImageGrayType  & image, ImageRGBType const& left, ImageRGBType const& right )const
 {
  m_left.clear(  ); S_match::S_feature::S_disparity::S_Stacker::Convolve().process( m_left,  m_bank, ImageGrayType(  left ) );
  m_right.clear( ); S_match::S_feature::S_disparity::S_Stacker::Convolve().process( m_right, m_bank, ImageGrayType( right ) );
  return process( image );
 }

S_match::S_feature::S_disparity::BSFS::SizeType 
S_match::S_feature::S_disparity::BSFS::process( ImageGrayType      & image )const
 {
  SizeType result = 0;
  SizeType width  = m_left.resolution()[0];
  SizeType height = m_left.resolution()[1];

  image.resolution( { width, height } );

  m_cost.resize( width + 1 );
  for (int i = 0; i < width+1; i++)
   {
    m_cost[i].resize( width + 1);
   }

  for( SizeType line = 0; line < height; line++ )
   {
    ScalarType the_max = 0;
    m_cost[0][0] = 0.0;
    for (int i = 1; i < width+1; i++)
     {
      m_cost[i][0] = i * m_occlusion;
      m_cost[0][i] = i * m_occlusion;
     }
    for (int i = 1; i < width + 1; i++)
     {
      for (int j = 1; j < width + 1; j++)
       {
        ScalarType no_occlusion = m_cost[i - 1][j - 1] + m_coefficient * distance( line, i - 1, j - 1 );
        ScalarType i_occlusion = m_cost[i - 1][j] + m_occlusion;
        ScalarType j_occlusion = m_cost[i][j - 1] + m_occlusion;
        m_cost[i][j] = min( no_occlusion, i_occlusion, j_occlusion );
        the_max = std::max( the_max, m_cost[i][j] );
       }
     }

    SizeType i = width, j = width;
    ScalarType cost_val = m_cost[width][width];

    //if(false)
    //{
    // cv::Mat cost_mat( width+1, width+1, CV_8UC1);
    // for (int i = 0; i < width + 1; i++)
    //   for (int j = 0; j < width + 1; j++)
    //     {
    //      cost_mat.at<uchar>( i, j ) = (uchar)( 255 * ( m_cost[i][j]/the_max ) );
    //     }
    // cv::imwrite( ("cost-"  + std::to_string( line ) + ".png" ).c_str(), cost_mat );
    //}

    while( (i > 0) && (j > 0) )
     {
      if( m_cost[i][j] == m_cost[i - 1][j] + m_occlusion)
       {
        image.set( { i - 1,  line }, gray_type( { 0 } ) );
         --i;
       }
      else
       {
        if( m_cost[i][j] == m_cost[i][j - 1] + m_occlusion)
         {
          --j;
         }
        else
         {
          ++result;
          auto d = ScalarType( j ) - ScalarType(i);
          image.set( { i - 1,  line }, gray_type( { d } ) );
          cost_val -= m_coefficient * distance( line, i - 1, j - 1 );
          --i;
          --j;
         }
       }
     }
   }
  return result;
 }

void S_match::S_feature::S_disparity::BSFS::clear()
 {
  m_bank.clear(  );
  m_left.clear(  );
  m_right.clear( );
 }

void S_match::S_feature::S_disparity::BSFS::bank( BankType const& B )
 {
  m_bank = B;
 }

S_match::S_feature::S_disparity::BSFS::ScalarType
S_match::S_feature::S_disparity::BSFS::distance( SizeType const& line, SizeType const& L, SizeType const& R )const
 {
  ScalarType result=0;
  SizeType total = m_left.depth();
  for( SizeType depth=0; depth < total; ++depth )
   {
    auto l =  m_left.get( { L, line, depth } );
    auto r = m_right.get( { R, line, depth } );
    result += ( l - r ) * ( l - r );
   }
  result = sqrt( result / total );
  return result;
 }


S_match::S_feature::S_disparity::BSFS::ScalarType
S_match::S_feature::S_disparity::BSFS::min( ScalarType a, ScalarType b, ScalarType c )
{
   if ( (a < b) && (a < c) ) return a;
   else if (b < c)   return b;
   else return c;
}

S_match::S_feature::S_disparity::BSFS::ScalarType
S_match::S_feature::S_disparity::BSFS::sqr( ScalarType a )
 {
  return a * a;
 }

