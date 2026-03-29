#include "color/color.hpp"

#include <opencv2/opencv.hpp>

#include "./square.hpp"


class StereoNormalMatch
 {
  public:
    typedef cv::Mat ImageType;
    typedef std::size_t  SizeType;
    typedef double  ScalarType;
    typedef color::rgb<double> ColorType;
    typedef std::array<std::size_t,2>  Size2DType;
    typedef std::array<double,3>  Vector3DType;

    StereoNormalMatch();

    void process( ImageType & disparity, ImageType const& left, ImageType const& right )const;

    void process_P( SizeType const& line, ImageType const& left, ImageType const& right )const;
    void processL( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const;
    void processR( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const;
    void processB( ImageType& disparity, SizeType const& line, ImageType const& left, ImageType const& right )const;

    ScalarType distance( Vector3DType const& left, Vector3DType const& right )const;
    ScalarType distance( Size2DType const &L, Size2DType const &R, ImageType const& left, ImageType const& right )const;

    ColorType get( Size2DType const location, ImageType const image )const;

    mutable Stereo::Square m_square;


    ScalarType m_factor;
    ScalarType m_power;

    mutable cv::Mat m_disparityL;
    mutable cv::Mat m_disparityR;

    mutable double m_trash;
    double m_boundLo;
    double m_boundHi; 
    mutable std::vector< ::math::linear::vector::point<double, 3> > m_leftCloud; 
    mutable std::vector< ::math::linear::vector::point<double, 3> > m_rightCloud;
    void side( int s );
  private:
    int m_side;
 };