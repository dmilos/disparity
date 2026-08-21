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
typedef ::math::geometry::interval::structure<int, 2> RectangleType;





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

void crop( Case & target, Case const& source, RectangleType const& rect )
 {
  target.m_leftName     = source.m_leftName;
  target.m_rightName    = source.m_rightName;
  target.m_disprityName = source.m_disprityName;

  auto width  = ::math::geometry::interval::size(rect)[0] + 1;
  auto height = ::math::geometry::interval::size(rect)[1] + 1;
  auto X = rect[0][0];
  auto Y = rect[0][1];

  target.m_left     = source.m_left(     cv::Rect( X, Y, width, height ) ).clone();
  target.m_right    = source.m_right(    cv::Rect( X, Y, width, height ) ).clone();
  target.m_disprity = source.m_disprity( cv::Rect( X, Y, width, height ) ).clone();
  target.m_scale    = source.m_scale;
 }

void concatenateV(Case& target, Case const& up, Case const& down )
 {
  if( up.m_scale != down.m_scale )
   {
    std::cout << "ERROR:" << "Different scale";
    return;
   }
  if( up.m_left.cols != down.m_left.cols )
   {
    std::cout << "ERROR:" << "Different width";
    return;
   }

   target.m_scale    = up.m_scale;

   auto width  = up.m_left.cols;
   auto height = up.m_left.rows + down.m_left.rows;
   auto X = 0;
   auto Y = up.m_left.cols;

   target.m_left     = cv::Mat(height, width,  CV_8UC3 );
   up.m_left.copyTo(     target.m_left( cv::Rect2d( 0,0, up.m_left.cols, up.m_left.rows ) ) );
   down.m_left.copyTo(   target.m_left( cv::Rect2d( 0, up.m_left.rows, down.m_left.cols, down.m_left.rows ) ) );

   target.m_right    = cv::Mat(  height,width, CV_8UC3 ); 
   up.m_right.copyTo(    target.m_right( cv::Rect2d( 0,0, up.m_left.cols, up.m_left.rows ) ) );
   down.m_right.copyTo(  target.m_right( cv::Rect2d( 0, up.m_right.rows, down.m_right.cols, down.m_right.rows ) ) );

   target.m_disprity = cv::Mat(  height,width, CV_8UC1 );
   up.m_disprity.copyTo(   target.m_disprity(  cv::Rect2d( 0,0, up.m_left.cols, up.m_left.rows ) ) );
   down.m_disprity.copyTo( target.m_disprity(  cv::Rect2d( 0, up.m_disprity.rows, down.m_disprity.cols, down.m_disprity.rows ) ) );
 }

