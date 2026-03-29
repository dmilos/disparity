
#include "./stereomatchv2.hpp"
#include "math/math.hpp"

StereoMatchV2::StereoMatchV2()
 {
  m_square.m_range = 10000; //!< in pixels
  m_square.m_trashold = 10000;
  m_square.m_proximity = 0;
  m_square.m_infinity = 10000.0;

  m_side = 5;
  m_strip = 200;
  m_boundLo = 0.955;
  m_boundHi = 1.0;
}

#define DEBUG_DITANCE 0
#define DEBUG_LINE  0



void StereoMatchV2::process( ImageType & disparity, ImageType const& left, ImageType const& right )const
 {
  std::cout << "m_side  : " << m_side << std::endl;
 
#if (1 == DEBUG_DITANCE) && (0 == DEBUG_LINE)
  distance( { 0, 80 }, { 0, 80 }, left, right );
  return ;
#endif
  int width = (int)left.cols;
  int height = (int)right.cols;

  m_square.init( width, height );

  m_disparityL = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );
  m_disparityR = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

//for( SizeType line=0; line <  80 ; ++line )
//for( SizeType line=147; line <  148 ; ++line )
 //for( SizeType line= 160; line <   170 ; ++line )
 // for( SizeType line=80; line <  81 ; ++line )
//for( SizeType line=400; line <  420 ; ++line )
 for( SizeType line=0; line < right.rows; ++line )
   {
    std::cout << std::setw( 6 ) << line << "/" << left.rows << " - ";
    process_P(  line, left, right );
    m_square.importL( disparity, line );
    m_square.purge() ;
    processL( m_disparityL, line, left, right );
    processR( m_disparityR, line, left, right );
    m_square.purge();
    processB( disparity, line, left, right );
    std::cout << "|" << std::endl;
#if 1 == DEBUG_LINE
    return;
#endif
   }
 }

void StereoMatchV2::process_P(  SizeType const& line, ImageType const& left, ImageType const& right )const
{
  int width = (int)left.cols;
  int height = (int)right.cols;

  ScalarType maximum = -1e6;
  ScalarType minimum = +1e6;
  for( SizeType xL = 0; xL < width; ++xL )
   {
    for( SizeType xR = std::max<int>( 0, (int)xL - m_strip ); xR < xL; ++xR )
     {
      auto d = distance( { xL, line }, { xR, line }, left, right );
      m_square.m_distance[xR * width + xL] = (float)d;
      maximum = std::max( maximum, d );
      minimum = std::min( minimum, d );
    }
    if( 0 == (xL % 10) )  std::cout << ".";
   }
#if 1 == DEBUG_LINE
  extern std::string g_prefix;

  for( auto& value: m_square.m_distance ) value = pow( value, 0.05 );
  cv::Mat distanceMap( height, width, CV_64FC1, m_square.m_distance.data() );
  distanceMap = 255 *( distanceMap - minimum) / (maximum - minimum);
   cv::imwrite( "map" + format( (int)line ) +"_"+ g_prefix + ".png", distanceMap );
#endif
}

void StereoMatchV2::processL( ImageType & disparity, SizeType const & line, ImageType const& left, ImageType const& right )const
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

