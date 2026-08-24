#include "opencv2/opencv.hpp"

#include "./convolve.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::S_Stacker::Convolve::Convolve()
 {
  m_debug = false;
 }


#if 0 // ! defined ( OPENCV_ALL_HPP )
bool S_match::S_feature::S_disparity::S_Stacker::Convolve::process( LasagnaType &lasagna, BankType const& bank, ImageType const& image )const
 {
  if( true == m_debug )std::cout << PREFIX << "swf ..." << std::endl;

  SizeType width = image.resolution()[0];
  SizeType offset = lasagna.layer().size();

  lasagna.layer().resize( offset + bank.size() );

  for( SizeType index=0; index < bank.size(); ++index )
   {
    auto & layer = lasagna.layer()[ offset + index ];

    Size2DType hot = { bank[index].size()[0]/2, bank[index].size()[1]/2 };
    auto const& filter = bank[index];

    ::graphics::image::convolve::process( layer, filter, hot, image  );
    if( true == m_debug )std::cout << PREFIX<<   index << std::endl;
   }

  return true;
 }

#endif

#if 1 // defined( OPENCV_ALL_HPP )
bool S_match::S_feature::S_disparity::S_Stacker::Convolve::process( LasagnaType &lasagna, BankType const& bank, ImageType const& image )const
 {
  if( true == m_debug )std::cout << PREFIX<< "ocv..." << std::endl;

  SizeType width = image.resolution()[0];

  SizeType offset = lasagna.layer().size();

  lasagna.layer().resize( offset + bank.size() );

  ::cv::Mat Ls, Lt; graphics::image::convert::image2cv<ScalarType>( Ls, image );

  for( SizeType index=0; index < bank.size(); ++index )
   {
    auto & layer = lasagna.layer()[ offset + index ];
    
    //Size2DType hot = { bank[index].size()[0]/2, bank[index].size()[1]/2 };
    ::cv::Mat F; graphics::image::convolve::filter::filter2cv( F, bank[index] );

    ::cv::filter2D( Ls, Lt, -1, F, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT ); graphics::image::convert::cv2image( layer, Lt );

    if( true == m_debug )std::cout << PREFIX<< " ..."<< index << std::endl;
   }

  return true;
 }

#endif

bool S_match::S_feature::S_disparity::S_Stacker::Convolve::process( DisparityType &disparity, BankType const& bank, ImageType const& left, ImageType const& right )const
 {
  process( disparity.m_left , bank, left );
  process( disparity.m_right, bank, right );
  return true;
 }

#define MY_DEBUG 0

bool S_match::S_feature::S_disparity::S_Stacker::Convolve::process( LasagnaType &lasagna, BankType const& bank, ImageRgbType const& image )const
 {
  ScalarType coefficient = +log( 0.5 ) / ( 42.0 / 100.0 );
  if( true == m_debug )std::cout << PREFIX << "swf ..." << std::endl;

  SizeType width = image.resolution()[0];
  SizeType height = image.resolution()[1];
  SizeType offset = lasagna.layer().size();

  lasagna.layer().resize( offset + bank.size() );

#if 1 == MY_DEBUG
 int x_debug = 78;
 int y_debug = 61;
#endif

  MaskType *maskArray = nullptr;
  if( 0 == m_side ) { maskArray = & m_maskLeft ;  std::cout << "||"<< bank.size() << ", "; }
  if( 1 == m_side ) { maskArray = & m_maskRight;  std::cout << bank.size() << "||"; }
 
  for( SizeType index=0; index < bank.size(); ++index )
   {
    auto & layer = lasagna.layer()[ offset + index ];
    layer.resolution( image.resolution() );

    auto const& filter = bank[index];
#if 1 == MY_DEBUG
        {
        ::graphics::image::model< color::gray<double>::category_type > filterI;  
         ::graphics::image::convolve::filter::convert( filterI, filter );
         ::graphics::image::transformator_type<color::gray<double>::category_type >  invert = []( color::gray<double>& pixel )->void { pixel.set<0>( fabs( pixel[0] ) ); };
         ::graphics::image::transform( filterI, invert );  
         ::graphics::image::save( "aaaaaFo_" + std::to_string( filter.size()[0] ) + "_"+ std::to_string( index ) + ".png", filterI );
       }
#endif

    if( ( 0 != index) && ( 0 == (index% 10   ) ) ) std::cout << ".";
    if( ( 0 != index) && ( 0 == (index% 100  ) ) ) std::cout << "C";
    if( ( 0 != index) && ( 0 == (index% 1000 ) ) ) std::cout << "M";
    FilterType filterX; filterX.size( filter.size() );

    for( int y=0; y < height; ++y )
     for( int x=0; x < width; ++x )
      {
       auto const& mask   = (*maskArray)[y][x];
       //::graphics::image::convolve::filter::fill( filterX, 0 );
       ::graphics::image::convolve::filter::crop( filterX, { (int)mask.size()[0]/2 - (int)filter.size()[0]/2, (int)mask.size()[1]/2 - (int)filter.size()[1]/2 }, mask );

#if 1 == MY_DEBUG
       if( ( x_debug  ==x ) && ( y_debug == y ) ) 
        {
        ::graphics::image::model< color::gray<double>::category_type > filterI;  
         ::graphics::image::convolve::filter::convert( filterI, filterX );
         ::graphics::image::save( "aaaaaMc_" +  std::to_string(m_side) +"_"+std::to_string(x) +"x"+ std::to_string(y) + "_" + std::to_string( filter.size()[0] )  + ".png", filterI );
       }
#endif
       ::graphics::image::convolve::filter::multiply( filterX, filter );
#if 1 == MY_DEBUG
       if( ( x_debug ==x) && ( y_debug == y ) ) 
        {
        ::graphics::image::model< color::gray<double>::category_type > filterI;  
         ::graphics::image::convolve::filter::convert( filterI, filterX );
         ::graphics::image::transformator_type<color::gray<double>::category_type >  invert = []( color::gray<double>& pixel )->void { pixel.set<0>( fabs( pixel[0] ) ); };
         ::graphics::image::transform( filterI, invert );  
         graphics::image::save( "aaaaaFm_" + std::to_string(m_side) + "_" + std::to_string(x) +"x"+ std::to_string(y) + "_" + std::to_string( filter.size()[0] )+ "_" +  std::to_string( index ) + ".png", filterI );
       }
#endif

       auto v = ::graphics::image::convolve::process( filterX, { (int)x - (int)filter.size()[0]/2,  (int)y - (int)filter.size()[1]/2 }, image );
       auto g = color::get::gray( v );
       lasagna.set(   (SizeType)x, (SizeType)y, index, g );
      }

    if( true == m_debug )std::cout << PREFIX<<   index << std::endl;
   }

  return true;
 }


