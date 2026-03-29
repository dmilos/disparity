#include <iostream>
#include <iomanip>
#include "./filter.hpp"

#include "math/math.hpp"

void normalize( Filter& filter )
 {
  double plus = 0;
  double minus= 0;
  std::size_t count_minus = 0;
  std::size_t count_zero = 0;
  std::size_t count_plus = 0;

  for( Filter::SizeType y=0; y< filter.size()[1]; ++y )
    for( Filter::SizeType x = 0; x < filter.size()[0]; ++x )
    {
     auto const& value = filter.get( {x,y} );
     if( value < -0.000001 ) 
      {
       minus += value;
       ++count_minus;
       continue;
      }
     if( 0.000001 < value )
      {
       plus += value;
       ++count_plus;
       continue;
      }
     filter.set( { x,y }, 0 );
     ++count_zero;
    }
  minus = -minus;
  for( Filter::SizeType y=0; y < filter.size()[1]; ++y )
    for( Filter::SizeType x = 0; x < filter.size()[1]; ++x )
    {
     auto const& value = filter.get( {x,y} );

     if( value < 0 )filter.set( { x,y }, value / minus );
     if( 0 < value )filter.set( { x,y }, value / plus );
    }
    //std::cout << std::setw( 8 ) << count_minus << ";";
    //std::cout << std::setw( 8 ) << count_zero << ";";
    //std::cout << std::setw( 8 ) << count_plus << ";";
    //std::cout << std::setw( 8 ) << abs( (int)count_plus - (int)count_minus ) << ";";
    //std::cout << std::endl;
 }

void save( std::string const& name, Filter const& filter )
 {
  cv::Mat mat( (int)filter.size()[1], (int)filter.size()[0], CV_64FC1, const_cast<double*>( filter.data()) );
  cv::Mat  cvMat = mat.clone();
  double minimum = filter.get({0,0});
  double maximum = filter.get({0,0}); 
  for( int y=0;y< filter.size()[1]; ++y )
    for( int x = 0; x < filter.size()[0]; ++x )
    {
      minimum = std::min( minimum, filter.get( { (std::size_t)x,(std::size_t)y } ) );
      maximum = std::max( maximum, filter.get( { (std::size_t)x,(std::size_t)y } ) );
    }

  minimum = - std::max( fabs( minimum ), fabs( maximum ) );
  maximum = + std::max( fabs( minimum ), fabs( maximum ) );
  cv::imwrite( name, 256*( cvMat - minimum) / ( maximum - minimum));
 }

void from_image( Filter& filter, cv::Mat const& gray, std::array<int,2> const& location )
 {
  for( int y=0 ; y < filter.size()[1] ; ++ y )
   {
    auto Y = y + location[1];
    if( Y < 0 ) continue;
    if( gray.rows <= Y ) continue;
    for( int x=0 ; x < filter.size()[0] ; ++ x )
     {
      auto X = x + location[0];
      if( gray.cols <= X ) continue;
      if( X < 0 ) continue;

      filter.set( {(Filter::SizeType)x,(Filter::SizeType)y},  gray.at<std::uint8_t>( Y,X)/ 255.0 );
     }
  }
 }

void gauss( Filter& filter )
 {
  for( int y=0 ; y < filter.size()[1] ; ++ y )
   {
    auto V = ::math::function::any_to_any<double>( y, 0, (double)filter.size()[1]-1, -1, +1 );

     for( int x=0 ; x < filter.size()[0] ; ++ x )
     {
      auto U = ::math::function::any_to_any<double>( x, 0, (double)filter.size()[0]-1, -1, +1 );

      auto D = sqrt( U*U + V*V );
      if( 1.0 < D ) 
       {
        filter.set( { (Filter::SizeType)x,(Filter::SizeType)y }, 0 ); 
        continue; 
       }

      filter.set( { (Filter::SizeType)x,(Filter::SizeType)y}, ::math::function::distribution::normal( D, 1.0/math::constants::PHI_SQRT2 ) );
     }
  }

 }

void gabor( Filter& filter, double const angle, double const& frequency, double const& shift )
 {
  double scaleX = 1;//::math::constants::GOLD;
  for( int y=0 ; y < filter.size()[1] ; ++ y )
   {
    auto V = ::math::function::any_to_any<double>( y, 0, (double)filter.size()[1]-1, -1, +1 );

     for( int x=0 ; x < filter.size()[0] ; ++ x )
     {
      auto U = ::math::function::any_to_any<double>( x, 0, (double)filter.size()[0]-1, -1, +1 );
      auto D = sqrt( U*U + V*V );
      if( 1.0 < D ) 
       {
        filter.set( { (Filter::SizeType)x,(Filter::SizeType)y }, 0 ); 
        continue; 
       }

      auto value = ::math::function::gabor2D<double>( angle, math::constants::PHI_invSQRT2, frequency, shift, { scaleX, 1.0 } )( {U,V } ) ;
      filter.set( { (Filter::SizeType)x,(Filter::SizeType)y}, value );
     }
  }

 }
 
 void laplace( Filter& filter, double const& frequency, double const& shift )
 {
  for( int y=0 ; y < filter.size()[1] ; ++ y )
   {
    auto V = ::math::function::any_to_any<double>( y, 0, (double)filter.size()[1]-1, -1, +1 );

     for( int x=0 ; x < filter.size()[0] ; ++ x )
     {
      auto U = ::math::function::any_to_any<double>( x, 0, (double)filter.size()[0]-1, -1, +1 );
      auto D = sqrt( U*U + V*V );
      if( 1.0 < D ) 
       {
        filter.set( { (Filter::SizeType)x,(Filter::SizeType)y }, 0 ); 
        continue; 
       }
      auto value = ::math::function::gabor<double,1>( math::constants::PHI_div_2, frequency, shift )( D ) ;
      filter.set( { (Filter::SizeType)x,(Filter::SizeType)y}, value );
     }
  }

 }