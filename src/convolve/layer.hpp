#pragma once
#include <array>
#include <vector>
#include <string>

class Layer
 {
  public:
    typedef double ScalarType;
    typedef std::array<std::size_t,2>  Size2DType;
    typedef std::vector<ScalarType> ContainerType;

    ScalarType const * data()const { return m_container.data(); }
    ScalarType       * data()      { return m_container.data(); }

    Size2DType const& size()const{ return m_size; }
    bool size( Size2DType const& S ){  m_size = S; m_container.resize(  m_size[0]  * m_size[1] ); return true; }

    ScalarType const& get( Size2DType const& location )const
     {
      static ScalarType dummy = 0;
      if( m_size[0] <= location[0] ) return dummy;
      if( m_size[1] <= location[1] ) return dummy;
      return m_container[location[1] * m_size[0] + location[0]];
     }
    bool set( Size2DType const& location, ScalarType const& value )
     {
      if( m_size[0] <= location[0] ) return false;
      if( m_size[1] <= location[1] ) return false;
      m_container[ location[1]* m_size[0] + location[0] ] = value;
      return true;
     }


  public:
   Size2DType m_size;
   ContainerType m_container;
 };

extern void save( std::string const& name, Layer const& filer );