bool S_match::S_feature::S_disparity::S_Stacker::Convolve::process( DisparityType &disparity, BankType const& bank, ImageRgbType const& left, ImageRgbType const& right )const
 {
  m_side = 0; process( disparity.m_left , bank, left  );
  m_side = 1; process( disparity.m_right, bank, right );
  m_side = -1;
  return true;
 }

void S_match::S_feature::S_disparity::S_Stacker::Convolve::makeMask( MaskType & maskVector, Size2DType const& size, ImageRgbType const& image )const
 {
  std::cout << PREFIX << "makeMask ..." ;
  auto time_start = std::chrono::system_clock::now();

  SizeType width  = image.resolution()[0];
  SizeType height = image.resolution()[1];
#if 1 == MY_DEBUG
 int x_debug = 78;
 int y_debug = 61;
#endif

  maskVector.resize( height );
  for( int y=0; y < height; ++y )
   {
    maskVector[y].resize( width, FilterType{ size } );
   }

  for( int y=0; y < height; ++y )
   for( int x=0; x < width; ++x )
    {
     auto const& center = image.get( { (SizeType)x,(SizeType)y } );
     auto & filter = maskVector[y][x];
     ::graphics::image::convolve::filter::fill<ScalarType>( filter, 0 );

     std::array<int,2>  corner;
     corner[0] = x - (int)size[0]/2;
     corner[1] = y - (int)size[1]/2;
     ::graphics::image::convolve::filter::extractor_type< double, ImageRgbType::color_type::category_type >  functor 
        = [ &center ]( ImageRgbType::color_type const& pixel )
      {
       extern int  g_offset0;
       extern int  g_offset1;
       auto d = ::color::operation::distance( center, pixel );
       //auto d = ::color::operation::distance<::color::constant::distance:: hsv_cone_entity>( center, pixel );

       //auto c = sqrt( -log( 0.5 ) )/( 9.0/1000.0 ); 
       //d =  exp( - c * d * d );

       //d = 1 - ::math::function::gain<double>( ::math::function::bais<double>(               d, g_offset0 / 100.0 ), g_offset1 / 100.0/10.0 );
       //d = 1 - ::math::function::gain<double>( ::math::function::bais<double>( d, 83 / 100.0 ), 7 / 100.0/10.0 );

       //d = 1 - d; if( d < ( 86/ 100.0)  ) { d = 0; } else { if( ( 96/ 100.0) < d ) d = 1; }  

       //d = 1 - d;
    
       d = ::math::function::ramp<double>( ::math::function::any_to_any<double>( d, 15.0 / 100.0, 3.0 / 100.0, 0.0 ,1.0 ) );

       return d;
      };

    ::graphics::image::convolve::filter::extract( filter, functor, image, corner );
#if 1 == MY_DEBUG
    if( ( x_debug == x ) && ( y_debug == y ) ) 
     {
     ::graphics::image::model< color::gray<double>::category_type > filterI;  
      graphics::image::convolve::filter::convert( filterI, filter );
      graphics::image::save( "aaaaaM_" + std::to_string(m_side) + "_" +std::to_string(x) +"x"+ std::to_string(y) + "_" + std::to_string( filter.size()[0] )  + ".png", filterI );
    }
#endif
   }
      
   std::cout << std::chrono::duration<double>( std::chrono::system_clock::now() - time_start ).count() << "... makeMask" << std::endl;
 }