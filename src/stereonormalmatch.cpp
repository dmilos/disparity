
#include "math/math.hpp"
#include "./stereonormalmatch.hpp"

StereoNormalMatch::StereoNormalMatch()
 {
  side( 8 );
  m_trash = 0.14;
  m_factor = 1;
 }

 void StereoNormalMatch::side( int s )
  {
   m_side = s;
   m_leftCloud.resize( (2 * m_side + 1) * (2 * m_side + 1) );
   m_rightCloud.resize( (2 * m_side + 1) * (2 * m_side + 1) );
  }

void StereoNormalMatch::process( ImageType & disparity, ImageType const& left, ImageType const& right )const
 {
  int width = (int)left.cols;
  int height = (int)right.cols;
  m_square.init( width, height );

  m_disparityL = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );
  m_disparityR = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

  //for( SizeType line=60; line <  240 ; ++line )
  //for( SizeType line=86; line <  154 ; ++line )
  //for( SizeType line=130; line <  160 ; ++line )
  //for( SizeType line=122; line <  123 ; ++line )
  for( SizeType line=0; line <  left.rows ; ++line )
   {
    std::cout << std::setw( 6 ) << line << "/" << left.rows << " - ";
    process_P(  line, left, right );
    m_square.importL( disparity, line );
    processL( m_disparityL, line, left, right );
    processR( m_disparityR, line, left, right );
    m_square.purge();
    processB( disparity, line, left, right );
    std::cout << "|" << std::endl;;
   }
 }

void StereoNormalMatch::process_P(  SizeType const& line, ImageType const& left, ImageType const& right )const
{
  int width = (int)left.cols;
  int height = (int)right.cols;

  ScalarType maximum = 0;
  for( SizeType xL = 0; xL < width; ++xL )
   {
    for( SizeType xR = std::max<int>( 0, (int)xL - 100 ); xR < xL; ++xR )
     //for( SizeType xR = 0; xR < height; ++xR )
     {
      auto d = distance( { xL, line }, { xR, line }, left, right );
      m_square.m_distance[xR * width + xL] = (float)d;
      maximum = std::max( maximum, d );
     }
    if( 0 == (xL % 10) )  std::cout << ".";
  }

  //cv::Mat distanceMap( height, width, CV_64FC1, m_square.m_distance.data() );
  //distanceMap *= 255/ maximum;
  //cv::imwrite( "map" + std::to_string( line ) + ".png", distanceMap );
 }

void StereoNormalMatch::processL( ImageType & disparity, SizeType const & line, ImageType const& left, ImageType const& right )const
 {
  m_square.processL(  );
  m_square.disparityL();

  int width =  (int)left.cols;
  int height = (int)right.cols;

  for( SizeType xL=0; xL < (SizeType)width; ++xL )
   {
    disparity.at<std::uint8_t>( (int)line, (int)xL ) = m_square.m_disparityL[xL];
   }
 }

