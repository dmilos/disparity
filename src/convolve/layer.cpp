#include "./layer.hpp"

#include "opencv2/opencv.hpp"

void save( std::string const& name, Layer const& layer )
 {
  cv::Mat mat( (int)layer.size()[1], (int)layer.size()[0], CV_64FC1, const_cast<double*>(layer.data()) );
  cv::Mat  cvMat = mat.clone();

  double minimum = layer.get( { 0,0 } );
  double maximum = layer.get( { 0,0 } );
  for( int y = 0; y < layer.size()[1]; ++y )
   for( int x = 0; x < layer.size()[0]; ++x )
    {
     minimum = std::min( minimum, layer.get( { (std::size_t)x,(std::size_t)y } ) );
     maximum = std::max( maximum, layer.get( { (std::size_t)x,(std::size_t)y } ) );
    }

  cv::imwrite( name, 256 * (cvMat - minimum) / (maximum - minimum) );
 }
