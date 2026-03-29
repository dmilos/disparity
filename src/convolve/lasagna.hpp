
#include "./layer.hpp"

class Lasagna
 {
  public:
    typedef std::size_t SizeType;
    typedef double ScalarType;
    typedef std::array<SizeType, 2>  Size2DType;

    typedef Layer LayerType;
    typedef std::vector<Layer> ContainerType;

    void size( SizeType const& width, SizeType const& height, SizeType const& depth )
    {
      m_container.resize( depth );
      for( auto& layer : m_container )
      {
        layer.size( { width, height } );
      }
    }

    SizeType depth() const{ return m_container.size(); }


    ContainerType m_container;
 };