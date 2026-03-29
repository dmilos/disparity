#include "opencv2/opencv.hpp"
#include "color/color.hpp"

class Bilateral
 {
  public:
    typedef cv::Mat ImageType;
    typedef std::array<int,2> Integer2DType;
    typedef color::rgb<double> ColorType;
    typedef double ScalarType;
    typedef std::size_t SizeType;


    Bilateral( SizeType const& iteration, SizeType  const& range, ScalarType  const& proximity = 0.1 );

  public:
    ScalarType distance( ColorType const& left, ColorType const& right )const;
    ColorType get( ImageType const& image, Integer2DType const& location  )const;
    bool set( ImageType & image, Integer2DType const& location, ColorType const& value )const;
    ColorType process( ImageType const& image, Integer2DType const& location )const;
    void process( ImageType & target, ImageType const& source )const;

    SizeType m_iterations;
    SizeType m_range;
    ScalarType m_proximity;
 };