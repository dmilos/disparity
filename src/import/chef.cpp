#include "./chef.hpp"
#include "./stacker/convolve.hpp"

namespace S_match::S_feature::S_disparity{


Chef::Chef()
 {


 }

Chef::SizeType Chef::process( ImageGrayType  & image, ImageRGBType const& left, ImageRGBType const& right )const
 {
  m_disparity.clear();
  bank_type bank;   bank.reserve( 100 );
  make_bank(  bank  );
  m_leftG  = left; 
  m_rightG = right; 
  S_match::S_feature::S_disparity::S_Stacker::Convolve().process( m_disparity, bank, m_leftG, m_rightG );

  return m_disparity.process( image );
 }

Chef::filter_type  Chef::single_gabor( SizeType size, ScalarType angle, ScalarType frequency, ScalarType shift, std::array<ScalarType,2> const& scale )
 {
  filter_type result;
  result.size( { size,size } );
  graphics::image::convolve::library::gabor( result, angle, math::constants::PHI_invSQRT2, frequency, shift, scale );
  graphics::image::convolve::filter::normalize( result );

  return result;
 }

 void Chef::make_bank(  bank_type & bank  )
  {
   typedef std::vector<int> parameter_type;
   parameter_type parameter;
              // 017
#define OFF(a) parameter.push_back( a )

OFF(  15 ); OFF(  10 ); OFF( 170 ); OFF( 165 ); OFF(  15 ); OFF(  15 ); 
OFF( 150 ); OFF( 115 ); OFF(  35 ); OFF( 170 ); OFF(  35 ); OFF( 140 ); 
OFF(  -1 ); OFF(  -1 ); OFF(  30 ); OFF( 130 ); OFF(  -1 ); OFF( 115 ); 

OFF(  -1 ); OFF(   0 ); OFF( 115 ); OFF(  10 ); OFF( 170 ); OFF( 105 ); 
OFF(  -1 ); OFF(  -1 ); OFF(  10 ); OFF(  -1 ); OFF(  -1 ); OFF(  25 ); 
OFF(  -1 ); OFF(  -1 ); OFF(  50 ); OFF(  -1 ); OFF(  -1 ); OFF(  30 ); 

OFF(  -5 ); OFF(  -5 ); OFF( 100 ); OFF( 140 ); OFF(  -5 ); OFF(  90 ); 
OFF(  -5 ); OFF(  -5 ); OFF(  20 ); OFF(  -5 ); OFF(  -5 ); OFF(  95 ); 
OFF(  -1 ); OFF(  -5 ); OFF( 175 ); OFF(  -5 ); OFF(  -5 ); OFF(  -5 ); 

OFF(  -5 ); OFF(  -5 ); OFF(   5 ); OFF(  -5 ); OFF(  -5 ); OFF(  15 ); 
OFF(  -5 ); OFF(  -5 ); OFF(  90 ); OFF(  -5 ); OFF(  -5 ); OFF(  90 ); 
OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); OFF(  -5 ); OFF(  -5 ); OFF(  -5 ); 

OFF(  -5 ); OFF(  20 ); OFF(  10 ); OFF(  -5 ); OFF(  -5 ); OFF(  15 ); 
OFF(  -5 ); OFF(  -5 ); OFF( 155 ); OFF(  -5 ); OFF(  -5 ); OFF(  10 ); 
OFF(  -1 ); OFF(  -5 ); OFF(  -5 ); OFF(   5 ); OFF(  -5 ); OFF( 155 ); 

OFF(  -1 ); OFF(  -1 ); OFF(  35 ); OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); 
OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); 
OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); 

OFF(  -1 ); OFF(  -1 ); OFF(   5 ); OFF(  -1 ); OFF(  35 ); OFF(   0 ); 
OFF(  -1 ); OFF(  -1 ); OFF( 145 ); OFF( 175 ); OFF(  -1 ); OFF(  -5 ); 
OFF(  -1 ); OFF(  -1 ); OFF( 125 ); OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); 

OFF(  -1 ); OFF(  -1 ); OFF(  40 ); OFF(  -1 ); OFF(  -1 ); OFF(  30 ); 
OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); 
OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); OFF(  -1 ); OFF(  -1 ); OFF(  -5 ); 


#undef OFF

#define GABOR(DP_SIZE,DP_ANGLE,DP_FREQ,DP_SHIFT) \
 single_gabor( (std::size_t)DP_SIZE, ::math::geometry::deg2rad<double>(DP_ANGLE), DP_FREQ,::math::geometry::deg2rad<double>(DP_SHIFT), {1,1} )

  int index=0;
  for( auto size: { 20, 18, 16, 14, 12, 10, 8, 6 } )
   for( int count=0; count < 3; ++count )
    {
     if( 0 <= parameter[ index ] ) { bank.push_back( GABOR(  size, parameter[ index ],  0.500,   90 ) ); } index++;
     if( 0 <= parameter[ index ] ) { bank.push_back( GABOR(  size, parameter[ index ],  1.000,   90 ) ); } index++;
     if( 0 <= parameter[ index ] ) { bank.push_back( GABOR(  size, parameter[ index ],  1.500,   90 ) ); } index++;
     if( 0 <= parameter[ index ] ) { bank.push_back( GABOR(  size, parameter[ index ],  0.619,    0 ) ); } index++;
     if( 0 <= parameter[ index ] ) { bank.push_back( GABOR(  size, parameter[ index ],  1.1255,   0 ) ); } index++;
     if( 0 <= parameter[ index ] ) { bank.push_back( GABOR(  size, parameter[ index ],  1.6283,   0 ) ); } index++;
    }
  }
}

