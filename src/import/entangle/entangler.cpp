#include "entangler.hpp"

#include <iostream>
#include <iomanip>

// SMART pravi opasne probleme
#define SMART  0       
#define PARTIAL    0   
#define ALL  1

S_match::S_feature::S_disparity::Entangler::Entangler( /*ScalarType const& trash, ScalarType const& proximity*/  )
 //: m_trash( trash ) ,  m_proximity( proximity )
 {
  m_proximity = 1e-1; //!< maximal proximity
  m_trash     = 1e-5; //!< competirors distance

  m_proximity = 100;   //!< maximal proximity
  m_trash     = 1e-8;  //!< competirors distance
  m_maxR = 0.35; 
  m_maxL = 0.35;
 }

bool S_match::S_feature::S_disparity::Entangler::proximity( ScalarType const& p )
 {
  m_proximity = p;
  return true;
 }

bool S_match::S_feature::S_disparity::Entangler::trash( ScalarType const& t )
 {
  m_trash = t;
  return true;
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::global( SquareType const& square )
 {
  m_statSpan = 0;
  SizeType  width = square.resolution()[0];
  SizeType height = square.resolution()[1];

  m_bestL.resize( height );
  m_bestR.resize( width );

  for( SizeType L=0; L < width; ++L )
   {

#if 1 == SMART
    m_bestR[L] = searchR( L, square, limitR( L ), L );
#elif   1 == PARTIAL
    m_bestR[L] = searchR( L, square,  0, L );
#elif   1 == ALL
    m_bestR[L] = searchR( L, square,  0, width );
#endif
   }

  for( SizeType R=0; R < height; ++R )
   {
#if 1 == SMART
    m_bestL[R] = searchL( R, square, R, limitL( R ) );
#elif  1 == PARTIAL
    m_bestL[R] = searchL( R, square, R, height );
#elif 1 == ALL
    m_bestL[R] = searchL( R, square, 0, height );
#endif
   }

  purge();
  //std::cout << m_statSpan <<  std::endl;
  return 0;
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::local( SquareType const& square )
 {
  SizeType result = 0;
  result += localR( square );
  result += localL( square );
  purge();
  return result;
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::localL( SquareType const& square )
 {
  SizeType result = 0;
  SizeType width  = m_bestR.size();
  SizeType height = m_bestL.size();

  SizeType R0 = 0;
  for( SizeType L0=0; L0 < width; ++L0 )
   {
    if( true == tieL( L0 ) )
     {
      R0 = getR( L0 );
      continue;
     }

    SizeType R1 = height;
    SizeType L1 = L0;
    for( ; L1 < width; ++L1 )
     {
      if( true == tieL( L1 ) )
       {
        R1 = getR( L1 );
        break;
       }
     }

    for( SizeType L = L0; L < L1; ++ L )
     {
      //m_bestR[L] = searchR( L, square, R0+1, std::min( L, R1 ) );
      m_bestR[L] = searchR( L, square, R0+1, R1 );
      ++result;
     }
    L0 = L1; --L0;
   }
  return result;
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::localR( SquareType const& square )
 {
  SizeType result = 0;
  SizeType width  = m_bestR.size();
  SizeType height = m_bestL.size();

  SizeType L0 = 0;
  for( SizeType R0=0; R0 < height; ++R0 )
   {
    if( true == tieR( R0 ) )
     {
      L0 = getL( R0 );
      continue;
     }

    SizeType L1 = width;
    SizeType R1=R0+1;
    for( ; R1 < height; ++R1 )
     {
      if( true == tieR( R1 ) )
       {
        L1 = getL( R1 );
        break;
       }
     }

    for( SizeType R = R0; R < R1; ++ R )
     {
      //m_bestL[R] = searchL( R, square, std::max( L0+1, R ), L1 );
      m_bestL[R] = searchL( R, square, L0+1, L1 );
      ++result;
     }
    R0 = R1; --R0;
   }
  return result;
 }

//S_match::S_feature::S_disparity::Entangler::NearestType const& S_match::S_feature::S_disparity::Entangler::bestL( )const
// {
//  return m_bestL;
// }
//
//S_match::S_feature::S_disparity::Entangler::NearestType const& S_match::S_feature::S_disparity::Entangler::bestR( )const
// {
//  return m_bestR; 
// }

bool     S_match::S_feature::S_disparity::Entangler::connect( SizeType const& L, SizeType const& R )
 {
  if( false == validL( L ) ) return false;
  if( false == validR( R ) ) return false;
  m_bestR[ L ] = R;
  m_bestL[ R ] = L;
  return true;
 }

bool     S_match::S_feature::S_disparity::Entangler::tie( SizeType const& L, SizeType const& R )const
 {
  if( false == validL( L ) ) return false;
  if( false == validR( R ) ) return false;

  auto iL = getL( R );
  if( false == validL( iL ) ) return false;
  auto iR = getR( L );
  if( false == validR( iR ) ) return false;

  return ( L == iL ) && ( R == iR );
 }

bool     S_match::S_feature::S_disparity::Entangler::tieL( SizeType const& L )const
 {
  if( false == validL( L ) ) return false;
  auto R = getR( L );
  if( false == validR( R ) ) return false;
  auto iL = getL( R );
  return L == iL;
 }
bool     S_match::S_feature::S_disparity::Entangler::tieR( SizeType const& R )const
 {
  if( false == validR( R ) ) return false;
  auto L = getL( R );
  if( false == validL( L ) ) return false;
  auto iR = getR( L );
  return R == iR;
 }

bool S_match::S_feature::S_disparity::Entangler::untieL( SizeType const& L )
 {
  if( false == validL( L ) ) return false;
  auto R = getR( L );
  m_bestR[ L ] = badR();
  m_bestL[ R ] = badL();
  return true;
 }
bool S_match::S_feature::S_disparity::Entangler::untieR( SizeType const& R )
 {
  if( false == validR( R ) ) return false;
  auto L = getL( R );
  m_bestL[ R ] = badL();
  m_bestR[ L ] = badR();
  return true;
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::getR( SizeType const& L )const
 {
  if( false == validL( L ) ) return badR();
  return m_bestR[ L ];
 }
S_match::S_feature::S_disparity::Entangler::SizeType  
S_match::S_feature::S_disparity::Entangler::getL( SizeType const& R )const
 {
  if( false == validR( R ) ) return badL();
  return m_bestL[ R ];
 }

bool S_match::S_feature::S_disparity::Entangler::checkR( SizeType const& L )const
 {
  if( false == validL( L ) ) return false;
  return validR( getR( L ) );
 }
bool S_match::S_feature::S_disparity::Entangler::checkL( SizeType const& R )const
 {
  if( false == validR( R ) ) return false;
  return validL( getL( R ) );
 }

bool S_match::S_feature::S_disparity::Entangler::spoilR( SizeType const& L )
 {
  m_bestR[ L ] = badR();
  return true;
 }
bool S_match::S_feature::S_disparity::Entangler::spoilL( SizeType const& R )
 {
  m_bestL[ R ] = badL();
  return true;
 }

bool S_match::S_feature::S_disparity::Entangler::validL( SizeType const& L )const
 {
  return L < m_bestR.size();
 }
bool S_match::S_feature::S_disparity::Entangler::validR( SizeType const& R )const
 {
  return R < m_bestL.size();
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::purge()
 {
  SizeType result = 0;
  SizeType width  = m_bestR.size();
  SizeType height = m_bestL.size();

  for( SizeType L=0; L < width; ++L )
   {
    if( true == tieL( L ) ) continue;
    spoilR( L );
    ++result;
   }
  for( SizeType R=0; R < height; ++R )
   {
    if( true == tieR( R ) ) continue;
    spoilL( R );
    ++result;
   }
  return result;
 }

S_match::S_feature::S_disparity::Entangler::SizeType 
S_match::S_feature::S_disparity::Entangler::searchR( SizeType const& L, SquareType const& square, SizeType const& limitR_A, SizeType const& limitR_B )const
 {
  SizeType result = badR();
  SizeType width  = m_bestR.size();
  SizeType height = m_bestL.size();

  ScalarType best = 1e6; //!< INFINITY
  bool noise = true;

   for( SizeType R = limitR_A; R < limitR_B; ++R  )
   {
    auto const distance =  square.get( { L, R } );  m_statSpan = std::max( distance, m_statSpan );
    if( m_proximity < distance )
      {
       //m_proximityCount++;
       continue;
      }
    if( distance < best )
     {
      auto delta = fabs( distance - best );
      if( delta < m_trash ) //!< noise = ( delta < m_trash ? true : false );
       {
        noise = true;
       }
      else
       {
        noise = false;
       }
      best = distance;
      result = R;
     }
   }
  return ( true == noise ) ? badR() : result;
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::searchL( SizeType const& R, SquareType const& square, SizeType const& limitL_A, SizeType const& limitL_B )const
 {
  SizeType result = badL();
  SizeType width  = m_bestR.size();
  SizeType height = m_bestL.size();

  ScalarType best = 1e6; //!< INFINITY  sqrt( 2*std::max(width,height))
  bool noise = true;
  for( SizeType L = limitL_A; L < limitL_B; ++L  )
   {
    auto const distance =  square.get( { L, R } );  m_statSpan = std::max( distance, m_statSpan );
    if( m_proximity < distance )
      {
       //m_proximityCount++;
       continue;
      }
    if( distance < best )
     {
      auto delta = fabs( distance - best );
      if( delta < m_trash )  //!< noise = ( delta < m_trash ? true : false );
       {
        noise = true;
       }
      else
       {
        noise = false;
       }

      best = distance;
      result = L;
     }
   }
  return ( true == noise ) ? badL() : result;
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::limitL( SizeType const& R )const
 { // return upper limit. value is larger than R, can not exced _width_
  //return width; 
  SizeType width = m_bestR.size();
  return  SizeType( std::min<SizeType>( width, R + SizeType( width * m_maxL ) ) );
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::limitR( SizeType const& L )const
 {  //! Lower limit, can not exceed L, return type is R
  //return 0; 
  SizeType height = m_bestL.size();
  return SizeType( std::max<int>(     0, (int)L - (int)( height * m_maxR ) ) );
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::badL( )const
 {
  return m_bestR.size();
 }

S_match::S_feature::S_disparity::Entangler::SizeType
S_match::S_feature::S_disparity::Entangler::badR( )const
 {
  return m_bestL.size();
 }
