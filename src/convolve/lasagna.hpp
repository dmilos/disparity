
#include "./layer.hpp"

class Lasagna
 {
  public:
    typedef std::size_t SizeType;
    typedef double ScalarType;
    typedef std::array<SizeType, 2>  Size2DType;
    typedef std::array<SizeType,3> Size3DType;

    typedef Layer LayerType;
    typedef std::vector<Layer> ContainerType;

  public:
    void size( SizeType const& width, SizeType const& height, SizeType const& depth )
     {
      m_container.resize( depth );
      for( auto& layer : m_container )
      {
        layer.size( { width, height } );
      }
     }

  public:
    SizeType depth() const{ return m_container.size(); }
    Size2DType const& resolution() const;
  public:
   //bool       get( FeatureType &feature, Size2DType const& coord )const;
    ScalarType get( Size3DType const& coord )const;
   //bool       get( LineType &line, SizeType const& y )const;
  public:
    bool       set( Size3DType const& coord, ScalarType const& v );
    bool       set( Size2DType const& coord, SizeType const& level, ScalarType const& v );
    bool       set( SizeType const& x, SizeType const& y, SizeType const& level, ScalarType const& v );

  public:
    ContainerType m_container;
 };