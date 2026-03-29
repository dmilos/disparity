#include "color/color.hpp"

#include <opencv2/opencv.hpp>

#include "./square.hpp"


class StereoPatchNormGrayMatch
 {
  public:
    typedef cv::Mat ImageType;
    typedef std::size_t  SizeType;
    typedef double  ScalarType;
    typedef color::rgb<double> ColorType;
    typedef std::array<std::size_t,2>  Size2DType;

    StereoPatchNormGrayMatch();

    void process( ImageType & disparity, ImageType const& left, ImageType const& right )const;

    void process_P( SizeType const& line, ImageType const& left, ImageType const& right )const;
    void processL( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const;
    void processR( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const;
    void processB( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const;

    ScalarType distance( ColorType const& left, ColorType const& right )const;
    ScalarType distance( Size2DType const &L, Size2DType const &R, ImageType const& left, ImageType const& right )const;

    ColorType get( Size2DType const location, ImageType const image )const;

    mutable Stereo::Square m_square;


    int m_side;
    ScalarType m_factor; //!< for gray
    ScalarType m_power;

    mutable cv::Mat m_disparityL;
    mutable cv::Mat m_disparityR;

    double m_trash;
    double m_boundLo;
    double m_boundHi;

 
};