void load_files( )
 {
  std::string dataRoot = "../../data";

  //Case temp0;  load_case( temp0, dataRoot + "/Wood1", "view1.png", "view5.png", "disp1.png", 3);
  //crop( g_collection["wood-crop"], temp0, { { 250, 0 }, {  250+190, 0+15 } });  //!< Referent
  //return;

  //Case temp0;  load_case( temp0, dataRoot + "/venus", "im2.png", "im6.png", "disp2.png", 8 );
  //crop( g_collection["venus-crop"], temp0, { { 0, 200 }, { 160, 200+50 } });  //!< Referent
  //return;

  //load_case(g_collection["cones"], dataRoot + "/cones", "im2.png", "im6.png", "disp2.png", 4);
  ////Case temp0; 
  ////crop(   g_collection["cones-crop"], temp0, { { 450-80, 170 }, { 450-1, 170 + 130 } } );  //!< medium
  //////crop( g_collection["cones-crop"], temp0, { { 450-80, 175 }, { 450-1, 175 +  40 } } );  //!< small
  //return;

  //load_case( g_collection["cloth"], dataRoot + "/Cloth1", "view1.png", "view5.png", "disp1.png", 3 );
  //Case temp0;   load_case( temp0, dataRoot + "/Cloth1", "view1.png", "view5.png", "disp1.png", 3);
  //crop(g_collection["cloth-crop"], temp0, { { 0 * 110, 0 }, { 1 * 110 - 35, 90 } });
  //return;

  //crop(g_collection["cloth-crop"], temp0, { { 2 * 110, 0 }, { 3 * 110 - 35, 90 } });
  //crop(g_collection["cloth-line"], temp0, { { 0, 90 }, { 415, 150  } });
  // crop(g_collection["cloth-line"], temp0, { { 0, 45 }, { 415, 45+30  } });
   //crop(g_collection["cloth-line"], temp0, { { 0, 40 }, { 320, 40+50  } });

  //crop( g_collection["cloth-crop"], temp0, { { 190, 160 }, { 190+200, 160+100 } }); 
  // crop( g_collection["cloth-crop"], temp0, { { 130, 40 }, { 340, 90 } } );
  // crop( g_collection["cloth-crop"], temp0, { { 230, 95 }, { 230+140, 95+ 65 } } );
  //crop( g_collection["cloth-crop"], temp0, { { 0, 95 }, { 415, 150 } } );
  //crop( g_collection["cloth-crop"], temp0, { { 200, 90 }, { 200+100, 90+ 80 } } );
  //crop( g_collection["cloth-crop"], temp0, { { 200, 70 }, { 200+100, 70+ 40 } } );
  //crop( g_collection["cloth-crop"], temp0, { { 200, 70 }, { 200+160, 70 + 80 } } );
  //crop( g_collection["cloth-crop"], temp0, { { 180, 40 }, { 180+140, 40 + 30 } } );

  //Case a;  crop( a, temp0, { { 0*200, 0 }, { 1*200 - 35, 100 + 200 } });
  //Case b;  crop( b, temp0, { { 1*200, 0 }, { 2*200 - 35, 100 + 200 } });
  //concatenateV( g_collection["cloth-stripe2"], a, b );

  //Case a;  crop( a, temp0, { { 0*110, 0 }, { 1*110 - 35, 100 + 200 } });
  //Case b;  crop( b, temp0, { { 1*110, 0 }, { 2*110 - 35, 100 + 200 } });
  //Case c;  crop( c, temp0, { { 2*110, 0 }, { 3*110 - 35, 100 + 200 } });
  //Case d;  crop( d, temp0, { { 3*110, 0 }, { 4*110 - 35, 100 + 200 } });
  //Case x;  concatenateV( x, a, b );
  //Case y;  concatenateV( y, c, d );
  //concatenateV( g_collection["cloth-stripe"], x, y );
  //return;

  //load_case(g_collection["Cloth1-big"], dataRoot + "/Cloth1-big", "view1.png", "view5.png", "disp1.png", 1);
  //Case temp0;   load_case(temp0, dataRoot + "/Cloth1-big", "view1.png", "view5.png", "disp1.png", 1);
  //crop( g_collection["cloth-big-crop"], temp0, { { 50, 100 }, { 380, 120 } }); 
  //crop(g_collection["cloth-big-crop"], temp0, { { 530, 130+10 }, { 530 + 360, 130+60-15 } });
  //crop(g_collection["cloth-big-crop"], temp0, { { 530, 130 +10 }, { 530 + 230, 130 + 60 -20 } });
  //return;

  //load_case( g_collection["sawtooth"], dataRoot + "/sawtooth", "im2.png", "im6.png", "disp2.png", 8.049);
  //Case temp;   load_case( temp, dataRoot + "/sawtooth", "im2.png", "im6.png", "disp2.png", 8.049);
  //crop(g_collection["sawtooth-crop"], temp, { { 0 , 350 }, { 350, 370 } });

  // ////crop( g_collection["sawtooth-crop"], temp, { { 110, 85 }, { 110 + 105, 85+ 75 } }); 
  // ////crop( g_collection["sawtooth-crop"], temp, { { 40, 0 }, { 40 + 50, 50 } }); 
  // ////crop( g_collection["sawtooth-crop"], temp, { { 170, 50 }, { 170 + 110, 80 } }); 
  // ////crop( g_collection["sawtooth-crop"], temp, { { 75, 70+20 }, { 75+200, 70 + 50} }); 
  // //crop( g_collection["sawtooth-crop"], temp, { { 390, 140 }, { 433, 280} }); 
  //crop(g_collection["sawtooth-crop"], temp, { { 0*100, 133 }, { 1*100-20, 240 } });
   //Case a;  crop( a, temp, { { 0*100, 0 }, { 1*100-20, 240 } });
   //Case b;  crop( b, temp, { { 1*100, 0 }, { 2*100-20, 240 } });
   //Case c;  crop( c, temp, { { 2*100, 0 }, { 3*100-20, 240 } });
   //Case d;  crop( d, temp, { { 3*100, 0 }, { 4*100-20, 240 } });
   //Case x;  concatenateV( x, a, b );
   //Case y;  concatenateV( y, c, d );
   //concatenateV( g_collection["sawtooth-08-crop"], x, y );
  //return;

   //load_case(g_collection["Art"], dataRoot + "/Art", "view1.png", "view5.png", "disp1.png", 3);
   //Case temp;    load_case(temp, dataRoot + "/Art", "view1.png", "view5.png", "disp1.png", 3);
   //crop(g_collection["Art-01-stripe"], temp, { { 40, 0 }, { 40 + 1*100, 300 } });
   //Case a;  crop( a, temp, { { 0*100, 0 }, { 1*100-20, 240 } });
   //Case b;  crop( b, temp, { { 1*100, 0 }, { 2*100-20, 240 } });
   //Case c;  crop( c, temp, { { 2*100, 0 }, { 3*100-20, 240 } });
   //Case d;  crop( d, temp, { { 3*100, 0 }, { 4*100-20, 240 } });
   //Case x;  concatenateV( x, a, b );
   //Case y;  concatenateV( y, c, d );
   //concatenateV( g_collection["Art-08-crop"], x, y );
   //return;

  //load_case( g_collection["rocks1"], dataRoot + "/Rocks1", "view1.png", "view5.png", "disp1.png", 3);
  //////Case temp;   load_case(temp, dataRoot + "/Rocks1", "view1.png", "view5.png", "disp1.png", 3);
  //////crop( g_collection["rock1-crop"], temp, { { 60, 110 }, { 60+120, 110+60 } });
  //////load_case( g_collection["rocks1"], dataRoot + "/Rocks1", "view1.png", "view5.png", "disp1.png", 3);
  //return;

  //Case temp0;  crop( temp0, tempX, { { 0*120, 0 }, { 1*120, 200 } }); 
  //Case temp1;  crop( temp1, tempX, { { 1*120, 0 }, { 2*120, 200 } }); 
  //Case temp2;  crop( temp2, tempX, { { 2*120, 0 }, { 3*120, 200 } }); 
  //Case temp3;  crop( temp3, tempX, { { 3*120, 0 }, { 4*120, 200 } }); 
  //Case tempA;  concatenateV( tempA, temp0, temp1 );
  //Case tempB;  concatenateV( tempB, temp2, temp3 );

  //concatenateV( g_collection["rocks1-stack"], tempA, temp2 );
  //return;

  //load_case(g_collection["baby1"], dataRoot + "/Baby1", "view1.png", "view5.png", "disp1.png", 3);
  //Case temp; load_case( temp, dataRoot + "/Baby1", "view1.png", "view5.png", "disp1.png", 3);
  //crop( g_collection["baby1-crop2"], temp, { { 280 , 210 }, { 350, 360 } });
  //crop( g_collection["baby1-crop2"], temp, { { 300 , 120 }, { 400, 210 } });
  //return;

  //Case aC;  crop(aC, a, { { 0 , 0 }, { 400, 360 } });
  //Case b; load_case( b, dataRoot + "/Art", "view1.png", "view5.png", "disp1.png", 3);
  //Case bC;  crop(bC, b, { { 0 , 0 }, { 400, 360 } });
  //Case big;  concatenateV(big, aC, bC);
 
  //Case temp0;  crop( temp0, big, { { 0*100, 0 }, { 1*100, 715 } }); 
  //Case temp1;  crop( temp1, big, { { 1*100, 0 }, { 2*100, 715 } }); 
  //Case temp2;  crop( temp2, big, { { 2*100, 0 }, { 3*100, 715 } }); 
  //Case temp3;  crop( temp3, big, { { 3*100, 0 }, { 4*100, 715 } }); 
  //Case tempA;  concatenateV( tempA, temp0, temp1 );
  //Case tempB;  concatenateV( tempB, temp2, temp3 );

  //concatenateV( g_collection["big-stripe"], tempA, temp2 );
  //return;
  //crop( g_collection["Baby1-crop1"], g_collection["Baby1"], { { 165, 120 }, { 165 + 120, 120+50 } }); 
  //crop( g_collection["Baby1-crop2"], g_collection["Baby1"], { { 135, 265 }, { 135 + 120, 265+50 } }); 
  //crop( g_collection["Baby1-crop3"], g_collection["Baby1"], { {  40, 250 }, {  40 + 120, 250+50 } }); 
  //crop( g_collection["Baby1-crop4"], g_collection["Baby1"], { { 170, 175 }, { 170 + 120, 175+50 } }); 
  //concatenateV(g_collection["Baby1-cat0"], g_collection["Baby1-crop1"], g_collection["Baby1-crop2"]);
  //concatenateV(g_collection["Baby1-cat1"], g_collection["Baby1-crop3"], g_collection["Baby1-crop4"]);
  //concatenateV(g_collection["Baby1-catX"], g_collection["Baby1-cat0"],  g_collection["Baby1-cat1"]);
  //g_collection.erase("Baby1"); 
  //g_collection.erase("Baby1-crop1"); g_collection.erase("Baby1-crop2"); g_collection.erase("Baby1-crop3"); g_collection.erase("Baby1-crop4");
  //g_collection.erase("Baby1-cat0"); g_collection.erase("Baby1-cat1");

  //crop( g_collection["Art-crop"], g_collection["Art"], { {20,100}, { 130, 180} }); g_collection.erase( "Art" );


  //load_case(g_collection["Flowerpots"], dataRoot + "/Flowerpots", "view1.png", "view5.png", "disp1.png", 3);
  //return;

  //load_case( g_collection["Wood1"], dataRoot + "/Wood1", "view1.png", "view5.png", "disp1.png", 3);
  //Case temp; load_case( temp, dataRoot + "/Wood1", "view1.png", "view5.png", "disp1.png", 3 );
  ////crop(g_collection["Wood1-crop"], temp, { {30,250}, { 220, 320} });
  //crop(g_collection["Wood1-crop"], temp, { {64,320}, { 235, 367} });
  //crop(g_collection["Wood1-crop"], temp, { {250,150}, { 370, 200} });
  //crop(g_collection["Wood1-crop"], temp, { {0,190}, { 450, 220} });
  //crop(g_collection["Wood1-crop"], temp, { {0,160}, { 450, 200} });
  //crop(g_collection["Wood1-crop"], temp, { {0,230}, { 450, 310} });
  //crop(g_collection["Wood1-crop"], temp, { {0,270-40}, { 450, 270+40} });
  //crop(g_collection["Wood1-crop"], temp, { {0,335}, { 250, 360} }); //!< LEFT
  //crop(g_collection["Wood1-crop"], temp, { {0,150}, { 455, 150+90 } });
  //return;

  load_case( g_collection["Bowling1-big"], dataRoot + "/Bowling1", "view1.png", "view5.png", "disp1.png", 3);
  //Case temp;   load_case(temp, dataRoot + "/Bowling1", "view1.png", "view5.png", "disp1.png", 3 );
  //crop(g_collection["Bowling1-crop-07"], temp, { {0,125}, { 415, 165 } });
  ////crop(g_collection["Bowling1-crop"], temp, { {0,90}, { 415, 90+10 } });
  //crop(g_collection["Bowling1-350-crop-07"], temp, { {0, 350}, { 415,  350+10 } });
  return;

  // gallery
  load_case( g_collection["sawtooth"], dataRoot + "/sawtooth", "im2.png", "im6.png", "disp2.png", 8.049); 

  load_case( g_collection["Dolls"], dataRoot + "/Dolls", "view1.png", "view5.png", "disp1.png", 3 );
  load_case( g_collection["Baby1"], dataRoot + "/Baby1", "view1.png", "view5.png", "disp1.png", 3);

  load_case( g_collection["Art"], dataRoot  + "/Art",  "view1.png", "view5.png", "disp1.png", 3 );

  load_case( g_collection["Cloth1"], dataRoot + "/Cloth1", "view1.png", "view5.png", "disp1.png", 3 );
  load_case( g_collection["Cloth1-big"], dataRoot + "/Cloth1-big", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Reindeer"], dataRoot + "/Reindeer", "view1.png", "view5.png", "disp1.png", 3 );
  load_case(g_collection["tsukuba-016"], dataRoot + "/tsukuba", "1/combine_1-5_016_L.png", "1/combine_1-5_016_R.png", "truedisp.row3.col3.png", 4.319 );

  load_case( g_collection["Bowling1"], dataRoot + "/Bowling1", "view1.png", "view5.png", "disp1.png", 3 );

  load_case( g_collection["poster1"], dataRoot + "/poster1", "im2.png",    "im6.png", "disp2.png", 8.049 );
  load_case( g_collection["poster2"], dataRoot + "/poster2", "im2.png",    "im6.png", "disp2.png", 8.049 );
  load_case( g_collection["circle"], dataRoot  + "/circle",   "untitled-L.png", "untitled-R.png", "disparity.png", 3 );
  load_case( g_collection["cubes1"], dataRoot  + "/cubes1",  "cube-L.png", "cube-R.png", "disparity.png", 3 );

  load_case( g_collection["cones"], dataRoot  + "/cones",  "im2.png", "im6.png", "disp2.png", 4 );
  load_case( g_collection["Monopoly"], dataRoot  + "/Monopoly",  "view1.png", "view5.png", "disp1.png", 3 );

  load_case( g_collection["Baby2"], dataRoot + "/Baby2", "view1.png", "view5.png", "disp1.png", 3 );

  load_case( g_collection["Moebius"], dataRoot + "/Moebius", "view1.png", "view5.png", "disp1.png", 3 );
  load_case( g_collection["Lampshade2"], dataRoot + "/Lampshade2", "view1.png", "view5.png", "disp1.png", 3 );
  load_case( g_collection["Plastic"], dataRoot + "/Plastic", "view1.png", "view5.png", "disp1.png", 3 );
  load_case( g_collection["Rocks1"], dataRoot + "/Rocks1", "view1.png", "view5.png", "disp1.png", 3 );
  load_case( g_collection["Wood1"], dataRoot + "/Wood1", "view1.png", "view5.png", "disp1.png", 3 );
  //load_case( g_collection["Computer"], dataRoot + "/Computer", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Dolls"], dataRoot + "/Dolls", "view1.png", "view5.png", "disp1.png", 3 );
//load_case( g_collection["Drumsticks"], dataRoot + "/Drumsticks", "view1.png", "view5.png", "disp1.png", 1 );
  //load_case( g_collection["Dwarves"], dataRoot + "/Dwarves", "view1.png", "view5.png", "disp1.png", 1 );
  load_case( g_collection["Flowerpots"], dataRoot + "/Flowerpots", "view1.png", "view5.png", "disp1.png", 3 );
  load_case(g_collection["Flowerpots-big"], dataRoot + "/Flowerpots-big", "view1.png", "view5.png", "disp1.png", 1 );
  //load_case( g_collection["aujfa-eq"], dataRoot + "/aujfa", "im-eq-L.png", "im-eq-R.png", "disp1.png", 1 );
  //load_case( g_collection["aujfa"], dataRoot + "/aujfa", "imL.png", "imR.png", "disp1.png", 1 );
  load_case( g_collection["teddy"], dataRoot + "/teddy", "im2.png", "im6.png", "disp2.png", 4 );
  load_case( g_collection["venus"], dataRoot + "/venus", "im2.png", "im6.png", "disp2.png", 8 );
  load_case( g_collection["Laundry"], dataRoot + "/Laundry", "view1.png", "view5.png", "disp1.png", 3 );
  load_case( g_collection["Aloe"], dataRoot + "/Aloe", "view0.png", "view6.png", "disp1.png", 1 );
  load_case( g_collection["Baby3"], dataRoot + "/Baby3", "view0.png", "view1.png", "disp1.png", 3 );
 
  load_case( g_collection["tsukuba"],     dataRoot + "/tsukuba", "scene1.row3.col1.png", "scene1.row3.col5.png", "truedisp.row3.col3.png", 1 );
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
    auto quaity = compare(item.second.m_scale * disparity, item.second.m_disprity, 4 );
    std::string prefix  = item.first +  "_";
    std::string postfix = "_max";
    std::string number = format( (int)quaity, 7 );
    cv::imwrite( "disparity_" + prefix + number + postfix + ".png", item.second.m_scale *disparity );
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


int main_convolve_sliding( int argc, char* argv[] )
 {
  std::string dataRoot = "../../data";

  //Case mainFrame;   load_case( mainFrame, dataRoot + "/Cloth1-big", "view1.png", "view5.png", "disp1.png", 3 );
  //Case mainFrame;   load_case(mainFrame, dataRoot + "/Cloth1-big", "view1.png", "view5.png", "disp1.png", 1);
  Case mainFrame;   load_case(mainFrame, dataRoot + "/Cloth1", "view1.png", "view5.png", "disp1.png", 3 );

  int cropX = 0;
  int cropY = 0;
  int cropW = 120;
  int cropH = 200;
  int crop_stepX = 10;
  int crop_stepY = 20;
  Case theCrop; 
  crop( theCrop, mainFrame, { { cropX, cropY }, { cropX + cropW, cropY + cropH } });

  StereoConvolveMatch convolve;
  int tolerance_compare = 3;
  auto& matcher = convolve;
  
   {
    auto& item = theCrop;
    std::cout << "Dolls"<< std::endl;
    cv::Mat & left  = item.m_left;
    cv::Mat & right = item.m_right;

    std::string prefix =  "Dolls_";
    std::string postfix = "_max";
    std::string number = std::to_string( 0 );
    cv::Mat disparity;
    disparity = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

    convolve.initialize( left, right );
    convolve.m_restriction.clear();
 
    extern int findIndex( std::string const& signature );

    //convolve.m_restriction.push_back(-1);

    convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,2} );" ) );
    convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {2,1} );" ) );
    convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
    convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} );" ) );
    convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,2} );" ) );
    convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );" ) );
    convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,1} );" ) );
    convolve.m_restriction.push_back( findIndex( "filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {2,1} );" ) );


