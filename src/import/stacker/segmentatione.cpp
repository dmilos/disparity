#include "opencv2/opencv.hpp"

#include "./segmentatione.hpp"

#include <iostream>
#include <iomanip>

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::S_Stacker::SegmentationE::SegmentationE( SizeType const& precision, SizeType const& bins )
 {
  m_debug = false;

  m_precision = precision;
  m_bins = bins;
 }


bool S_match::S_feature::S_disparity::S_Stacker::SegmentationE::process( LasagnaType &lasagna, SizeType const& laeyer_index )const
 {
  {
   auto & layer = lasagna.layer()[ laeyer_index ];

   std::vector<std::size_t> histogram;  histogram.resize( m_precision, 0 );
   graphics::image::analyze::histogram( histogram, layer );

   auto total = graphics::image::analyze::histogram_total( histogram )+1;
   graphics::image::analyze::histogram_cumulative( histogram );

   SizeType size = m_bins;
   std::vector<double> table_value; table_value.resize( histogram.size() );
   for( SizeType index=0; index < histogram.size(); ++index )
    {
     table_value[ index ] = ((int)math::function::any_to_any<double>( (double)histogram[index], 0, (double)total, 0, (double)size ))/(double)(size-1);
    }

   graphics::image::correct::lut1d( layer, table_value );

   //graphics::image::save( "layer-SegmentationE" + std::to_string( rand() ) + ".png", layer );
  }
  
  return true;
 }

bool S_match::S_feature::S_disparity::S_Stacker::SegmentationE::process( DisparityType &disparity, SizeType const& left_index, SizeType const& right_index )const
 {
  SizeType offset = disparity.m_left.layer().size();

  std::vector<std::size_t> histogram;  histogram.resize( m_precision, 0 );
  graphics::image::analyze::histogram( histogram, disparity.m_left.layer()[left_index] );
  graphics::image::analyze::histogram( histogram, disparity.m_right.layer()[ right_index ] );

  auto total = graphics::image::analyze::histogram_total( histogram )+1;
  graphics::image::analyze::histogram_cumulative( histogram );

  std::vector<double> table_value; table_value.resize( histogram.size() );
  for( SizeType index=0; index < histogram.size(); ++index )
   {
    auto bin = m_bins * (double)histogram[index]/(double)total;
    table_value[ index ] = (int)(bin)/(double)(m_bins-1);
   }

  graphics::image::correct::lut1d( disparity.m_left.layer()[left_index], table_value );
  graphics::image::correct::lut1d( disparity.m_right.layer()[right_index], table_value );

  auto R = rand();
  //graphics::image::save( "layer-se-" + std::to_string( R ) + "-left.png",  disparity.m_left.layer()[ left_index] );
  //graphics::image::save( "layer-se-" + std::to_string( R ) + "-right.png", disparity.m_right.layer()[right_index] );

  return true;
 }
