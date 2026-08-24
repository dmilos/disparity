#include "./base.hpp"

#include <iostream>
#include <iomanip>

#define SMART  1
#define PARTIAL    0
#define ALL  0

S_match::S_feature::S_disparity::EntangleBase::EntangleBase(    )
 {
  m_maxR = 1;
  m_maxL = 1;
 }

 //S_match::S_feature::S_disparity::EntangleBase::NearestType const& S_match::S_feature::S_disparity::EntangleBase::bestL( )const
// {
//  return m_bestL;
// }
//
//S_match::S_feature::S_disparity::EntangleBase::NearestType const& S_match::S_feature::S_disparity::EntangleBase::bestR( )const
// {
//  return m_bestR;
// }

bool     S_match::S_feature::S_disparity::EntangleBase::connect( SizeType const& L, SizeType const& R )
 {
  if( false == validL( L ) ) return false;
  if( false == validR( R ) ) return false;
  m_bestR[ L ] = R;
  m_bestL[ R ] = L;
  return true;
 }

bool     S_match::S_feature::S_disparity::EntangleBase::tie( SizeType const& L, SizeType const& R )const
 {
  if( false == validL( L ) ) return false;
  if( false == validR( R ) ) return false;

  auto iL = getL( R );
  if( false == validL( iL ) ) return false;
  auto iR = getR( L );
  if( false == validR( iR ) ) return false;

  return ( L == iL ) && ( R == iR );
 }

bool     S_match::S_feature::S_disparity::EntangleBase::tieL( SizeType const& L )const
 {
  if( false == validL( L ) ) return false;
  auto R = getR( L );
  if( false == validR( R ) ) return false;
  auto iL = getL( R );
  return L == iL;
 }
bool     S_match::S_feature::S_disparity::EntangleBase::tieR( SizeType const& R )const
 {
  if( false == validR( R ) ) return false;
  auto L = getL( R );
  if( false == validL( L ) ) return false;
  auto iR = getR( L );
  return R == iR;
 }

bool S_match::S_feature::S_disparity::EntangleBase::untieL( SizeType const& L )
 {
  if( false == validL( L ) ) return false;
  auto R = getR( L );
  m_bestR[ L ] = badR();
  m_bestL[ R ] = badL();
  return true;
 }
bool S_match::S_feature::S_disparity::EntangleBase::untieR( SizeType const& R )
 {
  if( false == validR( R ) ) return false;
  auto L = getL( R );
  m_bestL[ R ] = badL();
  m_bestR[ L ] = badR();
  return true;
 }

S_match::S_feature::S_disparity::EntangleBase::SizeType
S_match::S_feature::S_disparity::EntangleBase::getR( SizeType const& L )const
 {
  if( false == validL( L ) ) return badR();
  return m_bestR[ L ];
 }
S_match::S_feature::S_disparity::EntangleBase::SizeType
S_match::S_feature::S_disparity::EntangleBase::getL( SizeType const& R )const
 {
  if( false == validR( R ) ) return badL();
  return m_bestL[ R ];
 }

bool S_match::S_feature::S_disparity::EntangleBase::checkR( SizeType const& L )const
 {
  if( false == validL( L ) ) return false;
  return validR( getR( L ) );
 }
bool S_match::S_feature::S_disparity::EntangleBase::checkL( SizeType const& R )const
 {
  if( false == validR( R ) ) return false;
  return validL( getL( R ) );
 }

bool S_match::S_feature::S_disparity::EntangleBase::spoilR( SizeType const& L )
 {
  m_bestR[ L ] = badR();
  return true;
 }
bool S_match::S_feature::S_disparity::EntangleBase::spoilL( SizeType const& R )
 {
  m_bestL[ R ] = badL();
  return true;
 }

bool S_match::S_feature::S_disparity::EntangleBase::validL( SizeType const& L )const
 {
  return L < m_bestR.size();
 }
bool S_match::S_feature::S_disparity::EntangleBase::validR( SizeType const& R )const
 {
  return R < m_bestL.size();
 }

S_match::S_feature::S_disparity::EntangleBase::SizeType
S_match::S_feature::S_disparity::EntangleBase::purge()
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

 
S_match::S_feature::S_disparity::EntangleBase::SizeType
S_match::S_feature::S_disparity::EntangleBase::limitL( SizeType const& R )const
 { // return upper limit. value is larger than R, can not exced _width_
  //return width;
  SizeType width = m_bestR.size();
  return  SizeType( std::min<SizeType>( width, R + SizeType( width * m_maxL ) ) );
 }

S_match::S_feature::S_disparity::EntangleBase::SizeType
S_match::S_feature::S_disparity::EntangleBase::limitR( SizeType const& L )const
 {  //! Lower limit, can not exceed L, return type is R
  //return 0;
  SizeType height = m_bestL.size();
  return SizeType( std::max<int>(     0, (int)L - (int)( height * m_maxR ) ) );
 }

S_match::S_feature::S_disparity::EntangleBase::SizeType
S_match::S_feature::S_disparity::EntangleBase::badL( )const
 {
  return m_bestR.size();
 }

S_match::S_feature::S_disparity::EntangleBase::SizeType
S_match::S_feature::S_disparity::EntangleBase::badR( )const
 {
  return m_bestL.size();
 }
