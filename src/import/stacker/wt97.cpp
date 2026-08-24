#include "opencv2/opencv.hpp"

#include "./wt97.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::S_Stacker::WT97::WT97( SizeType const& size, ScalarType const& trash )
 {
  m_debug = false;
  m_size = size;
  m_trash = trash;
 }


namespace
 {

void fwt97(double* x,int n) {
  double a;
  int i;

  // Predict 1
  a=-1.586134342;
  for (i=1;i<n-2;i+=2) {
    x[i]+=a*(x[i-1]+x[i+1]);
  }
  x[n-1]+=2*a*x[n-2];

  // Update 1
  a=-0.05298011854;
  for (i=2;i<n;i+=2) {
    x[i]+=a*(x[i-1]+x[i+1]);
  }
  x[0]+=2*a*x[1];

  // Predict 2
  a=0.8829110762;
  for (i=1;i<n-2;i+=2) {
    x[i]+=a*(x[i-1]+x[i+1]);
  }
  x[n-1]+=2*a*x[n-2];

  // Update 2
  a=0.4435068522;
  for (i=2;i<n;i+=2) {
    x[i]+=a*(x[i-1]+x[i+1]);
  }
  x[0]+=2*a*x[1];

  // Scale
  a=1/1.149604398;
  for (i=0;i<n;i++) {
    if (i%2) x[i]*=a;
    else x[i]/=a;
  }
  /*
  std::vector<double> tempbank; tempbank.resize( n );
  for (i=0;i<n;i++) {
    if (i%2==0) tempbank[i/2]=x[i];
    else tempbank[n/2+i/2]=x[i];
  }
  for (i=0;i<n;i++) x[i]=tempbank[i];
  */
}


 }

bool S_match::S_feature::S_disparity::S_Stacker::WT97::process( LasagnaType &lasagna, ImageType const& image )const
 {
  if( true == m_debug )std::cout << PREFIX << "Window Gray ..." << std::endl;

  SizeType width = image.resolution()[0];
  SizeType height = image.resolution()[1];
  SizeType offset = lasagna.layer().size();

  lasagna.layer().resize( offset + 2*m_size );
  for( SizeType index=0; index <  2*m_size; ++index )
   {
    auto & layer = lasagna.layer()[ offset + index ];
    layer.resolution( image.resolution(), color::gray<double>({0}) );
   }

  std::vector< double > signal( m_size, 0 );

  for( int y=0; y < height; ++y )
   {
    for( int x=0; x < width; ++x )
     {
      auto const&   C = image.get( {(SizeType)x,(SizeType)y} );

      {
       int left = std::max<int>( 0, x - (int)m_size /2 );
       int right = std::min<int>( (int)width, x + (int)m_size /2 );
       
       for( int index = left; index < right; ++index )
        {
         auto const&   c =  image.get( { (SizeType)index, (SizeType)y } );
         signal[index-left] =  color::get::gray( c );
         double distance = color::operation::distance( c, C );
         if( m_trash < distance ) signal[index-left] = 0;
        }
       
       fwt97( signal.data(), (int)signal.size() );
       
       for( SizeType index=0; index < m_size; ++index )
        {
         auto & layer = lasagna.layer()[ offset +      0 +index ];
         ColorType const value( { signal[ index ] } );
         layer.set( { (SizeType)x,(SizeType)y }, value );
        }
      }

      {
      int left = std::max<int>( 0, y - (int)m_size /2 );
      int right = std::min<int>( (int)height, y + (int)m_size /2 );

      for( int index = left; index < right; ++index )
       {
        auto const&   c =  image.get( { (SizeType)x, (SizeType)index } );
        signal[index-left] =  color::get::gray( c );
        double distance = color::operation::distance( c, C );
        if( m_trash < distance ) signal[index-left] = 0;
       }

      fwt97( signal.data(), (int)signal.size() );

      for( SizeType index=0; index < m_size; ++index )
       {
        auto & layer = lasagna.layer()[ offset + m_size + index ];
        ColorType const value( { signal[ index ] } );
        layer.set( { (SizeType)x,(SizeType)y }, value );
       }
      }


     }
   }
  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::WT97::process( DisparityType &disparity, ImageType const& left, ImageType const& right )const
 {
  process( disparity.m_left , left );
  process( disparity.m_right, right );
  return true;
 }

