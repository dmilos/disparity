#include "./lasagna.hpp"


Lasagna::Size2DType const&
Lasagna::resolution() const
 {
  if( 0 == m_container.size() )
   {
    static Size2DType s_result{0,0};
    return s_result;
   }
  return m_container[0].size();
 }

Lasagna::ScalarType
Lasagna::get( Size3DType const& coord )const
 {
  if( coord[2] < m_container.size() )
   {
    return m_container[coord[2]].get( { coord[0], coord[1] } );
   }

  return 0;
 }

bool        Lasagna::set( Size3DType const& coord, ScalarType const& v )
 {
  return set( coord[0], coord[1], coord[2], v );
 }

bool        Lasagna::set( Size2DType const& coord, SizeType const& level, ScalarType const& v ) 
 {
  return set( level, coord[0], coord[1], v );
 }

bool        Lasagna::set( SizeType const& x, SizeType const& y, SizeType const& level, ScalarType const& v )
 {
  if( m_container.size() <= level )
   {
    return false;
   }
   m_container[level].set( { x, y }, v );
  return true;
 }
