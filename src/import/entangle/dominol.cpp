#include "./dominol.hpp"

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::EntanglDominoL::EntanglDominoL()
 {
  //m_debug = false;
 }


S_match::S_feature::S_disparity::EntanglDominoL::SizeType 
S_match::S_feature::S_disparity::EntanglDominoL::global( SquareType const& square )
 {
  SizeType result = 0;
  SizeType width  = square.resolution()[0]; m_bestL.resize( width  ); std::fill( m_bestL.begin(), m_bestL.end(), width  );
  SizeType height = square.resolution()[1]; m_bestR.resize( height ); std::fill( m_bestR.begin(), m_bestR.end(), height );


  for( SizeType L=0; L < width; ++L )
   {
    m_bestR[L] = searchR( L, square, limitR( L ), L );
   }

  return result;
 }

S_match::S_feature::S_disparity::EntanglDominoL::SizeType 
S_match::S_feature::S_disparity::EntanglDominoL::searchR( SizeType const& L, SquareType const& square, SizeType const& limitR_A, SizeType const& limitR_B )const
 {
  SizeType result = badR();
  SizeType width  = m_bestR.size();
  SizeType height = m_bestL.size();

  ScalarType best = 1e6; //!< INFINITY
  bool noise = true;

   for( SizeType R = limitR_A; R < limitR_B; ++R  )
   {
    auto const distance = square.get( { L, R } ); 
    if( distance < best )
     {
      best = distance;
      result = R;
     }
   }
  return result;
 }