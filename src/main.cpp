#include <iostream>
#include <fstream>
#include <cstddef>
#include <iomanip>
#include <vector>
#include <array>
#include <numeric>
#include <filesystem>
#include <math/math.hpp>
#include <color/color.hpp>
#include <opencv2/opencv.hpp>

#include "./compare.hpp"
#include "./stereomatch.hpp"
#include "./stereomatchV1.hpp"
#include "./stereomatchV2.hpp"
#include "./stereopatchmatch.hpp"
#include "./stereopatchnormgraymatch.hpp"
#include "./stereonormalmatch.hpp"
#include "./convolve/stereoconvolvematch.hpp"
#include "./filter/bilateral.hpp"


typedef ::color::rgb<std::uint8_t> ColorType;
typedef ::math::linear::vector::structure<double, 2> Point2dType;
typedef ::math::linear::vector::structure<double, 3> Point3dType;
typedef ::math::linear::homography::structure<double, 2> Homography3dType;
typedef ::math::geometry::projective::camera::projection<double>   projection_t;
typedef ::math::geometry::projective::camera::decompose<double> decompose_t;
typedef ::math::geometry::projective::camera::mobile< double >camera_type;

 std::string windowName = "Camera Feed";
 int slider_X, slider_Y, slider_Z;

 static void sliderOn( int, void* ) {}


void init()
 {
  cv::namedWindow( windowName, cv::WINDOW_AUTOSIZE ); // Create Window   WINDOW_FREERATIO

  //cv::createTrackbar( "Tx", windowName, &slider_X, 100, sliderOn );
   cv::createTrackbar( "Ty", windowName, &slider_Y, 100, sliderOn );
  //cv::createTrackbar( "Tz", windowName, &slider_Z, 100, sliderOn );
}

std::string format( int const& value, int w )
 {
  std::stringstream ss;
  ss << std::setw( w ) << std::setfill('0') << value;
  return ss.str();
 }

double g_valueS = 0;
double g_value0 = 0;
double g_value1 = 0;
double g_value2 = 0;
std::string g_prefix;

void best( cv::Mat & disparity, cv::Mat const& left, cv::Mat const& right )
 {
  disparity = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

  StereoPatchMatch spm;

  //spm.m_trash = 1;
  //spm.m_side = (int)g_value0;
  //spm.m_square.m_trashold = 0.03;
  //spm.m_square.m_proximity = 0.0009;
  //spm.m_square.m_trashold = 1;
  //spm.m_square.m_proximity = 0;
  //spm.process( disparity, left, right );

  StereoMatch sam;
  //sam.m_side = (int)g_valueS;
  //sam.m_side = (int)g_value0;
  //sam.m_gammaC = g_value1;
  //sam.m_gammaS = g_value2;
  //sam.m_boundLo = g_value1;
  //sam.m_boundHi = g_value2;
  //sam.m_formula = g_value0;
  //sam.m_boundLo = g_value1;
  sam.m_boundHi = g_value1;

  StereoConvolveMatch scm;

  scm.process( disparity, left, right );
 }

struct Case
 {
  std::string m_leftName;
  std::string m_rightName;
  std::string m_disprityName;

  cv::Mat m_left;
  cv::Mat m_right;
  cv::Mat m_disprity;
  double m_scale;
};

bool load_case
 (
   Case & theCase 
  ,std::string const& root
  ,std::string const& left, std::string const& right, std::string const& disparity
  ,double const& scale
  )
 {
  theCase.m_leftName     = left ;
  theCase.m_rightName    = right ;
  theCase.m_disprityName = disparity ;

  theCase.m_left     = cv::imread( root + "/"+ left );
  theCase.m_right    = cv::imread( root + "/" + right );
  theCase.m_disprity = cv::imread( root + "/" + disparity, cv::ImreadModes::IMREAD_GRAYSCALE );
  theCase.m_scale = scale;
  return true;
}

std::map<std::string, Case> g_collection;

