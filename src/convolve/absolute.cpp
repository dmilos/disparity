#include "./filter.hpp"

bool absolute( Filter & filter )
 {
  auto result_ptr = filter.data();

  auto total = filter.size()[0] * filter.size()[1];
  for( int index = 0; index < total; ++index )
   {
    result_ptr[index] = fabs( result_ptr[index] );
    //*result_ptr  = fabs( *result_ptr ); ++result_ptr;
   } 
  return true;

  for(  Filter::SizeType y=0; y < filter.size()[1]; ++y )
   {
    for(  Filter::SizeType x=0; x < filter.size()[0]; ++x )
     {

      filter.set( {x,y}, fabs( filter.get( {x,y} ) ) );

     }
   }
  return true;
 }

bool absolute( Filter & result, Filter const& left, Filter const& right)
 {
  if( left.size() != right.size() ) return false;
  if( result.size() != right.size() )result.size( left.size() );

  for(  Filter::SizeType y=0; y < result.size()[1]; ++y )
   {
    for(  Filter::SizeType x=0; x < result.size()[0]; ++x )
     {
      auto const& L =  left.get( {x,y} );
      auto const& R =  right.get( {x,y} );

      result.set( {x,y}, fabs( L - R ) );

     }
   }
  return true;
 }