#include "opencv2/opencv.hpp"

#include "./segmentationl.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::S_Stacker::SegmentationL::SegmentationL( SizeType const& precision, SizeType const& interval )
 {
  m_debug = false;

  m_precision = precision;
  m_interval = interval;
 }


bool S_match::S_feature::S_disparity::S_Stacker::SegmentationL::process( LasagnaType &lasagna, SizeType const& laeyer_index )const
 {
  {
   auto & layer = lasagna.layer()[ laeyer_index ];

   std::vector<std::size_t> histogram;  histogram.resize( m_precision, 0 );
   graphics::image::analyze::histogram( histogram, layer );
   std::vector<std::size_t> table_index;
   graphics::image::analyze::mean_shift<std::size_t>( table_index, histogram, m_interval, 10 );
   std::vector<double> table_value; table_value.resize( table_index.size() );
   for( int index=0; index< table_index.size(); ++index ) table_value[index] = table_index[index]/ (double)table_index.size();
   graphics::image::correct::lut1d( layer, table_value );

   //graphics::image::save( "layer-SegmentationL" + std::to_string( rand() ) + ".png", layer ); 
  }

  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::SegmentationL::process( DisparityType &disparity, SizeType const& left_index, SizeType const& right_index )const
 {
  SizeType offset = disparity.m_left.layer().size();

    std::vector<std::size_t> histogram;  histogram.resize( m_precision, 0 );
    graphics::image::analyze::histogram( histogram, disparity.m_left.layer()[left_index] );
    graphics::image::analyze::histogram( histogram, disparity.m_right.layer()[ right_index ] );

    std::vector<std::size_t> table_index;
    graphics::image::analyze::mean_shift<std::size_t>( table_index, histogram, m_interval, 10 );
    std::vector<double> table_value; table_value.resize( table_index.size() );
    for( int index=0; index< table_index.size(); ++index ) table_value[index] = table_index[index]/ (double)table_index.size();

    graphics::image::correct::lut1d( disparity.m_left.layer()[left_index], table_value );
    graphics::image::correct::lut1d( disparity.m_right.layer()[right_index], table_value );

   auto R = rand();
   //graphics::image::save( "layer-s-" + std::to_string( R ) + "-left.png",  disparity.m_left.layer()[ left_index] ); 
   //graphics::image::save( "layer-s-" + std::to_string( R ) + "-right.png", disparity.m_right.layer()[right_index] ); 

  return true;
 }
