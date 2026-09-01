#include "feature.hpp"

#include <iostream>
#include <iomanip>



S_match::S_feature::S_disparity::Feature::Feature(  )
 {
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::distance( TypeType const& left, TypeType const& right )
 {
  /*
  extern int g_offset0;
  switch( g_offset0 )
   {
    case( 0): return absolute(  left,  right );
    case( 1): return dot_abs(  left,  right );
    case( 2): return euclid(  left,  right );
    case( 3): return euclid_normed(  left,  right );
    case( 4): return correlation(  left,  right );
    case( 5): return vector_angle(  left,  right );
    case( 6): return average_minimum(  left,  right );
    case( 7): return average_maximum(  left,  right );
    case( 8): return partial_maximum(  left,  right );
    case( 9): return hamming(  left,  right );
    case(10): absolute_trim(  left,  right );
    case(10): absolute_truncate(  left,  right );
    case(10): suport_weight(  left,  right );
   }
  */
  return absolute( left, right );
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::dot_abs( TypeType const& left, TypeType const& right )
 {
  ScalarType result = 0;
  SizeType len = std::min( left.size(), right.size() );

  for( SizeType i=0 ; i < len; ++i )
   {
    ScalarType a = fabs( left[i] * right[i] );
    result += a;
   }
  result = sqrt( result / len );
  return result;
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::euclid( TypeType const& left, TypeType const& right )
 {
  ScalarType result = 0;
  SizeType len = std::min( left.size(), right.size() );

  for( SizeType i=0 ; i < len; ++i )
   {
    ScalarType a = left[i] - right[i];
    result += a*a;
   }
  result = sqrt( result / len );
  return result;
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::euclid_normed( TypeType const& left, TypeType const& right )
 {
  ScalarType result = 0;
  ScalarType x2 = 0;
  ScalarType y2 = 0;
  SizeType len = std::min( left.size(), right.size() );

  for( SizeType i=0 ; i < len; ++i )
   {
    ScalarType a = left[i] - right[i];
    result += a*a;
    x2 += left[i]*left[i];
    y2 += right[i]*right[i];
   }
  result = sqrt( result / sqrt( x2 * y2 ) );
  return result;
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::correlation( TypeType const& left, TypeType const& right )
 {
  ScalarType result = 0;
  SizeType len = std::min( left.size(), right. size() );


  ScalarType xx = 0;
  ScalarType x = 0;

  ScalarType xy = 0;

  ScalarType yy = 0;
  ScalarType y = 0;

  for( SizeType i=0 ; i < len; ++i )
   {
    auto const L = left[i];
    auto const R = right[i];

    xx += L*L;
    x  += L;

    xy += L * R;

    yy += R*R;
    y += R;
   }

  result =  ( xy-x*y) / sqrt( ( xx-x*x) *( yy-y*y ) );
  return result;
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::vector_angle( TypeType const& left, TypeType const& right )
 {
  ScalarType result = 0;
  SizeType len = std::min( left.size(), right. size() );

  ScalarType ls = 0;
  ScalarType rs = 0;

  for( SizeType i=0 ; i < len; ++i )
   {
    auto const L = left[i];
    auto const R = right[i];

    result += fabs( L * R ) ;
    ls  +=  L*L;
    rs  +=  R*R;
   }

  result /=  sqrt( ls * rs );
  return result;
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::absolute( TypeType const& left, TypeType const& right )
 {
  ScalarType result = 0;
  SizeType len = std::min( left.size(), right.size() );

  for( SizeType i=0 ; i < len; ++i )
   {
    ScalarType a = left[i] - right[i];
    result += fabs( a );
   }
  result = result / len;
  return result;
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::average_minimum( TypeType const& left, TypeType const& right )
 {
  ScalarType result = 0;
  SizeType len = std::min( left.size(), right. size() );

  m_temp.resize( len );

  for( SizeType i=0 ; i < len; ++i )
   {
    ScalarType a = fabs( left[i] - right[i] );
    m_temp[ i ] = a;
   }
  std::sort( m_temp.begin(), m_temp.end() );
  // extern int g_entanglerP;
  SizeType sub_len = std::min<SizeType>( 10/*g_entanglerP*/, len );

  for( SizeType i=0 ; i < sub_len; ++i )
   {
    result += m_temp[ i ];
   }
  result /= sub_len;

  return result;
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::average_maximum( TypeType const& left, TypeType const& right )
 {
  ScalarType result = 0;
  SizeType len = std::min( left.size(), right.size() );

  m_temp.resize( len );

  for( SizeType i=0 ; i < len; ++i )
   {
    ScalarType a = fabs( left[i] - right[i] );
    m_temp[ i ] = a;
   }
  std::sort( m_temp.rbegin(), m_temp.rend() );
  // extern int g_entanglerP;
  //SizeType sub_len = std::min<SizeType>( 10/*g_entanglerP*/, len  );
  SizeType sub_len =   len / 3;

  for( SizeType i=0 ; i < sub_len; ++i )
   {
    result += m_temp[ i ];
   }
  result /= sub_len;

  return result;
 }


S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::partial_maximum( TypeType const& left, TypeType const& right )
 {
  SizeType len = std::min( left.size(), right.size() );

  SizeType total = 5; //extern int g_index; total = g_index;
  ScalarType result = - (ScalarType)len;
  //ScalarType summae = 0; //!< debug

  for( int piece =0; piece < total; ++piece )
   {
    ScalarType partial = 0;
    SizeType B = (piece * len ) /total;
    SizeType E = ( (piece + 1) * len ) /total;

    for( SizeType i = B ; i < E ; ++i )
     {
      ScalarType a = fabs( left[i] - right[i] );
      partial += a;
     }
     //summae += partial;     //!< debug
     result = std::max( result, partial );
   }
  result /= len/total;

  //auto a = absolute( left, right );
  //if( result != a )
  // {
  //  result = result;
  // }
  return result;
 }


S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::hamming( TypeType const& left, TypeType const& right )
 {
  ScalarType result = 0;
  SizeType len = std::min( left.size(), right.size() );

  for( SizeType i=0 ; i < len; ++i )
   {
    ScalarType a = fabs( left[i] - right[i] );
    if( a < ( 1.0 / len ) )  ++result;
   }

  result /= len;

  return result;
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::absolute_trim( TypeType const& left, TypeType const& right )
 {

  extern int g_offset0;
  extern int g_offset1;
  extern int g_offset3;

  ScalarType trash = 3.0/100.0;
  //ScalarType mid   = g_offset1/100.0;
  ScalarType over  = 4.0/100.0;

  ScalarType result = 0;
  SizeType len = std::min( left.size(), right.size() );

  for( SizeType i=0 ; i < len; ++i )
   {
    ScalarType a = fabs( left[i] - right[i] );
    if( a < trash ) a = 0;
    if( over < a  ) a *= 2;
    result += a;
   }

  result /= len;

  return result;
 }


S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::absolute_truncate( TypeType const& left, TypeType const& right )
 {
  extern int g_offset0;

  //ScalarType T = math::function::any_to_any<double>( 17, 0, 30, 0.04, 0.06 ); 
  ScalarType T = math::function::any_to_any<double>( 20, 0, 30, 0.00, 0.01 ); 

  //ScalarType T = math::function::any_to_any<double>( g_offset0, 0, 30, 0.0, 0.1 ); 

  ScalarType result = 0;
  SizeType len = std::min( left.size(), right.size() );

  for( SizeType i=0 ; i < len; ++i )
   {
    ScalarType a = fabs( left[i] - right[i] );
    if( T < a  ) a = T;
    result += a;
   }

  result /= len;

  return result;
 }

S_match::S_feature::S_disparity::Feature::ScalarType
S_match::S_feature::S_disparity::Feature::suport_weight( TypeType const& left, TypeType const& right )
 {
  //extern int g_offset0;

  //ScalarType T = g_offset1 / 100.0;
  
  ScalarType A = 0;  
  ScalarType B = 0;

  SizeType len = std::min( left.size(), right.size() );
  for( SizeType i=0 ; i < len; i += 4 )
   {
    ScalarType wL =  left[ i + 0 + 0 ] ;
    ScalarType rL =  left[ i + 1 + 0 ];
    ScalarType gL =  left[ i + 1 + 1 ];
    ScalarType bL =  left[ i + 1 + 2 ];

    ScalarType wR =  right[ i + 0 + 0 ] ;
    ScalarType rR =  right[ i + 1 + 0 ];
    ScalarType gR =  right[ i + 1 + 1 ];
    ScalarType bR =  right[ i + 1 + 2 ];

    ScalarType d  = fabs( rL - rR ) + fabs( gL - gR ) + fabs( bL - bR );

    ScalarType E  =  d; //  if( E < T ) E = 0;

    A += wL * wR * E;
    B += wL * wR;
   }

  ScalarType result = A / B;

  return result;
 }
