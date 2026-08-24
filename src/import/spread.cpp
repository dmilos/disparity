#include "spread.hpp"

#include <iostream>
#include <iomanip>



S_match::S_feature::S_disparity::Spread::Spread( ScalarType const& epsilon  )
 : m_epsilon( epsilon )
 {
 }

void
S_match::S_feature::S_disparity::Spread::prepare( SizeType const& lineno, BankType const& bank, ImageType const& image )
 {
  m_value.resize( image.resolution()[0] );

  Integer2DType corner;
  for( SizeType x=0; x< image.resolution()[0]; ++x )
   {
    m_value[x].resize( bank.size() );
    for( SizeType i=0; i< bank.size(); ++i )
     {
      corner[0] = (int)x      - (int)(bank[i].size()[0]/2);
      corner[1] = (int)lineno - (int)(bank[i].size()[1]/2);
      auto value = graphics::image::convolve::process( bank[i], corner, image ).get<0>();
      m_value[x][i] = value;
     }
   }
 }

void S_match::S_feature::S_disparity::Spread::prepare( SizeType const& lineno, LasagnaType const& lasagna )
 {
  m_value.resize( lasagna.resolution()[0] );

  for( SizeType x=0; x < lasagna.resolution()[0]; ++x )
   {
    m_value[x].resize( lasagna.depth() );
    for( SizeType i=0; i < lasagna.depth(); ++i )
     {
      m_value[x][i] = lasagna.get( { x, lineno, i } );
     }
   }

  return ;
 }

S_match::S_feature::S_disparity::Spread::ScalarType 
S_match::S_feature::S_disparity::Spread::process()
 {
  ScalarType result = 0;
  for( SizeType x = 0; x < m_value.size(); ++x )
   {
    result += process( x );
   }
  return result / m_value.size();
 }

S_match::S_feature::S_disparity::Spread::ScalarType 
S_match::S_feature::S_disparity::Spread::process( SizeType const& x )
 {
  if( m_value[x].size() < 3 )
   {
    return 1;
   }
  auto vektor = m_value[x];
  std::sort( vektor.begin(), vektor.end() );

  ScalarType result = 0;
  SizeType count = 0;
  for( SizeType i=1; i < (int)vektor.size()-1; ++i )
   {
    auto middle =     ( vektor[i+1] + vektor[i-1] )/2;
    auto half   = fabs( vektor[i+1] - vektor[i-1] )/2;
    if( half < m_epsilon ) continue;
    result += fabs( vektor[i]  - middle )/half;
    ++count;
   }
  return ( 0 != count ) ? ( result / count ) : 1;
 }

S_match::S_feature::S_disparity::Spread::ScalarType 
S_match::S_feature::S_disparity::Spread::dispersion( SizeType const& x )
 {
  if( m_value[x].size() < 3 )
   {
    return 1;
   }
  auto vektor = m_value[x];
  std::sort( vektor.begin(), vektor.end() );

  ScalarType result = 0;
  ::math::statistic::gauss::V1< ScalarType >   g1;
  ::math::statistic::gauss::V2< ScalarType >   g2;
  //::math::statistic::gauss::V3< ScalarType >   g3;

  for( SizeType i=0; i < (int)vektor.size()-1; ++i )
   {
    auto delta   = fabs( vektor[i+1] - vektor[i] );
    g1.push( delta );
    //g2.push( delta );
   }
  //  g3.push( delta );
  result = g1.deviation();
  //result = g2.deviation();
  //result = g3.dsipersion();
  return result;
 }