void load_files( )
 {
  std::string dataRoot = "c:/work/code/cpp/prj/disparity/data";

  load_case( g_collection["Cloth1"], dataRoot + "/Cloth1", "view1.png", "view5.png", "disp1.png", 3 );
  return;
  load_case( g_collection["poster1"], dataRoot + "/poster1", "im2.png",    "im8.png", "disp2.png", 3 );
  load_case( g_collection["circle"], dataRoot  + "/circle",   "untitled-L.png", "untitled-R.png", "disparity.png", 1 );
  load_case( g_collection["cubes1"], dataRoot  + "/cubes1",  "cube-L.png", "cube-R.png", "disparity.png", 1 );

  load_case( g_collection["cones"], dataRoot  + "/cones",  "im2.png", "im6.png", "disp2.png", 1 );
  load_case( g_collection["Monopoly"], dataRoot  + "/Monopoly",  "view1.png", "view5.png", "disp1.png", 1 );

  load_case( g_collection["Art"], dataRoot  + "/Art",  "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Baby1"], dataRoot + "/Baby1", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Baby2"], dataRoot + "/Baby2", "view1.png", "view5.png", "disp1.png", 1 );

  load_case( g_collection["Bowling1"], dataRoot + "/Bowling1", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Moebius"], dataRoot + "/Moebius", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Lampshade2"], dataRoot + "/Lampshade2", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Plastic"], dataRoot + "/Plastic", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Reindeer"], dataRoot + "/Reindeer", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Rocks1"], dataRoot + "/Rocks1", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Wood1"], dataRoot + "/Wood1", "view1.png", "view5.png", "disp1.png", 1 );
  //load_case( g_collection["Computer"], dataRoot + "/Computer", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Dolls"], dataRoot + "/Dolls", "view1.png", "view5.png", "disp1.png", 1 );
  //load_case( g_collection["Drumsticks"], dataRoot + "/Drumsticks", "view1.png", "view5.png", "disp1.png", 1 );
  //load_case( g_collection["Dwarves"], dataRoot + "/Dwarves", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Flowerpots"], dataRoot + "/Flowerpots", "view1.png", "view5.png", "disp1.png", 1 );
  //load_case( g_collection["aujfa-eq"], dataRoot + "/aujfa", "im-eq-L.png", "im-eq-R.png", "disp1.png", 1 );
  //load_case( g_collection["aujfa"], dataRoot + "/aujfa", "imL.png", "imR.png", "disp1.png", 1 );
  load_case( g_collection["sawtooth"], dataRoot + "/sawtooth", "im0.png", "im8.png", "disp2.png", 1 );
  load_case( g_collection["teddy"], dataRoot + "/teddy", "im2.png", "im6.png", "disp2.png", 1 );
  load_case( g_collection["venus"], dataRoot + "/venus", "im0.png", "im8.png", "disp2.png", 1 );
  load_case( g_collection["Laundry"], dataRoot + "/Laundry", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Aloe"], dataRoot + "/Aloe", "view0.png", "view6.png", "disp1.png", 1 );
  load_case( g_collection["Baby3"], dataRoot + "/Baby3", "view0.png", "view1.png", "disp1.png", 1 );
 
  load_case( g_collection["tsukuba"],     dataRoot + "/tsukuba", "scene1.row3.col1.png", "scene1.row3.col5.png", "truedisp.row3.col3.png", 1 );
  load_case( g_collection["tsukuba-016"], dataRoot + "/tsukuba", "1/combine_1-5_016_L.png", "1/combine_1-5_016_R.png", "truedisp.row3.col3.png", 1 );
  load_case( g_collection["tsukuba-256"], dataRoot + "/tsukuba", "1/combine_1-5_256_L.png", "1/combine_1-5_256_R.png", "truedisp.row3.col3.png", 1 );
  load_case( g_collection["tsukuba-200"], dataRoot + "/tsukuba", "1/scene1.row3.col1-200.png", "1/scene1.row3.col5-200.png", "truedisp.row3.col3.png", 1 );
 }

