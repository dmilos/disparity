
#include "./stereomatchedge.hpp"

StereoEdgeMatch::StereoEdgeMatch()
 {
  // preset 1
  m_trash = 0.1;
  m_side = 6;
  m_square.m_trashold = 0.09;
  m_square.m_proximity = 0.0;

  // preset 2
  m_trash = 1;
  m_side = 6;
  m_square.m_trashold = 0.03;
  m_square.m_proximity = 0.0009;
 }

void StereoEdgeMatch::process( ImageType & disparity, ImageType const& left, ImageType const& right )const
 {
  int width = (int)left.cols;
  int height = (int)right.cols;

  // bilateral

  for( SizeType Y=0; Y <  left.rows ; ++Y )
   {
    
    for( SizeType X = 0; X < left.cols-1; ++X )
     {
      auto const p0 = get( { X, Y }, m_imageL );
      auto const p1 = get( { X+1, Y }, m_imageL );
      auto d = distance( p0, p1 );
      if( d < m_trash )
       {
        // length ++
        // summae = 
       }
      //summae /= length;

      //for( int i=start; i< X; ++i )
       {
        //auto t = i/length;
        // set t
        // set l
        // set color
       }

     }
   }

  m_square.init( width, height );
  m_disparityL = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );
  m_disparityR = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

  for( SizeType line=0; line <  left.rows ; ++line )
   {
    std::cout << std::setw(6) << line << "/" << left.rows << " - ";
    process_P(  line, left, right );
    m_square.importL( disparity, line );
    m_square.purge();
    processB( disparity, line, left, right );
    std::cout << "|" << std::endl;;
   }
 }

void StereoEdgeMatch::process_P(  SizeType const& line, ImageType const& left, ImageType const& right )const
{
  int width = (int)left.cols;
  int height = (int)right.cols;

  ScalarType maximum = 0;
  for( SizeType xL = 0; xL < width; ++xL )
   {
    for( SizeType xR = std::max<int>( 0, (int)xL - 100 ); xR < xL; ++xR )
     //for( SizeType xR = 0; xR < height; ++xR )
     {
      //auto d = distance( { xL, line }, { xR, line } );
      //m_square.m_distance[xR * width + xL] = (float)d;
      //maximum = std::max( maximum, d );
     }
    if( 0 == (xL % 10) )  std::cout << ".";
  }

  //cv::Mat distanceMap( height, width, CV_64FC1, m_square.m_distance.data() );
  //distanceMap *= 255/ maximum;
  //cv::imwrite( "map" + std::to_string( line ) + ".png", distanceMap );
 }

 
void StereoEdgeMatch::processB( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const
 {
  m_square.disparityB();

  int width = (int)left.cols;
  int height = (int)right.cols;

  for( SizeType xL = 0; xL < (SizeType)width; ++xL )
   {
    disparity.at<std::uint8_t>( (int)line, (int)xL ) = m_square.m_disparityB[xL];
   }
 }

StereoEdgeMatch::ScalarType StereoEdgeMatch::distance( ColorType const &left, ColorType const & right )const
 {
  //color::gray<double> L; L = left;
  //color::gray<double> R; R = right;
  //color::lab<double> L; L = left;
  //color::lab<double> R; R = right;
  //auto d = ::color::operation::distance( L, R )/100.0 ;
  //return d;
  //auto g = 10*fabs( L[0] - R[0] );
  auto d = ::color::operation::distance( left, right );
  return d;
  //return g;
}

StereoEdgeMatch::ColorType StereoEdgeMatch::get( Size2DType const location, ImageType const image )const
 {
  ColorType result;
  auto const& pixel = image.at<cv::Vec3b>( (int)location[1], (int)location[0] );
  result[0] = pixel[2]/255.0;
  result[1] = pixel[1]/255.0;
  result[2] = pixel[0]/255.0;
  return result;
 }

