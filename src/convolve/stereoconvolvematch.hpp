#include "color/color.hpp"

#include <opencv2/opencv.hpp>

#include "./square.hpp"
#include "./filter.hpp"
#include "./layer.hpp"
#include "./lasagna.hpp"


class StereoConvolveMatch
 {
  public:
    typedef cv::Mat ImageType;
    typedef std::size_t  SizeType;
    typedef double  ScalarType;
    typedef color::rgb<double> ColorType;
    typedef std::array<std::size_t, 2>  Size2DType;
    typedef std::array<ScalarType, 2>  Scalar2DType;
    typedef std::array<int,2>  Integer2DType;

    StereoConvolveMatch();

    void initialize( ImageType const& left, ImageType const& right );
    void process( ImageType& disparity, ImageType const& left, ImageType const& right )const;

    void process_P( SizeType const& line, ImageType const& left, ImageType const& right )const;
    //void processL( ImageType& disparity, SizeType const& line )const;
    //void processR( ImageType& disparity, SizeType const& line )const;
    void processB( ImageType& disparity, SizeType const& line )const;

    ScalarType distance( ColorType const& left, ColorType const& right )const;
    ScalarType distance( Size2DType const &L, Size2DType const &R )const;

    ColorType get( Size2DType const location, ImageType const image )const;


    typedef Layer LayerType;
    typedef Filter FilterType;
    typedef Filter MaskType;
    typedef Lasagna LasagnaType;

    void lazagna( SizeType const& width, SizeType const& height, SizeType const& depth );

    static ScalarType convolve( ImageType const& image, Integer2DType const& location, FilterType const& filter, MaskType const& mask );
    static ScalarType convolve( ImageType const& image, Integer2DType const& location, FilterType const& filter );

    static void getMask( MaskType &mask, ImageType const& image, Integer2DType const& location );
    static void convolve( LayerType& layer, ImageType const& image, FilterType const& filter );
    static void convolveM( LayerType& layer, ImageType const& image, FilterType const& filter );

    mutable Stereo::Square m_square;
    mutable LasagnaType m_lasagnaL;
    mutable LasagnaType m_lasagnaR;
    std::vector<Filter> m_bank;

    std::vector<int> m_restriction;

};