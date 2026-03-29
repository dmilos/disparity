#include "opencv2/opencv.hpp"

extern std::size_t compare( cv::Mat const& left, cv::Mat const& right, int tolerance  );
extern std::size_t mask( cv::Mat & mask,  cv::Mat const& left, cv::Mat const& right, int tolerance);
