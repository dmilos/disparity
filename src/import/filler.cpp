#include "filler.hpp"

#include <iostream>
#include <iomanip>

S_match::S_feature::S_disparity::Filler::Filler()
 {
  m_zero = color::constant::black_t{};
 }

S_match::S_feature::S_disparity::Filler::SizeType
S_match::S_feature::S_disparity::Filler::process( ImageType  & image  )
 {
  SizeType result = 0;
  for( int i=0 ; i < 10; ++i  )
   {
    SizeType partial = 0;
    SizeType X = 0, Y = 0;
    for( int i=0 ; i < 20; ++i  )
     {
      X  = processX( image );   partial +=  X; // std::cout <<  "X: " << X  << std::endl;
      Y  = processY( image );   partial +=  Y; // std::cout <<  "Y: " << Y  << std::endl;
      if( ( 0 == X ) && ( 0 == Y ) ) break;
     }
    SizeType X2 = 0, Y2 = 0;
    for( int i=0 ; i < 20; ++i  )
     {
      X2 = processX2( image, 2 );  partial += X2; // std::cout << "X2: " << X2 << std::endl;
      Y2 = processY2( image, 2 );  partial += Y2; // std::cout << "Y2: " << Y2 << std::endl;
      if( ( 0 == X2 ) && ( 0 == Y2 ) ) break;
     }
    if( 0 == partial ) break;
    result += partial;
   }

  return result;
 }

S_match::S_feature::S_disparity::Filler::SizeType
S_match::S_feature::S_disparity::Filler::processX( ImageType  & image  )
 {
  SizeType result =0;
  //double summae = 0;

  SizeType height0 = image.resolution()[1];
  SizeType height1 = height0 - 1;
  SizeType width0 = image.resolution()[0];
  SizeType width1 = width0 - 1;

  for( SizeType y = 0; y < height0; ++y )
   {
    for( SizeType x = 1; x < width1; ++x )
     {
      auto  const& pixelLeft = image.get( {x-1,y} );
      if( m_zero == pixelLeft )
       {
        continue;
       }
      auto   & pixelMiddle = image.get( {x,y} );
      if( m_zero != pixelMiddle )
       {
        continue;
       }
      auto const & pixelRight = image.get( {x+1,y} );
      if( m_zero == pixelRight )
       {
        continue;
       }
      //if( m_trash < fabs( pixelRight[0] - pixelLeft[0] ) )
      //  {
      //   continue;
      //  }
      pixelMiddle =  (pixelLeft + pixelRight )/2.0;
      //summae += fabs( pixelLeft[0] - pixelRight[0] );
      ++result;
     }
   }
  //std::cout
  //    << "R: " << result << "; "
  //    << "A: " << ( 0!=result ? (summae / result ): -1 )  << "; "
  //    << std::endl;
  return result;
 }

S_match::S_feature::S_disparity::Filler::SizeType
S_match::S_feature::S_disparity::Filler::processX2( ImageType  & image, SizeType const& gap )
 {
  SizeType result =0;
  double summae =0;

  SizeType height0 = image.resolution()[1];
  SizeType width0 = image.resolution()[0];
  SizeType width2 = width0 - 1 - gap;

  for( SizeType y = 0; y < height0; ++y )
   {
    for( SizeType x = 0; x < width2; ++x )
     {
      auto const & pixelP = image.get( {x,y} );
      if( m_zero == pixelP ){ continue; }
      auto const & pixelM = image.get( {x+gap+1,y} );
      if( m_zero == pixelM ){ continue; }

      bool skip = false;
      for( SizeType pos=0; pos < gap; ++ pos  )
       {
        if( m_zero != image.get( { x + 1 + pos, y } ) )
         {
          skip = true;
          break;
         }
       }
      if( true == skip )
       {
        continue;
       }

      for( SizeType pos=0; pos < gap; ++ pos  )
       {
        image.set( {x+pos+1,y}, ( ( (pos+1.0)/(gap+1.0))*pixelP + ( ( gap - pos )/( gap+1.0))*pixelM ) );
       }

      summae += fabs( pixelP[0] - pixelM[0] );
      result += gap;
     }
   }
  //std::cout << "A: " << summae / result << std::endl;
  return result;
 }

S_match::S_feature::S_disparity::Filler::SizeType
S_match::S_feature::S_disparity::Filler::processY( ImageType  & image  )
 {
  SizeType result =0;

  SizeType width0 = image.resolution()[0];
  SizeType height0 = image.resolution()[1];
  SizeType height1 = height0 - 1;

  for( SizeType x = 0; x < width0; ++x )
   for( SizeType y = 1; y < height1; ++y )
   {
     {
      auto const & pixelUp = image.get( {x,y-1} );
      if( m_zero == pixelUp )
       {
        continue;
       }
      auto    & pixelMiddle = image.get( {x,y} );
      if( m_zero != pixelMiddle )
       {
        continue;
       }
      auto const & pixelDown = image.get( {x,y+1} );
      if( m_zero == pixelDown )
       {
        continue;
       }

      pixelMiddle = (pixelDown + pixelUp )/2.0;
      ++result;
     }
   }
  return result;
 }

S_match::S_feature::S_disparity::Filler::SizeType
S_match::S_feature::S_disparity::Filler::processY2( ImageType  & image, SizeType const& gap )
 {
  SizeType result =0;
  //double summae =0;

  SizeType height0 = image.resolution()[1];
  SizeType height3 = height0 -1- gap;
  SizeType width0 = image.resolution()[0];
  SizeType width2 = width0;

  for( SizeType x = 0; x < width0; ++x )
   {
    for( SizeType y = 0; y < height3; ++y )
     {
      auto const & pixelP = image.get( { x, y } );
      if( m_zero == pixelP ){ continue; }
      auto const & pixelM = image.get( { x, y + 1 + gap } );
      if( m_zero == pixelM ){ continue; }

      bool skip = false;
      for( SizeType pos=0; pos < gap; ++ pos  )
       {
        if( m_zero != image.get( {x , y + 1 + pos } ) )
         {
          skip = true;
          break;
         }
       }
      if( true == skip )
       {
        continue;
       }

      for( SizeType pos=0; pos < gap; ++ pos  )
       {
        image.set( {x,y+pos}, ( ( (pos+1.0)/(gap+1.0))*pixelP + ( ( gap - pos )/( gap+1.0))*pixelM ) );
       }

      result += gap;
     }
   }
  //std::cout << "A: " << summae / result << std::endl;
  return result;
 }

