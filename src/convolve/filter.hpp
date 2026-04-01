#pragma once

#include <array>
#include <vector>
#include <opencv2/opencv.hpp>


class Filter
 {
  public:
    typedef std::size_t SizeType;
    typedef double ScalarType;
    typedef std::array<SizeType,2>  Size2DType;

    typedef std::vector<ScalarType> ContainerType;
    Filter()
     {
      size( { 1, 1 } );
     }

    ScalarType      * data()      { return m_container.data(); }
    ScalarType const* data()const { return m_container.data(); }
    ContainerType const& container()const{ return m_container; }

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

  private:
    Size2DType m_size;
    ContainerType m_container;
 };

extern void save( std::string const& name, Filter const& filer );
extern void normalize( Filter& filer );
extern void from_image( Filter& filter, cv::Mat const& gray, std::array<int, 2> const& location );

extern void gauss( Filter & filter );
extern void gabor( Filter & filter, double const angle, double const& frequency, double const& shift, std::array<double, 2> const& press={1,2} );
extern void laplace( Filter & filter, double const& frequency, double const& shift );