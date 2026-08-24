#include "./instance.hpp"
#include "../crosser.hpp"
#include <iostream>
#include <iomanip>


namespace S_match::S_feature::S_disparity::S_PatchM{


Instance::Instance()
 {
  m_span = 5;
  m_trash = 0.01;
  m_span  = 2; // LAB 
  m_trash = 9; // LAB 

  m_span  = 4; // RGB 
  m_trash = 0.917; // RGB 

  m_debug = false;
 }

Instance::SizeType Instance::process( ImageGrayType & image, ImageRGBType const& left, ImageRGBType const& right )const
 {
  SizeType result = 0;

  SizeType width  = left.resolution()[0];
  SizeType height = left.resolution()[1];
  image.resolution( { width, height } );
  image.clear( ::color::constant::black_t{} );

  //for( SizeType y= 130; y < 190; ++ y )
  for( SizeType y = 0; y < height; ++y )
   {
    for( SizeType x=0; x < width; ++ x )
     {
      image.set( { x, y }, gray_type( { 0 } ) );
     }

    //   y = 166;
    if( 0==( y%100) ) { std::cout << "%" ; } else { std::cout << ( ( y%10  )  ? "." : "*" ); }
    result += process( image, y, left, right );
   }
  std::cout << "|" << std::endl;
  return result;
 }

Instance::SizeType Instance::process( ImageGrayType & image, SizeType const& y, ImageRGBType const& left, ImageRGBType const& right )const
 {
  auto width  = left.resolution( )[0];
  auto height = left.resolution( )[1];

  m_square.resolution( {width,width} );

  for( SizeType l = 0; l < width; ++l )
   {
    for( SizeType r = 0; r < width; ++r )
     {
       //m_debug = true;
       //l = 321;
       //r = 292;
      auto d = distance_L( { l, y }, left, { r, y }, right );
      m_square.set( { l, r }, d );
      //m_square.set( { r, l }, d );
     }
   }

  m_entangler.global( m_square );
  S_match::S_feature::S_disparity::Crosser( 0 ).process( m_entangler );
  m_entangler.local( m_square );

  SizeType result = 0;

  for( SizeType L=0; L < width; ++ L )
   {
    auto const& R = m_entangler.getR( L );
    if( L != m_entangler.getL( R ) )
     {
      image.set( { L, y }, gray_type( { 0 } ) );
      continue;
     }
    ScalarType delta = ScalarType( R ) - ScalarType( L );
    image.set( { L, y }, gray_type( { delta } ) );
    ++result;
   }

  return result;
 }

Instance::ScalarType Instance::distance_euclid( Size2DType const& leftC, ImageRGBType const& leftI, Size2DType const& rightC, ImageRGBType const& rightI  )const
 {
  ScalarType result = 0;

  auto width = leftI.resolution()[0];
  auto height = leftI.resolution()[1];

  for( int y = -((int)m_span); y < (int)m_span; ++y )
   for( auto x =  -((int)m_span); x < (int)m_span; ++x )
    {
     Size2DType lP{ x +  leftC[0], y +  leftC[1] };  if( width <= lP[0] ) continue;  if(  height <= lP[1] ) continue;
     Size2DType rP{ x + rightC[0], y + rightC[1] } ; if( width <= rP[0] ) continue;  if(  height <= rP[1] ) continue;
     auto const& L = leftI.get( lP );
     auto const& R = rightI.get( rP );
     auto v = color::operation::distance( L, R )/ sqrt( 3 );
     result +=  v;
    }
  return result / ((2*m_span+1)*(2*m_span+1));
 }



Instance::ScalarType Instance::distance_L( Size2DType const& leftC, ImageRGBType const& leftI, Size2DType const& rightC, ImageRGBType const& rightI  )const
 {
  ScalarType result = 0;
  //ImageGrayType mask;  if( true == m_debug ) mask.resolution( { 2*m_span+ 1, 2*m_span+ 1 } );

  auto width  = leftI.resolution()[0];
  auto height = leftI.resolution()[1];

  auto Cl = leftI.get( leftC );
  auto Cr = rightI.get( rightC );
  auto d = color::operation::distance( Cl, Cr );

  double count = 0;
  int lo = (int)m_span;    lo = -lo;
  int hi = (int)m_span+1;

  for( int y = lo; y < hi; ++y )
   for( int x = lo; x < hi; ++x )
    {
     Size2DType lP{ x +  leftC[0], y +  leftC[1] }; if(  width <= lP[0] ) continue;  if(  height <= lP[1] ) continue;
     Size2DType rP{ x + rightC[0], y + rightC[1] }; if(  width <= rP[0] ) continue;  if(  height <= rP[1] ) continue;
     auto const& L = leftI.get( lP );
     auto const& R = rightI.get( rP );
     auto vL = color::operation::distance( L, Cl ) / sqrt( 3 ); 
     auto vR = color::operation::distance( R, Cr ) / sqrt( 3 );
     auto vX = 1 - std::max( vL , vR );
     extern int g_offset0;
     if( vX < m_trash ) { vX =0; }  else { vX = 1; }
     auto c  =  color::operation::distance( L, R )/ sqrt( 3 );
     result += vX *c; count += vX;
     //if( true == m_debug ) mask.set( { x+m_span, y+m_span }, color::gray<double>( { (double)vX } ) );
    }
  if( 0 != count )  result /= count;
  //if( true == m_debug ) graphics::image::save( "mask.png", mask );
  return result ;
 }

Instance::ScalarType Instance::distance_R( Size2DType const& leftC, ImageRGBType const& leftI, Size2DType const& rightC, ImageRGBType const& rightI  )const
 {
  ScalarType result = 0;

  auto width = leftI.resolution()[0];
  auto height = leftI.resolution()[1];

  auto C = rightI.get( rightC );
  int count = 0;
  int lo = (int)m_span;    lo = -lo;
  int hi = (int)m_span;

  for( int y = lo; y < hi; ++y )
   for( int x = lo; x < hi; ++x )
    {
     Size2DType lP{ x + leftC[0], y + leftC[1] };    if(  width <= lP[0] ) continue;  if(  height <= lP[1] ) continue;
     Size2DType rP{ x + rightC[0], y + rightC[1] } ; if(  width <= rP[0] ) continue;  if(  height <= rP[1] ) continue;
     auto const& L = leftI.get( lP );
     auto const& R = rightI.get( rP );
     auto v = color::operation::distance( L, R )/ sqrt( 3 );
     auto c = color::operation::distance( C, R ) / sqrt( 3 );
     if( m_trash < c ) continue;

     result += v; ++count;
    }
  if( 0 != count )  result /= count;
  return result ;
 }

}