int main_single( int argc, char *argv[] )
 {
  load_files( );

  StereoMatch sam;
  StereoMatchV1 samV1;
  StereoMatchV1 samV2;
  StereoPatchMatch spm;
  StereoNormalMatch snm;
  StereoPatchNormGrayMatch spngm;
  StereoConvolveMatch convolve;

  auto & matcher = convolve;

  for( auto const& item: g_collection )
   {
    std::cout << item.first << std::endl;
    cv::Mat left  = item.second.m_left;
    cv::Mat right = item.second.m_right;

    cv::Mat disparity = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

    convolve.initialize( left, right );
    matcher.process( disparity, left, right );

    std::string prefix  = item.first +  "_";
    std::string postfix = "_max";
    std::string number = std::to_string( 0 );
    cv::imwrite( "disparity_" + prefix + number + postfix + ".png", 2.5*disparity );
   }

  return EXIT_SUCCESS;
 }

int main_convolve_combination( int argc, char* argv[] )
 {
  load_files();

  cv::Mat left;
  cv::Mat right;
 
  StereoConvolveMatch convolve;

  cv::Mat ground_dummy = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );
  auto & matcher = convolve;
   for( auto const& item: g_collection )
    {
     std::cout << item.first << std::endl;
     cv::Mat left  = item.second.m_left;
     cv::Mat right = item.second.m_right;

     std::string prefix  = item.first +  "_";
     std::string postfix = "_max";
     std::string number  = std::to_string( 0 );
     cv::Mat disparity;
     disparity = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

     convolve.initialize( left, right );
 
     int max_q = 0;
     int counter = 0;
     convolve.m_restriction.push_back( 2 );
     convolve.m_restriction.push_back( 1 );
     convolve.m_restriction.push_back( 0 );

     do{
        disparity.setTo( cv::Scalar(0) );

      //for( auto & index : convolve.m_restriction  )
      // {
      //  index  = rand() % convolve.m_bank.size();
      // }

      convolve.process( disparity, left, right );
      auto quaity = compare( item.second.m_scale * disparity, item.second.m_disprity, 3 );

      number = format( (int)quaity, 5 );
      if( max_q  < quaity  )
       {
        std::cout << "Quality: " << quaity << "-> ";
        for( auto index : convolve.m_restriction  )
         {
          std::cout << index << "_";
         }

        max_q = (int)quaity;
        std::cout << "***" ;
        cv::imwrite( "disparity_" + prefix + number + postfix + ".png", 4*disparity );
        std::cout << std::endl;
       }
      if( 0 == (++counter%100) )
       {
        std::cout << std::setw(10) << quaity << "-> ";
        for( auto index : convolve.m_restriction )
         {
          std::cout << "( " << index << "); _ ";
         }
        std::cout<< std::endl;
      }

     }while( ::math::algorithm::next_combination<int>
       ( convolve.m_restriction.begin(), convolve.m_restriction.end(), (int)convolve.m_bank.size() )
      );
    }

  return EXIT_SUCCESS;
 }