void StereoMatchV2::processR( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const
 {
  m_square.processR( );
  m_square.disparityR();

  int width = (int)left.cols;
  int height = (int)right.cols;

  for( SizeType xR = 0; xR < (SizeType)width; ++xR )
   {
    disparity.at<std::uint8_t>( (int)line, (int)xR ) = m_square.m_disparityR[xR];
   }
 }

void StereoMatchV2::processB( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const
 {
  m_square.disparityB();

  int width = (int)left.cols;
  int height = (int)right.cols;

  for( SizeType xL = 0; xL < (SizeType)width; ++xL )
   {
    disparity.at<std::uint8_t>( (int)line, (int)xL ) = m_square.m_disparityB[xL];
   }
 }

StereoMatchV2::ScalarType StereoMatchV2::distance( Size2DType const &L, Size2DType const &R, ImageType const& left, ImageType const& right )const
 {
#if (1 == DEBUG_DITANCE) 
  extern std::string g_prefix;
#endif

#if (1 == DEBUG_DITANCE) && (0 == DEBUG_LINE)
  extern std::string g_prefix;
  // tsukuba
  const_cast<Size2DType&>( L) [0] = 350 * 1;
  const_cast<Size2DType&>( L) [1] = 147 * 1;
  const_cast<Size2DType&>( R) [0] = 296 * 1-3;
  const_cast<Size2DType&>( R) [1] = 147 * 1;
  // circle
  //const_cast<Size2DType&>( L) [0] = 8;
  //const_cast<Size2DType&>( L) [1] = 80;
  //const_cast<Size2DType&>( R) [0] = 8;
  //const_cast<Size2DType&>( R) [1] = 80;
#endif

  int width = (int)left.cols;
  int height = (int)right.cols;

  ScalarType summae = 0;
  ScalarType norma=0;

  ColorType pivotL=get( { L[0], L[1] }, left );
  ColorType pivotR=get( { R[0], R[1] }, right );

#if 1 == DEBUG_DITANCE
  cv::Mat patchL( 2*m_side+1, 2*m_side+1, CV_8UC3 );
  cv::Mat patchR( 2*m_side+1, 2*m_side+1, CV_8UC3 );
  cv::Mat maskL( 2*m_side+1, 2*m_side+1, CV_8UC1 );
  cv::Mat maskR( 2*m_side+1, 2*m_side+1, CV_8UC1 );
  cv::Mat distanceMap( 2*m_side+1, 2*m_side+1, CV_8UC1 );
#endif
  auto pivotD = distance( pivotL, pivotR );
  SizeType counter = 0;
  for( int y = -m_side; y <= m_side; ++y )
   for( int x = -m_side; x <= m_side; ++x )
    {
     auto Lx = (int)L[0] + x; if( Lx < 0 ) continue; if( left.cols  <= Lx ) continue;
     auto Ly = (int)L[1] + y; if( Ly < 0 ) continue; if( left.rows  <= Ly ) continue;
     auto Rx = (int)R[0] + x; if( Rx < 0 ) continue; if( right.cols <= Rx ) continue;
     auto Ry = (int)R[1] + y; if( Ry < 0 ) continue; if( right.rows <= Ry ) continue;
     ++counter;
     auto cL = get( { SizeType( Lx ), SizeType( Ly ) }, left  );
     auto cR = get( { SizeType( Rx ), SizeType( Ry ) }, right );

#if 1 == DEBUG_DITANCE
    patchL.at<cv::Vec3b>( y + m_side, x + m_side )[0] = (int)( cL[2] * 255 );
    patchL.at<cv::Vec3b>( y + m_side, x + m_side )[1] = (int)( cL[1] * 255 );
    patchL.at<cv::Vec3b>( y + m_side, x + m_side )[2] = (int)( cL[0] * 255 );
    patchR.at<cv::Vec3b>( y + m_side, x + m_side )[0] = (int)( cR[2] * 255 );
    patchR.at<cv::Vec3b>( y + m_side, x + m_side )[1] = (int)( cR[1] * 255 );
    patchR.at<cv::Vec3b>( y + m_side, x + m_side )[2] = (int)( cR[0] * 255 );
#endif

     auto distancaLcolor = distance( cL, pivotL );
     auto distancaRcolor = distance( cR, pivotR );

     auto coefficientL =  1.0-distancaLcolor/ sqrt( 3 );
     auto coefficientR =  1.0-distancaRcolor/ sqrt( 3 );
     ScalarType    coefficientF;

     coefficientL = math::function::to_one( math::function::ramp( coefficientL, m_boundLo, m_boundHi ), m_boundLo, m_boundHi );
     coefficientR = math::function::to_one( math::function::ramp( coefficientR, m_boundLo, m_boundHi ), m_boundLo, m_boundHi );

     coefficientF = std::max( coefficientL, coefficientR );

      auto value = distance( cL, cR )/sqrt(3);
      //value = ::math::function::ramp<double>( value, 0, m_trunc );
      //if( value < m_boundLo ) value = 0;
      //if( m_boundHi < value ) value = 1;
      //auto value = pivotD;

      summae += coefficientF * value;
      norma += coefficientF;

#if 1 == DEBUG_DITANCE
     maskL.at< std::uint8_t >( y + m_side, x + m_side ) = (std::uint8_t)(255 * coefficientL);
     maskR.at< std::uint8_t >( y + m_side, x + m_side ) = (std::uint8_t)(255 * coefficientR);
     distanceMap.at< std::uint8_t >( y + m_side, x + m_side ) = (std::uint8_t)( 8 * value );
     distanceMap.at< std::uint8_t >( y + m_side, x + m_side ) = (std::uint8_t)( 255 * coefficientF);
#endif
    }
    //if( norma < (2* m_side+1)* (2 * m_side + 1) * 0.2 ) return 1;
#if 1 == DEBUG_DITANCE

  cv::imwrite( g_prefix + "-maksL_"  + format( (int)L[0] ) + "x" + format( (int)L[1] ) + ".png" , maskL );
  cv::imwrite( g_prefix + "-maksR_"  + format( (int)R[0] ) + "x" + format( (int)R[1] ) + ".png" , maskR );
  cv::imwrite( g_prefix + "-patchL_" + format( (int)L[0] ) + "x" + format( (int)L[1] ) + ".png" , patchL );
  cv::imwrite( g_prefix + "-patchR_" + format( (int)R[0] ) + "x" + format( (int)R[1] ) + ".png" , patchR );
  cv::imwrite( g_prefix + "-coefF_"  + format( (int)L[0] ) + "x" + format( (int)R[0] ) + ".png" , 50*distanceMap );
 //exit(0);
#endif
  auto result = summae / norma;
  
  return result;
 }

StereoMatchV2::ScalarType StereoMatchV2::distance( ColorType const &left, ColorType const & right )const
 {
  auto d = ::color::operation::distance( left, right );
  return d;
 }

StereoMatchV2::ColorType StereoMatchV2::get( Size2DType const location, ImageType const image )const
 {
  ColorType result;
  auto const& pixel = image.at<cv::Vec3b>( (int)location[1], (int)location[0] );
  result[0] = pixel[2]/255.0;
  result[1] = pixel[1]/255.0;
  result[2] = pixel[0]/255.0;
  return result;
 }

