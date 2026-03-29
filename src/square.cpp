
#include "./square.hpp"

namespace Stereo {

Square::Square()
 {
  m_width  = 0;
  m_height = 0;
  m_range     = 10000;   //!< in pixels
  m_trashold  = 10000;   //!<minimal accepteal distance
  m_proximity = 0;       //!< distance from other
  m_infinity  = 10000.0; //!< lrgest distance
}

void Square::init( SizeType const& width, SizeType const& height )
 {
  m_width = width;
  m_height = height;
  m_distance.resize( width * height, -1 ); std::fill( m_distance.begin(), m_distance.end(), m_infinity );

  m_bestR.resize( width );   clearL();
  m_bestL.resize( height );  clearR();
  m_disparityL.resize( width ); std::fill( m_disparityL.begin(), m_disparityL.end(), 0);
  m_disparityR.resize( height ); std::fill( m_disparityR.begin(), m_disparityR.end(), 0 );
  m_disparityB.resize( std::max( width,height) ); std::fill( m_disparityB.begin(), m_disparityB.end(), 0 );
 }

void Square::processL( )
 {
  for( IntegerType xL=0; xL < (int)m_width; ++xL )
   {
    if( none() != m_bestR[xL] )
     {
      continue;
     }
    auto bR = 0;
    auto eR = std::max<IntegerType>( xL - (IntegerType)m_range, xL ) ;
    SizeType correspondR = bR;
    auto minimum     = m_distance[correspondR * m_width + xL];
    auto competition = m_distance[correspondR * m_width + xL];
    bool haveR = false;
    for( SizeType xR = bR; xR < eR; ++xR )
     {
      if( true == tieR( (IntegerType)xR ) )
       {
        continue;
       }

      auto const& current = m_distance[xR * m_width + xL];
      if( minimum <= current )
       {
        continue;
       }
      haveR = true;
      competition = minimum;
      minimum = current;
      correspondR = xR;
     }

    auto space = fabs( minimum - competition );
    if( ( m_proximity < space ) && ( true == haveR ) && ( minimum < m_trashold ) )
     {
      m_bestR[xL] = (int)correspondR;
     }
     else
     {
      m_bestR[xL] = -1;
     }
     
   }
 }

void Square::processR( )
 {
  for( IntegerType xR = 0; xR < (IntegerType)m_height; ++xR )
   {
    if( none() != m_bestL[xR] )
     {
      continue;
     }
    auto bL = xR;
    auto eL = std::min<IntegerType>( bL+ (IntegerType)m_range, (IntegerType)m_width );
    SizeType correspondL = bL;
    auto minimum     = m_distance[xR * m_width + correspondL];
    auto competition = m_distance[xR * m_width + correspondL];

    bool haveL = false;
    for( SizeType xL = bL; xL < eL; ++xL )
     {
      if( true == tieL( (IntegerType)xL ) )
       {
        continue;
       }
      auto const& current = m_distance[xR * m_width + xL];
      if( minimum <= current )
       {
        continue;
       }
      haveL = true;
      competition = minimum;
      minimum = current;
      correspondL = xL;
     }

    auto space = fabs( minimum - competition );
    if( (m_proximity < space ) && ( true == haveL ) && (minimum < m_trashold) )
     {
      m_bestL[xR] = (int)correspondL;
     }
     else
     {
      m_bestL[xR] = -1;
     }
   }
 }

bool Square::tieL( IntegerType const& L )
 {
  auto R = m_bestR[L];
  if( none() == R )
   {
    return false;
   }
  
  if( L != m_bestL[R] )
   {
    return false;
   }

  return true;
 }
 
bool Square::tieR( IntegerType const& R )
 {
  auto L = m_bestL[R];
  if( none() == L )
   {
    return false;
   }
  
  if( R != m_bestR[L] )
   {
    return false;
   }

  return true;
 }


Square::IntegerType Square::beginL( IntegerType const& pivotR )
 {
  for( IntegerType L = pivotR; L != -1 ; --L )
   {
    if( false == tieL( L ) )
     {
      continue;
     }
    return m_bestR[L]+1;
   }

  return 0;
}
Square::IntegerType Square::beginR( IntegerType const& pivotR )
 {
  for( IntegerType R = pivotR; R != -1 ; --R )
   {
    if( false == tieR( R ) )
     {
      continue;
     }
    return m_bestL[R]+1;
   }

  return 0;
 }

Square::IntegerType Square::endL( IntegerType const& begin )
 {
  for( IntegerType L = begin; L < (SizeType)m_width; ++L )
   {
    if( none() == m_bestR[L] )
     {
      continue;
     }
    return m_bestR[L];
   }

  return (IntegerType)begin;
 }

Square::IntegerType Square::endR( IntegerType const& begin )
 {
  for( IntegerType R = begin; R < (SizeType)m_width; ++R )
   {
    if(  none() != m_bestL[R] )
     {
      continue;
     }
    return m_bestL[R];
   }
  return (IntegerType)m_height;
 }

Square::IntegerType Square::none()
 {
  return -1;
 }


void Square::disparityL()
 {
  for( SizeType xL = 0; xL <  m_width; ++xL )
   {
    if( none() != m_bestR[xL] )
     {
      m_disparityL[xL] =  (int)xL-m_bestR[xL];
     }
    else
     {
      m_disparityL[xL] = 0;
     }
   }
 }

void Square::disparityR()
 {
  for( SizeType xR = 0; xR <  m_height; ++xR )
   {
    if( none() != m_bestL[xR] )
     {
      m_disparityR[ xR ] = m_bestL[xR] - (int)xR;
     }
    else
     {
      m_disparityR[xR] = 0;
     }
   }

 }

void Square::disparityB( )
 {
  for( SizeType L = 0; L < m_width; ++L )
   {
    auto R = m_bestR[L];
    if( none() == R ) { m_disparityB[ L ] = 0; continue; }
    m_disparityB[ L ] = 0;
    if( L != m_bestL[R] ) { m_disparityB[ L ] = 0; continue; }
    m_disparityB[ L ] = (int)L - (int)R;
   }
 }

Square::SizeType Square::purge()
 {
  SizeType result=0;
  for( SizeType L = 0; L < m_width; ++L )
   {
    auto R = m_bestR[L];
    if( none() == R )
     {
      continue;
     }

    if( L == m_bestL[R] )
     {
      continue;
     }

    m_bestR[ L ] = none();
    ++result;
   }

  for( SizeType R = 0; R < m_height; ++R )
   {
    auto L = m_bestL[R];
    if( none() == L )
     {
      continue;
     }

    if( R == m_bestR[L] )
     {
      continue;
     }

    m_bestL[ R ] = none();
    ++result;
   }
  return result;
 }
void Square::clearL()
 {
  std::fill( m_bestR.begin(), m_bestR.end(), none() );
 }

void Square::clearR()
 {
  std::fill( m_bestL.begin(), m_bestL.end(), none() );
 }

bool Square::importL( ImageType const& image, SizeType const& line )
 {
  if( image.cols != m_width ) return false;
  clearL();
  clearR();
  for( IntegerType L = 0; L < m_width; ++L )
   {
    auto D = image.at<std::uint8_t>( (int)line, L );
    if( 0 == D ) { m_bestR[L] = none(); continue; }
    if( L < D  ) { m_bestR[L] = none(); continue; }

    auto R = L - (IntegerType)D;
    m_bestR[L] = R;
    m_bestL[R] = L;
   }

  return true;
 }

 bool Square::importR( ImageType const& imageR, SizeType const& line )
 {
  if( imageR.cols != m_height ) return false;
  clearL();
  clearR();

  for( IntegerType R = 0; R < m_height; ++R )
   {
    auto D = imageR.at<std::uint8_t>( (int)line, R );
    if( 0 == D ) { m_bestL[R] = none(); continue; }
    if( D  < R ) { m_bestL[R] = none(); continue; }

    auto L = (IntegerType)D - R;
    m_bestL[R] = L;
    m_bestR[L] = R;
   }

  return true;
 }


 }