int main_convolve_increment( int argc, char* argv[] )
 {
  load_files();

  cv::Mat left;
  cv::Mat right;

  StereoConvolveMatch convolve;

  auto& matcher = convolve;
  for( auto const& item : g_collection )
   {
    std::cout << item.first << std::endl;
    cv::Mat left  = item.second.m_left;
    cv::Mat right = item.second.m_right;

    std::string prefix = item.first + "_";
    std::string postfix = "_max";
    std::string number = std::to_string( 0 );
    cv::Mat disparity;
    disparity = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

    convolve.initialize( left, right );
    convolve.m_restriction.clear();
 
    //extern int findIndex( std::string const& signature );
    //convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,1} );" ) );
    //convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)26, (SizeType)26 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
    //convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} );" ) );
    //convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );" ) );
    //convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
    //convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
    //convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} );" ) );
    //convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,1} );" ) );
    //convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {1,1} );"  ) );

    convolve.process( disparity, left, right );
    cv::imwrite( "disparity_" + prefix + number + postfix + ".png", item.second.m_scale * disparity );

   // continue;
 
    int counter = 0;
 
    int best_quaity   = 0;
    int max_quaity = 0;
    int cycle_counter = 0;
    cv::Mat hit_mask = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );
    int tolerance_compare = 3;
    while( ( convolve.m_restriction.size() < 120 ) )
     {
      ++cycle_counter;
 
    //max_quaity = 0;
    bool winner_have = false;
    int winner_position = 0;
    int winner_index = convolve.m_restriction[winner_position];

    for( int position = 0; position < convolve.m_restriction.size(); ++position )
     {
      int local_index = convolve.m_restriction[position];

      for( int index = -1; index < (int)convolve.m_lasagnaL.depth(); ++index )
       {
        convolve.m_restriction[position] = index;
        disparity.setTo( cv::Scalar( 0 ) ); //= cv::Mat::disparity::zeros( left.rows, left.cols, CV_8UC1 );

        convolve.process( disparity, left, right );

        auto quaity = compare( item.second.m_scale * disparity, item.second.m_disprity, tolerance_compare );

        if( max_quaity < quaity )
         {
          winner_have = true;
          max_quaity = (int)quaity;
          winner_position = position;
          winner_index = index;
          best_quaity = std::max( max_quaity, best_quaity );
          
          number = format( (int)quaity, 6 ) + "_";
          postfix = format( (int)cycle_counter, 6 );

          std::ofstream ofs( "disparity_" + prefix + number + postfix + ".txt", std::ios_base::app );
          ofs << "--- --- --- " << std::endl;
          std::cout << "Quality: " << quaity <<"; C:"<< cycle_counter << "; P:"  << position << "-> ";
          std::cout <<"[" << std::setw( 3 ) << convolve.m_restriction.size() << "]";
          for( auto index : convolve.m_restriction )
           {
            extern std::vector<std::string> g_table;
            std::cout << "(" << index << ");_";
            if( ( 0 < index) && ( index < g_table.size() ) ) ofs << g_table[ index] << std::endl;
           }

          max_quaity = (int)quaity;
          std::cout << "***";
          cv::imwrite( "disparity_" + prefix + number + postfix + ".png", item.second.m_scale * disparity );

          //for( double disparity_scale = 1; disparity_scale < 5.0; disparity_scale += 0.01 )
          // {
          //  postfix = std::to_string( disparity_scale  );
          mask( hit_mask, item.second.m_scale * disparity, item.second.m_disprity, tolerance_compare );
           //std::cout << std::setw(6)<< disparity_scale << "; " << std::setw( 6 ) << quaity <<  std::endl;
          cv::imwrite( "disparity_" + prefix + number + postfix +"_mask" + ".png", hit_mask );
          // }exit( 0 );
          std::cout << std::endl;
        }
        if( 0 == (++counter % 1000) )
        {
          std::cout << std::setw( 10 ) << quaity << "-> ";
          for( auto index : convolve.m_restriction )
          {
            std::cout << index << "; ";
          }
          std::cout << std::endl;
        }
       }
      convolve.m_restriction[position] = local_index;
      std::cout << ".";
     }
    convolve.m_restriction[winner_position] = winner_index;
    if( -1 == winner_index )
     {
      convolve.m_restriction.erase( convolve.m_restriction.begin() + winner_position );
      //convolve.m_square.m_trashold = 0.1 * convolve.m_restriction.size();
      std::cout << "x";
     }
    if( false == winner_have )
     {
      convolve.m_restriction.insert( convolve.m_restriction.begin(), -1 );
    //convolve.m_square.m_trashold = 0.1 * convolve.m_restriction.size();
      std::cout << "+";
     }

    std::sort( convolve.m_restriction.rbegin(), convolve.m_restriction.rend() );
    std::cout << "o";
   }
  }

  return EXIT_SUCCESS;
}


