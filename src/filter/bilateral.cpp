#include "./bilateral.hpp"


Bilateral::Bilateral( SizeType const& iteration, SizeType  const& range, ScalarType  const& proximity )
 {
  m_iterations = iteration;
  m_range = range;
  m_proximity = proximity;
}

Bilateral::ScalarType 
Bilateral::distance( ColorType const& left, ColorType const& right )const
 {
  color::gray<double> Lg { left  };
  color::gray<double> Rg { right };
  auto dG = 256 * fabs( Lg[0] - Rg[0] );
  if( 16 < dG )return 1;
  auto Hl = 360 * color::get::hue( left );
  auto Hr = 360 * color::get::hue( right );

  auto dH = fabs( Hl - Hr );
  if( 180 < dH ) dH = 360 - dH;
  if(  30 < dH ) return 1;

  auto Sl = color::get::saturation( left );
  auto Sr = color::get::saturation( right );
  auto dS = fabs( Sl - Sr );
  if( 14.5 < dS ) return 1;

  return 0;
  return color::operation::distance( left, right );
 }

Bilateral::ColorType Bilateral::get( ImageType const& image, Integer2DType const& location )const
 {
  ColorType result = color::constant::black_t{};

  if( location[0] < 0 ) return result;
  if( location[1] < 0 ) return result;
  if( image.cols <= location[0] ) return result;
  if( image.rows <= location[1] ) return result;

  auto const& pixel = image.at<cv::Vec3b>( location[1], location[0] );

  result[0] = pixel[2]/255.0;
  result[1] = pixel[1]/255.0;
  result[2] = pixel[0]/255.0;

  return result;
 }

bool Bilateral::set( ImageType & image, Integer2DType const& location, ColorType const& value )const
 {
  if( location[0] < 0 ) return false;
  if( location[1] < 0 ) return false;
  if( image.cols<= location[0] ) return false;
  if( image.rows <= location[1] ) return false;

  auto & pixel = image.at<cv::Vec3b>( location[1], location[0] );
  pixel[0] = (int)( 255*value[2] );
  pixel[1] = (int)( 255*value[1] );
  pixel[2] = (int)( 255*value[0] );

  return true;
 }

Bilateral::ColorType Bilateral::process( ImageType const& image, Integer2DType const& location )const
 {
  //cv::Mat mask = cv::Mat::zeros( m_range * 2 + 1, m_range * 2 + 1, CV_8UC1 );
  //cv::Mat patch = cv::Mat::zeros( m_range * 2 + 1, m_range * 2 + 1, CV_8UC3 );

  ColorType result = color::constant::black_t{};
  auto center = get( image, location );

  SizeType counter = 0;
  for( int y= -(int)m_range; y <= (int)m_range; ++y )
    for( int x= -(int)m_range; x <= (int)m_range; ++x )
    {
     auto X = x + location[0];
     auto Y = y + location[1];
     auto other = get( image, { X, Y } );
     //patch.at<cv::Vec3b>( y+m_range, x+m_range ) = image.at<cv::Vec3b>(Y,X);
     auto d = distance( center, other );
     if( m_proximity < d )
      {
       continue;
      }
     result += other;
     //mask.at<std::uint8_t>( y+m_range, x+m_range ) = 255;
     ++counter;
    }
  
  //cv::imwrite( "mask" + std::to_string( location[0] ) + "x" + std::to_string( location[1] ) + ".png", mask );
  //cv::imwrite( "patch" + std::to_string( location[0] ) + "x" + std::to_string( location[1] ) + ".png", patch );
  return result / counter;
 }

void Bilateral::process( ImageType & target, ImageType const& source )const
 {
  int width = source.cols;
  int height = source.rows;
  target = source.clone();
  ImageType temp = source.clone();
  ImageType *S = &temp;
  ImageType *T = &target;

  for( int i=0; i< m_iterations; ++i )
   {
    for( int y=0; y < height; ++y )
     for( int x=0; x < width; ++x )
      {
       set( *T, {x,y}, process( *S, Integer2DType{x,y} ) );
      }

    std::swap( S, T );
   }

  if( &target != S )
   {
    target = S->clone();
   }
 }