//convolve.m_square.m_trashold = 0.06 * convolve.m_restriction.size();
//convolve.m_square.m_trashold = 0.060 * 14; //!<??
//convolve.m_square.m_trashold = 0.045 * 13; //!<??
//convolve.m_square.m_trashold = 0.025 * 12;

    // convolve.process( disparity, left, right );
    int counter = 0;

    int best_quaity   = 0;
    int max_quaity = 0;

    cv::Mat hit_mask = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );
    for( int cycle_counter = 0;  convolve.m_restriction.size() < 240; ++cycle_counter)
     {
      if ( 0 == ( cycle_counter % 10) )
       {
        std::cout << "L";
        //convolve.m_restriction.push_back(-1);
       }

      // if( 1 < std::count(convolve.m_restriction.begin(), convolve.m_restriction.end(), -1) )
      //  {
      //   std::remove(convolve.m_restriction.begin(), convolve.m_restriction.end(), -1);
      //   std::cout << "X";
      //  }

    //max_quaity = 0;
    bool winner_have = false;
    int winner_position = 0;
    int winner_index = convolve.m_restriction[winner_position];

    int cycle_quality = 0;
    for( int position = 0; position < convolve.m_restriction.size(); ++position )
     {
      int local_index = convolve.m_restriction[position];

      for( int index = -1; index < (int)convolve.m_lasagnaL.depth(); ++index )
       {
        convolve.m_restriction[position] = index;
        disparity.setTo( cv::Scalar( 0 ) ); //= cv::Mat::disparity::zeros( left.rows, left.cols, CV_8UC1 );

        convolve.process( disparity, left, right );

        auto quaity = compare( item.m_scale * disparity, item.m_disprity, tolerance_compare );
      //quaity /= g_line;
        cycle_quality = std::max<int>( cycle_quality, (int)quaity);
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
          ofs << "//--- --- --- "<< std::setw(10) << "Cloth1-crop" << "; " << max_quaity << "; " << std::setw(10) << cycle_quality << std::endl;
          std::cout << "Quality: " << std::setw(10) << quaity <<"; C:"<< cycle_counter << "; P:"  << position << "-> ";
          std::cout <<"[" << std::setw( 3 ) << convolve.m_restriction.size() << "]";
          for( auto index : convolve.m_restriction )
           {
            extern std::vector<std::string> g_table;
            std::cout << std::setw(4) << index << "; ";
            if( ( 0 < index) && ( index < g_table.size() ) ) ofs << g_table[ index] << std::endl;
           }

          max_quaity = (int)quaity;
          std::cout << "***";
          cv::imwrite( "disparity_" + prefix + number + postfix + ".png", item.m_scale * disparity );

          //for( double disparity_scale = 1; disparity_scale < 5.0; disparity_scale += 0.01 )
          // {
          //  postfix = std::to_string( disparity_scale  );
          mask( hit_mask, item.m_scale * disparity, item.m_disprity, tolerance_compare );
           //std::cout << std::setw(6)<< disparity_scale << "; " << std::setw( 6 ) << quaity <<  std::endl;
          cv::imwrite( "disparity_" + prefix + number + postfix +"_mask" + ".png", hit_mask );
          // }exit( 0 );
          std::cout << std::endl;
        }
        if( 0 == (++counter % 1000) )
        {
          std::cout << std::setw( 8 ) << quaity << "-> " ;
          std::cout << "P:" << std::setw(2) << position << "| ";
          for( auto index : convolve.m_restriction )
          {
            std::cout << std::setw(4)<< index << "; ";
          }
          std::cout << std::endl;
        }
       }
      convolve.m_restriction[position] = local_index;
      std::cout << ".";
     }

    convolve.m_restriction[winner_position] = winner_index;

    //if( -1 == winner_index )
    // {
    //  convolve.m_restriction.erase( convolve.m_restriction.begin() + winner_position );
    //  //convolve.m_square.m_trashold = 0.1 * convolve.m_restriction.size();
    //  std::cout << "x";
    // }

    std::sort( convolve.m_restriction.rbegin(), convolve.m_restriction.rend() );

    if( ( false == winner_have ) && ( 0 == std::count( convolve.m_restriction.begin(), convolve.m_restriction.end(), -1 ) ) )
     {
      convolve.m_restriction.insert( convolve.m_restriction.begin(), -1 );
      //convolve.m_square.m_trashold = 0.1 * convolve.m_restriction.size();
      std::cout << "+";
     }

    cropX += crop_stepX; if( mainFrame.m_left.cols <= cropX + cropW ) cropX = 0;
    cropY += crop_stepY; if( mainFrame.m_left.rows <= cropY + cropH ) cropY = 0;
    crop( theCrop, mainFrame, { { cropX, cropY }, { cropX + cropW, cropY + cropH } });
    max_quaity =(int) ( max_quaity * 0.80 );
    convolve.initialize( left, right );
    convolve.m_restriction.insert(convolve.m_restriction.begin(), -1 );

    std::cout << "o " << cropX << "," << cropY << std::setw(10) << max_quaity << "; " << std::setw(10) << cycle_quality << std::endl;
   }
  }


  return EXIT_SUCCESS;
 }