int main_rest( int argc, char *argv[] )
 {
  //init();

  cv::Mat left;
  cv::Mat right;

  StereoMatch sam;

  StereoPatchMatch spm;
  StereoNormalMatch snm;
  StereoPatchNormGrayMatch spngm;
  StereoConvolveMatch convolve;

  //spm.m_trash = 0.1;
  //spm.m_side = 6;
  //spm.m_square.m_trashold = 0.09;

  auto & matcher = convolve;
   //for( sm.m_factor = 6; sm.m_factor < 15; sm.m_factor += 0.2 )
   //for( sm.m_side = 6; sm.m_side < 15; sm.m_side += 1 )
   //for( sm.m_trash = 0; sm.m_trash < 0.2; sm.m_trash += 0.01 )
   //for( sm.m_boundHi = 0.9; sm.m_boundHi < 1; sm.m_boundHi += 0.01 )
   //for( sm.m_square.m_trashold = 0.1; sm.m_square.m_trashold < 0.2; sm.m_square.m_trashold += 0.01 )
    for( auto const& item: g_collection )
    {
     std::cout << item.first << std::endl;
     cv::Mat left =   item.second.m_left ;
     cv::Mat right =   item.second.m_right;

     std::string prefix  = item.first +  "_";
     std::string postfix = "_max";
     std::string number = std::to_string( 0 );
     cv::Mat disparity;
     disparity = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

     convolve.initialize( left, right );
/**/
     int max_q = 0;
     int counter = 0;
     //convolve.m_restriction.push_back( 5 );
     //convolve.m_restriction.push_back( 4 );
     //convolve.m_restriction.push_back( 3 );
     //convolve.m_restriction.push_back( 2 );
     convolve.m_restriction.push_back( 1 );
     convolve.m_restriction.push_back( 0 );
     do{

      //for( auto & index : convolve.m_restriction  )
      // {
      //  index  = rand() % convolve.m_bank.size();
      // }

      convolve.process( disparity, left, right );
      auto quaity = compare( item.second.m_scale *  disparity, item.second.m_disprity, 3 );

      number = std::to_string( quaity );
      if( max_q  < quaity  )
       {
        std::cout << "Quality: " << quaity << "; ";
        for( auto index : convolve.m_restriction  )
         {
          std::cout << index << "; ";
         }

        max_q = (int)quaity;
        std::cout << "***" ;
        cv::imwrite( "disparity_" + prefix + number + postfix + ".png", disparity );
        std::cout << std::endl;
       }
        if( 0 == (++counter%1000) )
         {
          std::cout << std::setw(10) << quaity << ". ";
          for( auto index : convolve.m_restriction )
           {
            std::cout << index << "; ";
           }
          std::cout<< std::endl;
        }

     }  while( ::math::algorithm::next_combination<int>
       ( convolve.m_restriction.begin(), convolve.m_restriction.end(), (int)convolve.m_bank.size() )
      );

     //postfix = std::to_string( matcher.m_side )+"_" + std::to_string( matcher.m_square.m_proximity );


/*
       cv::Mat left_original = left.clone();
       cv::Mat right_original = right.clone();
        int iteration = 2;
        int size = 3;
        g_valueS = 5;
        g_value0 = 0;         //!< trunc
        g_value1 = 1.0;  //!< color
        g_value2 = 10.0;      //!<  spatial

       // // for( g_valueS = 0; g_valueS < 10; g_valueS += 1 )
         //for( g_value0 = 0; g_value0 < 7.9; g_value0 += 1 )
        //for( g_value1 = 0.92; g_value1 < 1.001; g_value1 += 0.01 )
        //for( g_value2 = 0.0; g_value2 < 1; g_value2 += 0.1 )
         //for( int iteration = 0; iteration < 10; ++ iteration )
           //for( int size = 2; size < 3; ++size )
         {
          //auto quaity = compare( 3 * disparity, ground_tsukuba, 10 );
          number =  std::string("")
               //  + std::to_string( g_valueS ) + "_"
               //+ std::to_string( g_value0 ) + "_"
               //+ std::to_string( g_value1 ) + "_"
               //+ std::to_string( g_value2 ) + "_"
               //+ std::to_string( quaity ) +  "_"
               //+ std::to_string( iteration ) +  "_"
               //+ std::to_string( size ) +  "_"
               + "_200"
          ;
          g_prefix = number;
          //Bilateral( iteration, size ).process( left, left_original );           cv::imwrite( "left__" + prefix + number + postfix + ".png",  left);
          //Bilateral( iteration, size ).process( right, right_original.clone() ); cv::imwrite( "right_" + prefix + number + postfix + ".png", right );
          disparity = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );
          best( disparity, left, right );
      cv::imwrite( "disparity_" + prefix + number + postfix + ".png", disparity * 3 );
      //std::cout << quaity << std::endl;

     }  */
   }

  return EXIT_SUCCESS;
 }


int main( int argc, char* argv[] )
 {
  //main_single( argc, argv );
  //main_convolve_combination(  argc,  argv );
  main_convolve_increment(  argc,  argv );
  //main_rest( argc, argv );
 }
