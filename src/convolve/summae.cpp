#include "./filter.hpp"

double summae( Filter const& filter )
 {
  Filter::ScalarType result = 0;

  auto filter_ptr = filter.data();

  auto total = filter.size()[0] * filter.size()[1];
  for( int index = 0; index < total; ++index )
  //int index= total; while( index-- )
   {
    result += filter_ptr[index] ;
   // result +=  *filter_ptr; ++filter_ptr;
   }
  return result;

  for(  Filter::SizeType y=0; y < filter.size()[1]; ++y )
   {
    for(  Filter::SizeType x=0; x < filter.size()[0]; ++x )
     {
      result += filter.get( {x,y} );
     }
   }
  return result;
 }