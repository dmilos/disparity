
#include "./stereopatchnormgraymatch.hpp"

StereoPatchNormGrayMatch::StereoPatchNormGrayMatch()
 {
  m_trash = 0.13;
  m_side = 5;
 }

void StereoPatchNormGrayMatch::process( ImageType & disparity, ImageType const& left, ImageType const& right )const
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
    std::cout << std::setw(6) << line << "/" << left.rows << " - ";
    process_P(  line, left, right );
    m_square.importL( disparity, line );
    processL( m_disparityL, line, left, right );
    processR( m_disparityR, line, left, right );
    m_square.purge();
    processB( disparity, line, left, right );
    std::cout << "|" << std::endl;;
   }
 }

void StereoPatchNormGrayMatch::process_P(  SizeType const& line, ImageType const& left, ImageType const& right )const
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

void StereoPatchNormGrayMatch::processL( ImageType & disparity, SizeType const & line, ImageType const& left, ImageType const& right )const
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

void StereoPatchNormGrayMatch::processR( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const
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

void StereoPatchNormGrayMatch::processB( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const
 {
  m_square.disparityB();

  int width = (int)left.cols;
  int height = (int)right.cols;

  for( SizeType xL = 0; xL < (SizeType)width; ++xL )
   {
    disparity.at<std::uint8_t>( (int)line, (int)xL ) = m_square.m_disparityB[xL];
   }
 }

StereoPatchNormGrayMatch::ScalarType StereoPatchNormGrayMatch::distance( Size2DType const &L, Size2DType const &R, ImageType const& left, ImageType const& right )const
 {
  //const_cast<Size2DType&>( L) [0] = 335;
  //const_cast<Size2DType&>( L) [1] = 142;
  //const_cast<Size2DType&>( R) [0] = 278;
  //const_cast<Size2DType&>( R) [1] = 142;

  int width = (int)left.cols;
  int height = (int)right.cols;

  ColorType pivotL=get( { L[0], L[1] }, left );
  ColorType pivotR=get( { R[0], R[1] }, right );

  ScalarType summaeL = 0;
  ScalarType summaeR = 0;
  SizeType count = 0;
  for( int y = -m_side; y <= m_side; ++y )
   for( int x = -m_side; x <= m_side; ++x )
    {
     auto Lx = (int)L[0] + x; if( Lx < 0 ) continue; if( left.cols  <= Lx ) continue;
     auto Ly = (int)L[1] + y; if( Ly < 0 ) continue; if( left.rows  <= Ly ) continue;
     auto Rx = (int)R[0] + x; if( Rx < 0 ) continue; if( right.cols <= Rx ) continue;
     auto Ry = (int)R[1] + y; if( Ry < 0 ) continue; if( right.rows <= Ry ) continue;

     auto cL = get( { SizeType( Lx ), SizeType( Ly ) }, left  );
     auto cR = get( { SizeType( Rx ), SizeType( Ry ) }, right );
     summaeL = color::gray<double>( cL )[0];
     summaeR = color::gray<double>( cR )[0];
     ++count;
    }

   summaeL /= count;
   summaeR /= count;

   ColorType shiftL( { summaeL, summaeL, summaeL } );
   ColorType shiftR( { summaeR, summaeR, summaeR } );

  double summae = 0;
  for( int y = -m_side; y <= m_side; ++y )
   for( int x = -m_side; x <= m_side; ++x )
    {
     auto Lx = (int)L[0] + x; if( Lx < 0 ) continue; if( left.cols  <= Lx ) continue;
     auto Ly = (int)L[1] + y; if( Ly < 0 ) continue; if( left.rows  <= Ly ) continue;
     auto Rx = (int)R[0] + x; if( Rx < 0 ) continue; if( right.cols <= Rx ) continue;
     auto Ry = (int)R[1] + y; if( Ry < 0 ) continue; if( right.rows <= Ry ) continue;

     auto cL = get( { SizeType( Lx ), SizeType( Ly ) }, left  );
     auto cR = get( { SizeType( Rx ), SizeType( Ry ) }, right );

     auto distanca = distance( cL-shiftL, cR-shiftR );
     summae += distanca;
    }

  auto result = summae / m_side / m_side;

  return result;
 }

StereoPatchNormGrayMatch::ScalarType StereoPatchNormGrayMatch::distance( ColorType const &left, ColorType const & right )const
 {
   auto d = ::color::operation::distance( left, right );
  return d;
}

StereoPatchNormGrayMatch::ColorType StereoPatchNormGrayMatch::get( Size2DType const location, ImageType const image )const
 {
  ColorType result;
  auto const& pixel = image.at<cv::Vec3b>( (int)location[1], (int)location[0] );
  result[0] = pixel[2]/255.0;
  result[1] = pixel[1]/255.0;
  result[2] = pixel[0]/255.0;
  return result;
 }

