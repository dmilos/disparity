#pragma once

#include "color/color.hpp"

#include <opencv2/opencv.hpp>

namespace Stereo
{
class Square
 {
  public:
    typedef cv::Mat ImageType;
    typedef std::size_t  SizeType;
    typedef double  ScalarType;
    typedef int  IntegerType;
    typedef color::rgb<double> ColorType;
    typedef std::array<std::size_t,2>  Size2DType;
    typedef std::vector<ScalarType>  DistanceContainerType;
    typedef std::vector<IntegerType>     CorespodenceContainerType;

    typedef cv::Mat ImageType;


    Square();

    void init( SizeType const& width, SizeType const& height );

    void processL(  );
    void processR(  );

    bool tieL( IntegerType const& pivot );
    bool tieR( IntegerType const& pivot );
    IntegerType beginL( IntegerType const& L );
    IntegerType beginR( IntegerType const& pivot );
    IntegerType endL( IntegerType const& begin );
    IntegerType endR( IntegerType const& begin );

    bool importL( ImageType const& imageL, SizeType const& line );
    bool importR( ImageType const& imageR, SizeType const& line );

    void disparityL();
    void disparityR();
    void disparityB();
    SizeType  purge();
    void clearL();
    void clearR();
    IntegerType none();

    SizeType m_width;
    SizeType m_height;
    ScalarType m_infinity;
    ScalarType m_proximity;
    ScalarType m_trashold;
    SizeType   m_range;

    DistanceContainerType m_distance;
    std::vector< IntegerType > m_bestL;
    std::vector< IntegerType > m_bestR;

    std::vector< IntegerType > m_disparityL;
    std::vector< IntegerType > m_disparityR;
    std::vector< IntegerType > m_disparityB;
};

}