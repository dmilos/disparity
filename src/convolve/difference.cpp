#include "./filter.hpp"

bool difference( Filter & result, Filter const& left, Filter const& right)
 {
  if( left.size() != right.size() ) return false;
  if( result.size() != right.size() )result.size( left.size() );

  auto result_ptr = result.data();
  auto left_ptr = left.data();
  auto right_ptr = right.data();

  auto total = result.size()[0] * result.size()[1];
  for( int index = 0; index < total; ++index )
   {
    result_ptr[index] =  left_ptr[index] - right_ptr[index];
    //*result_ptr = *left_ptr - *right_ptr;
    //++result_ptr;
    //++left_ptr;
    //++right_ptr;
   } 
  return true;

  for(  Filter::SizeType y=0; y < result.size()[1]; ++y )
   {
    for(  Filter::SizeType x=0; x < result.size()[0]; ++x )
     {
      auto const& L =  left.get( {x,y} );
      auto const& R =  right.get( {x,y} );

      result.set( {x,y},  L-R  );

     }
   }
  return true;
 }