int g_line = 0;
int main_convolve_increment( int argc, char* argv[] )
 {
  load_files();

  cv::Mat left;
  cv::Mat right;

  StereoConvolveMatch convolve;

  int tolerance_compare = 4;
  auto& matcher = convolve;
  for( auto const& item : g_collection )
   {
    std::cout << item.first << std::endl;
    cv::Mat left  = item.second.m_left;
    cv::Mat right = item.second.m_right;

    std::string prefix = item.first + "_";
    std::string postfix = "_max";
    std::string number = std::to_string( 0 );
    cv::Mat disparity = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );
    cv::Mat hit_mask  = cv::Mat::zeros( left.rows, left.cols, CV_8UC1 );

    convolve.initialize( left, right );
    convolve.m_restriction.clear();
 
    extern int findIndex( std::string const& signature );


//convolve.m_restriction.push_back( findIndex("   " ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.5, math::constants::PHI / 2.0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.5, math::constants::PHI / 2.0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  75 ), 0.5, math::constants::PHI / 2.0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.5, math::constants::PHI / 2.0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  75 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  75 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  75 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.5, math::constants::PHI / 2.0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.5, math::constants::PHI / 2.0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,2} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,2} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,2} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,2} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {2,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {2,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {3,1} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {3,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {1,2} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {2,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {2,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {2,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {2,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.5, math::constants::PHI / 2.0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {3,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {2,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,3} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,2} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );" ) );
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,2} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,2} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,2} );"));
convolve.m_restriction.push_back( findIndex("filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,2} );"));

 
std::sort(convolve.m_restriction.rbegin(), convolve.m_restriction.rend());
convolve.m_restriction.erase(std::remove(convolve.m_restriction.begin(), convolve.m_restriction.end(), -1), convolve.m_restriction.end());
convolve.m_restriction.push_back( -1 );

