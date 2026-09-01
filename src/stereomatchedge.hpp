#include "color/color.hpp"

#include <opencv2/opencv.hpp>

#include "./square.hpp"
#include "./convolve/lasagna.hpp"


class StereoEdgeMatch
 {
  public:
    typedef cv::Mat ImageType;
    typedef std::size_t  SizeType;
    typedef double  ScalarType;
    typedef color::rgb<double> ColorType;
    typedef std::array<std::size_t,2>  Size2DType;

    typedef Lasagna LasagnaType;


    StereoEdgeMatch();

    void process( ImageType & disparity, ImageType const& left, ImageType const& right )const;

    void process_P( SizeType const& line, ImageType const& left, ImageType const& right )const;
    //void processL( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const;
    //void processR( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const;
    void processB( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const;

    ScalarType distance( ColorType const& left, ColorType const& right )const;

    ColorType get( Size2DType const location, ImageType const image )const;

    typedef Layer LayerType;
    void lazagna( SizeType const& width, SizeType const& height, SizeType const& depth );
    mutable Stereo::Square m_square;
    mutable LasagnaType m_lasagnaL;
    mutable LasagnaType m_lasagnaR;

    int m_side;
    ScalarType m_factor; //!< for gray
    ScalarType m_power;

    ImageType m_imageL;
    ImageType m_imageR;

    mutable cv::Mat m_disparityL;
    mutable cv::Mat m_disparityR;

    double m_trash;
    double m_boundLo;
    double m_boundHi;

};