void StereoNormalMatch::processR( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const
 {
  m_square.processR();
  m_square.disparityR();

  int width = (int)left.cols;
  int height = (int)right.cols;

  for( SizeType xR = 0; xR < (SizeType)width; ++xR )
  {
    disparity.at<std::uint8_t>( (int)line, (int)xR ) = m_square.m_disparityR[xR];
  }
 }

void StereoNormalMatch::processB( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const
 {
  m_square.disparityB();

  int width = (int)left.cols;
  int height = (int)right.cols;

  for( SizeType xL = 0; xL < (SizeType)width; ++xL )
   {
    disparity.at<std::uint8_t>( (int)line, (int)xL ) = m_square.m_disparityB[xL];
   }
 }

StereoNormalMatch::ScalarType StereoNormalMatch::distance( Size2DType const &L, Size2DType const &R, ImageType const& left, ImageType const& right )const
 {
  //const_cast<Size2DType&>( L) [0] = 335;
  //const_cast<Size2DType&>( L) [1] = 142;
  //const_cast<Size2DType&>( R) [0] = 278;
  //const_cast<Size2DType&>( R) [1] = 142;

  int width = (int)left.cols;
  int height = (int)right.cols;

  ScalarType summae = 0;
  ScalarType norma=0;

  ColorType pivotL=get( { L[0], L[1] }, left );
  ColorType pivotR=get( { R[0], R[1] }, right );

  //cv::Mat patchL( 2*m_side+1, 2*m_side+1, CV_8UC3 );
  //cv::Mat patchR( 2*m_side+1, 2*m_side+1, CV_8UC3 );
  //cv::Mat distance( 2*m_side+1, 2*m_side+1, CV_8UC1 );

  for( int y = -m_side; y <= m_side; ++y )
   for( int x = -m_side; x <= m_side; ++x )
    {
     m_leftCloud[  ( y+ m_side)*( 2*m_side+1 ) + ( x + m_side )  ] = { ((double)x)/m_side, ((double)y)/m_side, 0.0 };
     m_rightCloud[ ( y+ m_side)*( 2*m_side+1 ) + ( x + m_side )  ] = { ((double)x)/m_side, ((double)y)/m_side, 0.0 };

     auto Lx = (int)L[0] + x; if( Lx < 0 ) continue; if( left.cols  <= Lx ) continue;
     auto Ly = (int)L[1] + y; if( Ly < 0 ) continue; if( left.rows  <= Ly ) continue;
     auto Rx = (int)R[0] + x; if( Rx < 0 ) continue; if( right.cols <= Rx ) continue;
     auto Ry = (int)R[1] + y; if( Ry < 0 ) continue; if( right.rows <= Ry ) continue;

     auto cL = get( { SizeType( Lx ), SizeType( Ly ) }, left  );
     auto cR = get( { SizeType( Rx ), SizeType( Ry ) }, right );
     if( m_trash < ::color::operation::distance( pivotL, cL ) ) continue;

     //auto const& pixelL = left.at<cv::Vec3b>( Ly, Lx );
     //auto const& pixelR = right.at<cv::Vec3b>( Ry, Rx );

     //auto distanca = sqrt(  + ( pixelL[0] - pixelR[0] ) * ( pixelL[0] - pixelR[0])
     //                       + ( pixelL[1] - pixelR[1] ) * ( pixelL[1] - pixelR[1])
     //                       + ( pixelL[2] - pixelR[2] ) * ( pixelL[2] - pixelR[2])
     //   );
     //distanca /= 255.0 * 1.73;
    //auto spatial = sqrt( x*x+y*y )/ m_side/ m_side;
    //patchL.at<cv::Vec3b>( y + m_side, x + m_side )[0] = cL[2] * 255;
    //patchL.at<cv::Vec3b>( y + m_side, x + m_side )[1] = cL[1] * 255;
    //patchL.at<cv::Vec3b>( y + m_side, x + m_side )[2] = cL[0] * 255;
    //patchR.at<cv::Vec3b>( y + m_side, x + m_side )[0] = cR[2] * 255;
    //patchR.at<cv::Vec3b>( y + m_side, x + m_side )[1] = cR[1] * 255;
    //patchR.at<cv::Vec3b>( y + m_side, x + m_side )[2] = cR[0] * 255;
     m_leftCloud[  ( y+ m_side)*( 2*m_side+1 ) + ( x + m_side )  ] = { ((double)x)/m_side, ((double)y)/m_side, m_factor*color::gray<double>( cL )[0] };
     m_rightCloud[ ( y+ m_side)*( 2*m_side+1 ) + ( x + m_side )  ] = { ((double)x)/m_side, ((double)y)/m_side, m_factor*color::gray<double>( cR )[0] };
    }

  ::math::geometry::plane::no3d<double >  planeL;
  ::math::geometry::plane::no3d<double >  planeR;
  ::math::geometry::plane::fit( planeL, m_leftCloud );
  ::math::geometry::plane::fit( planeR, m_rightCloud );

  //cv::imwrite( "patchL_" + std::to_string( L[0] ) + "x" + std::to_string( L[1] ) + ".png" , patchL );
  //cv::imwrite( "patchR_" + std::to_string( L[0] ) + "x" + std::to_string( L[1] ) + ".png" , patchR );

  //static double summae_D = 0;
  //static double max_D = 0;
  //static double min_D = 100;
  //static int counter_D = 0;

  //auto d = math::linear::vector::distance( planeL.origin(), planeR.origin() );
  //if( 0.010810810810810811 < d ) return 1;

   auto result = math::linear::vector::angle( planeL.normal(), planeR.normal() );
  result /= math::constants::PHI;
  //summae_D += a;  ++counter_D;
  //max_D = std::max( max_D, a );
  //min_D = std::min( min_D, a );

  return result;
 }



StereoNormalMatch::ScalarType StereoNormalMatch::distance( Vector3DType const &left, Vector3DType const & right )const
 {
  auto d = math::linear::vector::angle( left, right );
  return d;
 }

StereoNormalMatch::ColorType StereoNormalMatch::get( Size2DType const location, ImageType const image )const
 {
  ColorType result;
  auto const& pixel = image.at<cv::Vec3b>( (int)location[1], (int)location[0] );
  result[0] = pixel[2]/255.0;
  result[1] = pixel[1]/255.0;
  result[2] = pixel[0]/255.0;
  return result;
 }