std::vector< double > trashold =
 {
  0.2,// 1.000 *  0,
  0.22,// 0.600 *  1,
  0.885778,// 0.400 *  2,
  1.27165,// 0.400 *  3,
  1.96254,  // 0.460 *  4,
  1.88685,// 0.390 *  5,
  2.26796,// 1.000 *  6,
  3.2559,// 1.120 *  7,
  0.01,// 1.100 *  8,
  0.01,// 1.110 *  9,
  0.01,// 1.100 * 10,
  0.01,// 1.090 * 11,
  0.01,// 1.080 * 12,
  0.01,// 1.070 * 13,
  0.01, // 1.060 * 14,
  0.01, // 1.060 * 15,
  0.01, // 1.060 * 16,
  0.01, // 1.060 * 17,
  0.01, // 1.060 * 18,
  0.01, // 1.060 * 19,
  0.01, // 1.060 * 20,
};

  if( convolve.m_restriction.size() < trashold.size() )
   {
    convolve.m_square.m_trashold = trashold[convolve.m_restriction.size()];
   }
  else
   {
    convolve.m_square.m_trashold = 10000;
   }

  //convolve.m_square.m_trashold = 0.1 * convolve.m_restriction.size();
  convolve.m_square.m_trashold = 10000;

    std::cout << "Control image... " <<  std::endl;
    convolve.process( disparity, left, right );

    auto quality = compare( item.second.m_scale * disparity, item.second.m_disprity, tolerance_compare );
    number = format((int)quality, 6) + "_";
    cv::imwrite( "disparityCtrl_" + prefix + number + postfix + ".png", item.second.m_scale * disparity);

    /* --- */
    //for (double scale = 3; scale < 5; scale += 0.01)
    // {
    //  auto quality = compare( scale * disparity, item.second.m_disprity, tolerance_compare);
    //   prefix =format((int)quality, 6) + "_";
    //  number = format((int)(scale*1000), 6) + "_";
    //  //cv::imwrite("disparity_" + prefix + number + postfix + ".png", item.second.m_scale * disparity);
    //  cv::Mat hit_mask = cv::Mat::zeros(left.rows, left.cols, CV_8UC1);
    //  mask( hit_mask, scale * disparity, item.second.m_disprity, tolerance_compare);
    //  cv::imwrite("mask_" + prefix + number + postfix + "_mask" + ".png", hit_mask );
    //}
    //continue;
/* --- */

    std::cout << "Loop ... " <<  std::endl;
    int counter = 0;
    int index_begin = -1;
    int index_end = 0*(int)convolve.m_lasagnaL.depth();

    int best_quaity   = 0;
    int max_quaity = 0;

    for( int cycle_counter = 0;  convolve.m_restriction.size() < 10500; ++cycle_counter)
     {
      if ( 0 == ( cycle_counter % 9 ) )
       {
        //++g_line;
       // std::cout << "L";
          //index_end += 30;
          //if( (int)convolve.m_lasagnaL.depth() <= index_end ) index_end = (int)convolve.m_lasagnaL.depth();
       }

      // if( 1 < std::count(convolve.m_restriction.begin(), convolve.m_restriction.end(), -1) )
      //  {
      //   std::remove(convolve.m_restriction.begin(), convolve.m_restriction.end(), -1);
      //   std::cout << "X";
      //  }

    //max_quaity = 0;
    bool winner_have = false;
    int winner_position = 0;
    int winner_index = convolve.m_restriction[winner_position];
    for( int position = 0; position < convolve.m_restriction.size(); ++position )
     {
      int local_index = convolve.m_restriction[position];

      for( int index = index_begin; index < (int)index_end; ++index )
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
          //if (4 == convolve.m_restriction.size())
          {
              std::ofstream ofs("disparity_" + prefix + number + postfix + ".txt", std::ios_base::app);
              ofs << "//--- --- --- " << item.first << ";  " << quaity << " _ " << 100 * quaity / double( left.rows*left.cols) << std::endl;
              ofs << "//--- --- --- " << convolve.m_restriction.size() << std::endl;
              ofs << "//--- --- --- " << convolve.m_square.m_trashold << " ;  " << convolve.m_square.m_trashold / convolve.m_restriction.size() << " ;" << std::endl;
              ofs << "//--- --- --- " << "begin:" << format(index_begin, 4) << "; " << "end:" << format(index_end, 4) << std::endl;

              std::cout << "Quality: " << quaity << "; C:" << cycle_counter << "; P:" << position << "-> ";
              std::cout << "[" << std::setw(3) << convolve.m_restriction.size() << "]";
              for (auto index : convolve.m_restriction)
              {
                  extern std::vector<std::string> g_table;
                  std::cout << std::setw(4) << index << "; ";
                  if ((0 < index) && (index < g_table.size())) ofs << g_table[index] << std::endl;
              }
          }

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
          std::cout << std::setw( 8 ) << quaity << "-> " ;
          std::cout << "P:" << std::setw(2) << position << "| ";
          for( auto index : convolve.m_restriction )
          {
            std::cout << std::setw(4)<< index << "; ";
          }
          std::cout << std::endl;
        }
       }
      convolve.m_restriction[position] = local_index;
      std::cout << ".";
     }

    if( true == winner_have )
     {
      convolve.m_restriction[winner_position] = winner_index;
      if( -1 == winner_index )
       {
        convolve.m_restriction.erase( convolve.m_restriction.begin() + winner_position );
        std::cout << "\033[31;40m" << "X(" << winner_position << ")" << "\033[37;40m";
       }
     }
    else
      {
       convolve.m_restriction.push_back(  -1 );

       if( 1 < std::count( convolve.m_restriction.begin(), convolve.m_restriction.end(), -1 ) )
        {
         std::cout << "DONE!!!"; break;

         std::ofstream ofs( "X_" + format(index_begin, 4 ) + "-" + format(index_end, 4) + "_disparity_" + number + postfix + ".txt", std::ios_base::app);
         ofs << "//--- --- --- " << item.first << ";  "<< "Q:" << max_quaity << "; " << (100 * max_quaity) / double(left.cols * left.rows) << std::endl;
         ofs << "//--- --- --- " << convolve.m_restriction.size() << std::endl;
         ofs << "//--- --- --- " << convolve.m_square.m_trashold << " ;  " << convolve.m_square.m_trashold / convolve.m_restriction.size() << " ;" << std::endl;
         ofs << "//--- --- --- " << "l:" << format(index_begin, 4) << ", " << format(index_end, 4)<<  std::endl;
         
         for( auto index : convolve.m_restriction )
          {
           extern std::vector<std::string> g_table;
           std::cout << std::setw(4) << index << "; ";
           if ((0 < index) && (index < g_table.size())) ofs << g_table[index] << std::endl;
          }
         max_quaity = 0;
         //convolve.m_square.m_trashold *= 1.075;
         std::cout << "\033[32;40m" << "NEW:" << convolve.m_square.m_trashold << ";" << "\033[37;40m";
         index_begin += 36;  
         index_end   += 36;
         if( convolve.m_lasagnaL.depth() < index_end ) 
          {
           std::cout << "DONE!!!";
           break;
          }

         convolve.m_restriction.clear();
         convolve.m_restriction.insert( convolve.m_restriction.begin(), -1 );
        }

       std::cout << "\033[32;40m" << "ROUND" << "\033[37;40m";
     }

    std::sort( convolve.m_restriction.rbegin(), convolve.m_restriction.rend() );

    std::cout << "o";
    g_line += 10;
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
 //  main_single( argc, argv );
  //main_convolve_sliding(argc, argv);
  //main_convolve_combination(  argc,  argv );
  main_convolve_increment(  argc,  argv );
  //main_rest( argc, argv );
 }
