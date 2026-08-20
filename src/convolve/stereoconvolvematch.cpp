#include <fstream>
#include "math/math.hpp"
#include "./stereoconvolvematch.hpp"

extern std::string format( int const& value, int w );

void make_gabor0( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
/* 1246 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,2} );  normalize( filter ); bank.push_back( filter );
/* 1143 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {1,2} );  normalize( filter ); bank.push_back( filter );
/* 1075 */filter.size( { (SizeType)24, (SizeType)24 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize( filter ); bank.push_back( filter );
/*  933 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize( filter ); bank.push_back( filter );
/*  925 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize( filter ); bank.push_back( filter );
/*  581 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,2} );  normalize( filter ); bank.push_back( filter );
/*  545 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,2} );  normalize( filter ); bank.push_back( filter );
/*  499 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,2} );  normalize( filter ); bank.push_back( filter );
/*  447 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} );  normalize( filter ); bank.push_back( filter );
/*  405 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {2,1} );  normalize( filter ); bank.push_back( filter );
/*  386 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {2,1} );  normalize( filter ); bank.push_back( filter );
/*  318 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {2,1} );  normalize( filter ); bank.push_back( filter );
/*  299 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {2,1} );  normalize( filter ); bank.push_back( filter );
/*  265 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} );  normalize( filter ); bank.push_back( filter );
/*  194 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} );  normalize( filter ); bank.push_back( filter );
/*  161 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );  normalize( filter ); bank.push_back( filter );
/*   72 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {1,1} );    normalize(filter); bank.push_back(filter);
  }

void make_gabor1( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;

  Filter filter;
/* 1122 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,3} ); normalize( filter ); bank.push_back( filter );
/* 1094 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,3} ); normalize( filter ); bank.push_back( filter );
/* 1089 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {1,3} ); normalize( filter ); bank.push_back( filter );
/* 1055 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {1,2} ); normalize( filter ); bank.push_back( filter );
/*  798 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,1} ); normalize( filter ); bank.push_back( filter );
/*  643 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,3} );                      normalize( filter ); bank.push_back( filter );
/*  639 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,3} );                      normalize( filter ); bank.push_back( filter );
/*  628 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,3} );                      normalize( filter ); bank.push_back( filter );
/*  621 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,3} );                      normalize( filter ); bank.push_back( filter );
/*  618 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,3} );                      normalize( filter ); bank.push_back( filter );
/*  569 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,2} );                      normalize( filter ); bank.push_back( filter );
/*  548 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,2} );                      normalize( filter ); bank.push_back( filter );
/*  540 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {1,2} );                      normalize( filter ); bank.push_back( filter );
/*  139 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,1} );                      normalize( filter ); bank.push_back( filter );
}

void make_gabor2( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
/* 2289 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {1,3} ); normalize( filter ); bank.push_back( filter );
/* 2254 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,3} ); normalize( filter ); bank.push_back( filter );
/* 2091 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {1,2} ); normalize( filter ); bank.push_back( filter );
/* 1773 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {2,1} ); normalize( filter ); bank.push_back( filter );
/* 1765 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {2,1} ); normalize( filter ); bank.push_back( filter );
/* 1366 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,3} ); normalize( filter ); bank.push_back( filter );
/* 1268 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,3} ); normalize( filter ); bank.push_back( filter );
/* 1290 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,3} ); normalize( filter ); bank.push_back( filter );
/*  975 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} ); normalize( filter ); bank.push_back( filter );
/*  940 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,2} ); normalize( filter ); bank.push_back( filter );
/*  583 */filter.size( { (SizeType)29, (SizeType)29 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {2,1} ); normalize( filter ); bank.push_back( filter );
/*  426 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {2,1} ); normalize( filter ); bank.push_back( filter );
/*  383 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {2,1} ); normalize( filter ); bank.push_back( filter );
/*  373 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} ); normalize( filter ); bank.push_back( filter );
/*  170 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} ); normalize( filter ); bank.push_back( filter );
/*   72 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {1,1} ); normalize( filter ); bank.push_back( filter );
/*    9 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} ); normalize( filter ); bank.push_back( filter );

}
void make_gabor3( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
//--- --- --- sawtooth-crop;  2918
/* 2129 */filter.size( { (SizeType)30, (SizeType)30 } ); gabor( filter, math::geometry::deg2rad(  75 ), 0.5, math::constants::PHI / 2.0, {3,1} ); normalize(filter); bank.push_back(filter);
/* 2273 */filter.size( { (SizeType)32, (SizeType)32 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {3,1} ); normalize(filter); bank.push_back(filter);
/* 2213 */filter.size( { (SizeType)31, (SizeType)31 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {3,1} ); normalize(filter); bank.push_back(filter);
/* 2039 */filter.size( { (SizeType)29, (SizeType)29 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} ); normalize(filter); bank.push_back(filter);
/* 1585 */filter.size( { (SizeType)24, (SizeType)24 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {3,1} ); normalize(filter); bank.push_back(filter);
/* 1119 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {2,1} );normalize( filter ); bank.push_back( filter );
/*  839 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} );normalize( filter ); bank.push_back( filter );
/*  834 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {3,1} );normalize( filter ); bank.push_back( filter );
/*  689 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  75 ), 0.5, math::constants::PHI / 2.0, {3,1} ); normalize( filter ); bank.push_back( filter );
/*  504 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {3,1} ); normalize( filter ); bank.push_back( filter );                      
/*  408 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                      normalize( filter ); bank.push_back( filter );
/*  339 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {1,2} ); normalize( filter ); bank.push_back( filter );
/*  288 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                      normalize( filter ); bank.push_back( filter );
/*  277 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} );                      normalize( filter ); bank.push_back( filter );
/*  255 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} );                      normalize( filter ); bank.push_back( filter );
/*  178 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,3} ); normalize( filter ); bank.push_back( filter );
/*  119 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} );                      normalize( filter ); bank.push_back( filter );
/*    9 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );                      normalize( filter ); bank.push_back( filter );


}
void make_gabor4( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
/* 2273 */filter.size( { (SizeType)32, (SizeType)32 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {3,1} );  normalize( filter ); bank.push_back( filter );
/* 2039 */filter.size( { (SizeType)29, (SizeType)29 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} );  normalize( filter ); bank.push_back( filter );
/* 1871 */filter.size( { (SizeType)28, (SizeType)28 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );  normalize( filter ); bank.push_back( filter );
/* 1751 */filter.size( { (SizeType)26, (SizeType)26 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {1,1} ); normalize( filter ); bank.push_back( filter );
/* 1585 */filter.size( { (SizeType)24, (SizeType)24 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {3,1} ); normalize( filter ); bank.push_back( filter );
/* 1534 */filter.size( { (SizeType)24, (SizeType)24 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,3} ); normalize( filter ); bank.push_back( filter );
/*  280 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {2,1} ); normalize( filter ); bank.push_back( filter );
/* 1078 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,3} ); normalize(filter); bank.push_back(filter);
/*  991 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,3} ); normalize( filter ); bank.push_back( filter );
/*  835 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {3,1} ); normalize( filter ); bank.push_back( filter );
/*  693 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {3,1} ); normalize(filter); bank.push_back(filter);
/*  636 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} ); normalize( filter ); bank.push_back( filter );
/*  441 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,2} ); normalize( filter ); bank.push_back( filter );
/*  350 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,3} ); normalize( filter ); bank.push_back( filter );
/*  317 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  75 ), 0.5, math::constants::PHI / 2.0, {2,1} ); normalize( filter ); bank.push_back( filter );
/*  255 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} ); normalize(filter); bank.push_back(filter);
/*  178 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,3} ); normalize(filter); bank.push_back(filter);
/*    9 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} ); normalize(filter); bank.push_back(filter);

}

void make_gabor5( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
/* 1265 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 2307 */filter.size( { (SizeType)32, (SizeType)32 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 2273 */filter.size( { (SizeType)32, (SizeType)32 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 2268 */filter.size( { (SizeType)32, (SizeType)32 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 2228 */filter.size( { (SizeType)32, (SizeType)32 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 2222 */filter.size( { (SizeType)32, (SizeType)32 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 2123 */filter.size( { (SizeType)30, (SizeType)30 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 2033 */filter.size( { (SizeType)29, (SizeType)29 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 2007 */filter.size( { (SizeType)29, (SizeType)29 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,3} );                       normalize(filter); bank.push_back(filter);
/* 1985 */filter.size( { (SizeType)29, (SizeType)29 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1910 */filter.size( { (SizeType)28, (SizeType)28 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1673 */filter.size( { (SizeType)25, (SizeType)25 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1631 */filter.size( { (SizeType)25, (SizeType)25 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1534 */filter.size( { (SizeType)24, (SizeType)24 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,3} );                       normalize(filter); bank.push_back(filter);
/* 1515 */filter.size( { (SizeType)24, (SizeType)24 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} );                       normalize(filter); bank.push_back(filter);
/* 1368 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1245 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {1,2} );  normalize(filter); bank.push_back(filter);
/* 1151 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1081 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1071 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {1,3} );  normalize(filter); bank.push_back(filter);
/*  944 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);

 }

void make_gabor6( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;

/* 1012 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {3,1} );                          normalize(filter); bank.push_back(filter);
/*  969 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*  932 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,3} );                          normalize(filter); bank.push_back(filter);
/*  917 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,2} );                          normalize(filter); bank.push_back(filter);
/*  915 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} );                          normalize(filter); bank.push_back(filter);
/*  905 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*  873 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {3,1} );     normalize(filter); bank.push_back(filter);
/*  850 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,1} );     normalize(filter); bank.push_back(filter);
/*  826 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {2,1} );                          normalize(filter); bank.push_back(filter);
/*  824 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {2,1} );                          normalize(filter); bank.push_back(filter);
/*  790 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*  906 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*  680 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {2,1} );     normalize(filter); bank.push_back(filter);
/*  617 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,2} );                          normalize(filter); bank.push_back(filter);
/*  526 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,2} );     normalize(filter); bank.push_back(filter);
/*  524 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {1,2} );     normalize(filter); bank.push_back(filter);
/*  509 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  75 ), 0.5, math::constants::PHI / 2.0, {3,1} );     normalize(filter); bank.push_back(filter);
/*  478 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {3,1} );                          normalize(filter); bank.push_back(filter);
/*  462 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {2,1} );                          normalize(filter); bank.push_back(filter);
/*  430 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*  426 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*  425 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*  395 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,3} );                          normalize(filter); bank.push_back(filter);
/*  321 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {2,1} );     normalize(filter); bank.push_back(filter);
/*  270 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,3} );                          normalize(filter); bank.push_back(filter);
/*  188 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*  176 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {1,3} );     normalize(filter); bank.push_back(filter);
/*   68 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*   63 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);
/*    5 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );                          normalize(filter); bank.push_back(filter);

 }

void make_gabor7(std::vector<Filter>& bank)
 {
    typedef std::size_t  SizeType;
    Filter filter;

/* 1102 */filter.size( { (SizeType)24, (SizeType)24 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,2} ); normalize(filter); bank.push_back(filter);
/* 1025 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} ); normalize(filter); bank.push_back(filter);
/*  694 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,3} ); normalize(filter); bank.push_back(filter);
/*  514 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,3} ); normalize(filter); bank.push_back(filter);
/*  478 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {3,1} ); normalize(filter); bank.push_back(filter);
/*  456 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} ); normalize(filter); bank.push_back(filter);
/*  450 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,3} ); normalize(filter); bank.push_back(filter);
/*  450 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,3} ); normalize(filter); bank.push_back(filter);
/*  447 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,3} ); normalize(filter); bank.push_back(filter);
/*  440 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,2} ); normalize(filter); bank.push_back(filter);
/*  429 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} ); normalize(filter); bank.push_back(filter);
/*  421 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} ); normalize(filter); bank.push_back(filter);
/*  391 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,3} ); normalize(filter); bank.push_back(filter);
/*  298 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {3,1} ); normalize(filter); bank.push_back(filter);
/*  291 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {3,1} ); normalize(filter); bank.push_back(filter);
/*  288 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} ); normalize(filter); bank.push_back(filter);
/*  276 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} ); normalize(filter); bank.push_back(filter);
/*  272 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,3} ); normalize(filter); bank.push_back(filter);
/*  217 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} ); normalize(filter); bank.push_back(filter);
/*  135 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} ); normalize(filter); bank.push_back(filter);
/*   88 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,3} ); normalize(filter); bank.push_back(filter);
/*   74 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,2} ); normalize(filter); bank.push_back(filter);
/*   64 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} ); normalize(filter); bank.push_back(filter);
/*   27 */filter.size( { (SizeType) 6, (SizeType) 6 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,3} ); normalize(filter); bank.push_back(filter);

 }
void make_gabor8(std::vector<Filter>& bank)
 {
  typedef std::size_t  SizeType;
  Filter filter;

/* 1910 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,3} );    normalize(filter); bank.push_back(filter);
/* 1822 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,2} );                         normalize(filter); bank.push_back(filter);
/* 1815 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} );                         normalize(filter); bank.push_back(filter);
/* 1804 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} );                         normalize(filter); bank.push_back(filter);
/* 1750 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,1} );    normalize(filter); bank.push_back(filter);
/* 1746 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,1} );    normalize(filter); bank.push_back(filter);
/* 1688 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,1} );                         normalize(filter); bank.push_back(filter);
/* 1444 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} );                         normalize(filter); bank.push_back(filter);
/*  908 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {1,1} );    normalize(filter); bank.push_back(filter);
/*  730 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );                         normalize(filter); bank.push_back(filter);
/*  661 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {1,1} );    normalize(filter); bank.push_back(filter);
/*  485 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );                         normalize(filter); bank.push_back(filter);
/*  456 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,2} );    normalize(filter); bank.push_back(filter);
/*  369 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );                         normalize(filter); bank.push_back(filter);
/*  361 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} );                         normalize(filter); bank.push_back(filter);
/*  307 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.5, math::constants::PHI / 2.0, {1,1} );    normalize(filter); bank.push_back(filter);
/*  150 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,3} );                         normalize(filter); bank.push_back(filter);

 }

void make_gabor9(std::vector<Filter>& bank)
 {
  typedef std::size_t  SizeType;
  Filter filter;
/* 2013 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 2005 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1993 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 1977 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1969 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1967 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1959 */filter.size( { (SizeType)23, (SizeType)23 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1893 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1887 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1884 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1873 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 1859 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1852 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1849 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1845 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1837 */filter.size( { (SizeType)22, (SizeType)22 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1770 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1766 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1764 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1763 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 1737 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1730 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1728 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1726 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1721 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1718 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1716 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1652 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1646 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1644 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1635 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 1632 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 1618 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1613 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1609 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1608 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1605 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1599 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1596 */filter.size( { (SizeType)20, (SizeType)20 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1533 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1527 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1524 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1513 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 1500 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/* 1497 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1491 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1488 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1487 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1477 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1451 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1443 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1413 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1407 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1404 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1380 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/* 1377 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1371 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1368 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1356 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1323 */filter.size( { (SizeType)18, (SizeType)18 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1284 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1260 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/* 1258 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1250 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1246 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1241 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1237 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1211 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1203 */filter.size( { (SizeType)17, (SizeType)17 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1173 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1166 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1152 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 1151 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/* 1142 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/* 1138 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1130 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1126 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1121 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1116 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1090 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1082 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/* 1055 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1046 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/* 1040 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 1033 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/* 1020 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/* 1019 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1010 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/* 1005 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/* 1000 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  996 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  971 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  969 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  962 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  924 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  915 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/*  900 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  899 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  891 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  885 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  877 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  851 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  843 */filter.size( { (SizeType)14, (SizeType)14 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  813 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  805 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  794 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/*  790 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  784 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  780 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  778 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  769 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  766 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  759 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  756 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  729 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  723 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  720 */filter.size( { (SizeType)13, (SizeType)13 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  709 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {1,3} );  normalize(filter); bank.push_back(filter);
/*  693 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  687 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  666 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  660 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  656 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  651 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  647 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  637 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  627 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,3} );                       normalize(filter); bank.push_back(filter);
/*  609 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  603 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  600 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  575 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  566 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  549 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  543 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  528 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  526 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  518 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  507 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,3} );                       normalize(filter); bank.push_back(filter);
/*  491 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  488 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  484 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  481 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  459 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {1,2} );  normalize(filter); bank.push_back(filter);
/*  444 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  441 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/*  435 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/*  419 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  410 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  408 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  407 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  397 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  390 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  90), 0.618975, 0, {1,3} );                       normalize(filter); bank.push_back(filter);
/*  380 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 120), 0.618975, 0, {1,2} );                       normalize(filter); bank.push_back(filter);
/*  375 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} );                       normalize(filter); bank.push_back(filter);
/*  370 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  363 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  353 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(  75 ), 0.5, math::constants::PHI / 2.0, {1,3} );  normalize(filter); bank.push_back(filter);
/*  335 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  325 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  311 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  307 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  302 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  286 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad( 150), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  277 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  255 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,2} );                       normalize(filter); bank.push_back(filter);
/*  251 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  244 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  241 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad(  15), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  215 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.5, math::constants::PHI / 2.0, {3,1} );  normalize(filter); bank.push_back(filter);
/*  188 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  183 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  180 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*  179 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  168 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*  156 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*  151 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 105), 0.618975, 0, {1,3} );                       normalize(filter); bank.push_back(filter);
/*  131 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 165), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  123 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*  100 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.5, math::constants::PHI / 2.0, {1,2} );  normalize(filter); bank.push_back(filter);
/*   82 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/*   73 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.5, math::constants::PHI / 2.0, {2,1} );  normalize(filter); bank.push_back(filter);
/*   67 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*   60 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(   0 ), 0.5, math::constants::PHI / 2.0, {1,1} );  normalize(filter); bank.push_back(filter);
/*   51 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  45), 0.618975, 0, {3,1} );                       normalize(filter); bank.push_back(filter);
/*   36 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0, {2,1} );                       normalize(filter); bank.push_back(filter);
/*   28 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0, {1,3} );                       normalize(filter); bank.push_back(filter);
/*    9 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 135), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*    5 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  75), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);
/*    2 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  30), 0.618975, 0, {1,1} );                       normalize(filter); bank.push_back(filter);

}

void make_laplace0( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
  bank.push_back( filter );
 }

typedef std::size_t SizeType;
typedef double  ScalarType;
typedef std::array<ScalarType, 2>  Scalar2DType;

SizeType g_count=0;
std::ofstream g_ofs( "filter-table.txt" );
std::vector<std::string> g_table;

int findIndex( std::string const& signature )
 {
  for( int index=0; index < g_table.size(); ++ index )
   {
    auto const& heist = g_table[index];
    auto position = heist.find( signature );
    if( position == std::string::npos ) continue;
    return index;
   }
  return -1;
 }

void make_laplace( std::vector<Filter>& bank, SizeType const& size_begin, SizeType const& size_end  )
 {
  for( auto size = size_begin; size < size_end; size += 1 )
   {
    std::stringstream ss;

    bank.resize( bank.size() + 1 );
    auto& filter = bank.back();
    filter.size( { (SizeType)size, (SizeType)size } );
    laplace( filter, 0.5, 0 );
    //save( "filter_laplace_" + format( (int)g_count, 3 ) +"_"+ format( (int)size, 3 ) +".png", filter );
    normalize( filter );

    ss << "/* " << std::setw( 4 ) << g_count << " */";
    ss << "filter.size( { (SizeType)" << size << ", (SizeType)" << size << " } ); ";
    ss << "laplace( filter, 0.5, 0 );"  ;

    g_ofs << ss.str() << std::endl; 
    g_table.push_back( ss.str() );

    ++g_count;
   }
  std::cout << "Total: " << g_count << std::endl;
 }

void make_gabor_simetric( std::vector<Filter>  & bank, SizeType const& size_begin, SizeType const& size_end, SizeType const& rotation_total, Scalar2DType const& press={1,1} )
 {
  typedef std::size_t  SizeType;
  Filter filter;

  for( int size = (int)size_begin; size < (int)size_end; size += 1 )
  {
    for( int index = 0; index < rotation_total; ++index )
    {
      std::stringstream ss;

      double angle = index * 180.0 / rotation_total;
      //if( 180 - 10 < angle ) continue;
      //if( angle < 10 ) continue;
      /**/

      bank.resize( bank.size() + 1 );
      auto& filterA = bank.back();
      filterA.size( { (SizeType)size, (SizeType)size } );
      gabor( filterA, math::geometry::deg2rad( angle ), 0.618975, 0, press );
      //save( "gabor[" + format( (int)g_count, 3 ) + "_A_" + format( size, 3 ) + "_" + format( (int)(angle), 3 ) + "].png", filterA );
      normalize( filterA );

      ss << "/* " << std::setw( 4 ) << g_count << " */";
      ss << "filter.size( { (SizeType)" << std::setw( 2 )<< size << ", (SizeType)" << std::setw( 2 ) << size << " } ); ";
      ss << "gabor( filter, math::geometry::deg2rad( " << std::setw( 3 ) << angle << "), 0.618975, 0" << ", {" << press[0] << "," << press[1] << "} );";

      g_ofs << ss.str() << std::endl;
      g_table.push_back( ss.str() );

      ++g_count;
    }
  }
 }

void make_gabor_non_simetric( std::vector<Filter>  & bank, SizeType const& size_begin, SizeType const& size_end, SizeType const& rotation_total, Scalar2DType const& press = { 1,1 } )
 {
  for( int size = (int)size_begin; size < (int)size_end; size += 2 )
  {
    for( int index = 0; index < rotation_total; ++index )
    {
      std::stringstream ss;
      double angle = index * 180.0 / rotation_total;
      //if( 180 - 10 < angle ) continue;
      //if( angle < 10 ) continue;
      /**/
      bank.resize( bank.size() + 1 );
      auto& filterB = bank.back();
      filterB.size( { (SizeType)size, (SizeType)size } );
      gabor( filterB, math::geometry::deg2rad( angle ), 0.5, math::constants::PHI / 2.0, press );
      //save( "gabor[" + format( (int)g_count, 3 ) + "_B_" + format( size, 3 ) + "_" + format( (int)(angle), 3 ) + "].png", filterB );
      normalize( filterB );

      ss << "/* " << std::setw( 4 ) << g_count << " */";
      ss << "filter.size( { (SizeType)" << std::setw( 2 ) << size << ", (SizeType)" << std::setw( 2 ) << size << " } ); ";
      ss << "gabor( filter, math::geometry::deg2rad( " << std::setw( 3 ) <<angle << " ), 0.5, math::constants::PHI / 2.0" << ", {" << press[0] << "," << press[1] << "} );";

      g_ofs << ss.str() << std::endl;
      g_table.push_back( ss.str() );

      ++g_count;
    }
  }
 }

StereoConvolveMatch::StereoConvolveMatch()
 {
  m_square.m_range = 160;
  g_count = 0;

  //make_gabor0( m_bank );
  //make_gabor1( m_bank );
  //make_gabor2( m_bank );
  //make_gabor3( m_bank );
  //make_gabor4( m_bank );  
  //make_gabor5( m_bank );
  //make_gabor6( m_bank );
  //make_gabor7( m_bank );
  //make_gabor8( m_bank );
   //make_gabor9( m_bank );
  //make_laplace0( m_bank );

  int resolution = 12;
  for( int radius=14; radius < 15; radius+= 1 )
   {
    make_gabor_simetric( m_bank, radius, radius+1, resolution, { 1, 1 } );
    make_gabor_simetric( m_bank, radius, radius+1, resolution, { 1, 2 } );
    make_gabor_simetric( m_bank, radius, radius+1, resolution, { 1, 3 } );
    //make_gabor_simetric( m_bank, radius, radius+1, resolution, { 2, 1 } );
    //make_gabor_simetric( m_bank, radius, radius+1, resolution, { 3, 1 } );
    //if( 0 ==( radius%2 ) )
     {
      make_gabor_non_simetric( m_bank, radius, radius+1, resolution, { 1, 1 } );
      make_gabor_non_simetric( m_bank, radius, radius+1, resolution, { 1, 2 } );
      make_gabor_non_simetric( m_bank, radius, radius+1, resolution, { 1, 3 } );
      //make_gabor_non_simetric( m_bank, radius, radius+1, resolution, { 2, 1 } );
      //make_gabor_non_simetric( m_bank, radius, radius+1, resolution, { 3, 1 } );
     }
   }

  /*
  make_gabor_simetric( m_bank, 7, 33, resolution, {1,1} );

  make_gabor_simetric( m_bank, 7, 33, resolution, {2,1} );
  make_gabor_simetric( m_bank, 7, 33, resolution, {3,1} );

  make_gabor_simetric( m_bank, 7, 33, resolution, { 1, 2 } );
  make_gabor_simetric( m_bank, 7, 33, resolution, { 1, 3 } );

  make_gabor_non_simetric( m_bank, 6, 33, resolution, {1,1} );

  make_gabor_non_simetric(m_bank, 6, 33, resolution, {2,1});
  make_gabor_non_simetric( m_bank, 6, 33, resolution, {3,1});

  make_gabor_non_simetric( m_bank, 6, 33, resolution, {1,2} );
  make_gabor_non_simetric( m_bank, 6, 33, resolution, {1,3} );
  */

 // make_laplace( m_bank, 6, 65 );
 //make_laplace( m_bank, 6, 65 );

  g_ofs.close();

  m_restriction.resize( m_bank.size() );
  for( int index=0; index < m_bank.size(); ++ index ) m_restriction[index] = index;

  std::cout << "Total: " << g_count << std::endl;
 }

void StereoConvolveMatch::initialize( ImageType const& left, ImageType const& right )
 {
  m_lasagnaL.size(  left.cols,  left.rows, m_bank.size() );
  m_lasagnaR.size( right.rows, right.rows, m_bank.size() );
  for( int i = 0; i < m_bank.size(); ++i )
   {
    convolve( m_lasagnaL.m_container[i], left, m_bank[i] );
    //save("layer_"+ format(i,2)+"_L.png", m_lasagnaL.m_container[i] );
    convolve( m_lasagnaR.m_container[i], right, m_bank[i] );
    //save( "layer_" + format( i, 2 ) + "_R.png", m_lasagnaR.m_container[i] );
    std::cout << i << "; ";
   }

  std::cout << "Total: " << m_bank.size() << std::endl;
 }

void StereoConvolveMatch::process( ImageType & disparity, ImageType const& left, ImageType const& right )const
 {
  int width = (int)left.cols;
  int height = (int)right.cols;
 
  m_square.init( width, height );

  extern int g_line;

  g_line = g_line % left.rows;
  if( left.rows < g_line + 8) g_line = 0;;

  //for( SizeType line=295; line <  316 ; ++line )
  //for( SizeType line= 0;  line < 75; ++line )
  //for( SizeType line=133; line <  143 ; ++line )
  //for( SizeType line= g_line; line < g_line + 8; ++line )
  for( SizeType line= 0; line <  left.rows ; ++line )
   {
    //std::cout << std::setw(6) << line << " - ";
    process_P( line, left, right );
    m_square.importL( disparity, line );
    m_square.purge();
    m_square.processL();
    m_square.disparityL();
    m_square.processR();
    m_square.disparityR();
    processB( disparity, line);
    //save( "line_" + std::to_string(line) + ".png", m_square );
    //std::cout << "|" << std::endl;;
   }
 }

void StereoConvolveMatch::process_P(  SizeType const& line, ImageType const& left, ImageType const& right )const
 {
  int width = (int)left.cols;
  int height = (int)right.cols;

  ScalarType maximum = 0;
  for( SizeType xL = 0; xL < width; ++xL )
   {
    for( SizeType xR = std::max<int>( 0, (int)xL - (int)m_square.m_range ); xR < xL; ++xR )
     //for( SizeType xR = 0; xR < height; ++xR )
     {
      auto d = distance( { xL, line }, { xR, line } );
      m_square.m_distance[xR * width + xL] = (float)d;
      maximum = std::max( maximum, d );
     }
    //if( 0 == (xL % 10) )  std::cout << ".";
  }

  //cv::Mat distanceMap( height, width, CV_64FC1, m_square.m_distance.data() );
  //distanceMap *= 255/ maximum;
  //cv::imwrite( "map" + std::to_string( line ) + ".png", distanceMap );
 }

void StereoConvolveMatch::processB( ImageType& disparity, SizeType const& line )const
 {
  m_square.disparityB();

  int width  = (int)m_lasagnaL.m_container[0].size()[0];
  int height = (int)m_lasagnaR.m_container[0].size()[0];

  for( SizeType xL = 0; xL < (SizeType)width; ++xL )
   {
    disparity.at<std::uint8_t>( (int)line, (int)xL ) = m_square.m_disparityB[xL];
   }
 }

StereoConvolveMatch::ScalarType StereoConvolveMatch::distance( Size2DType const &L, Size2DType const &R )const
 {
  ScalarType result = 0;

  //for( int i=0; i< m_lasagnaL.depth(); ++i )
  // {
  //  auto const& valueL = m_lasagnaL.m_container[i].get( L );
  //  auto const& valueR = m_lasagnaR.m_container[i].get( R );
  //  result += fabs( valueL - valueR );
  // }
  //return result / m_lasagnaL.depth();

  for( int i=0; i< m_restriction.size(); ++i )
   {
    if( m_restriction[i] < 0 ) continue;
    auto const& valueL = m_lasagnaL.m_container[m_restriction[i]].get( L );
    auto const& valueR = m_lasagnaR.m_container[m_restriction[i]].get( R );
    result += fabs( valueL - valueR );
   }
  return result / m_restriction.size();

 }

void StereoConvolveMatch::lazagna( SizeType const& width, SizeType const& height, SizeType const& depth )
 {
  m_lasagnaL.size( width, height, depth );
  m_lasagnaR.size( width, height, depth );
 }

StereoConvolveMatch::ScalarType 
StereoConvolveMatch::convolve( 
  ImageType     const& gray
 ,Integer2DType const& location
 ,FilterType    const& filter
 ,MaskType      const& mask
 )
 {
  ScalarType resut = 0;
  for( int y=0; y< filter.size()[1]; ++ y )
  {
   auto Y = y+ location[1];
   if( Y< 0 ) continue;
   if( gray.rows <= Y ) continue;
   for( int x = 0; x < filter.size()[1]; ++x )
    {
     auto X = x + location[0];
     if( X < 0 ) continue;
     if( gray.cols <= X ) continue;
     auto value = gray.at<std::uint8_t>(Y,X)/255.0;
     auto f = filter.get( { (SizeType)x, (SizeType)y } );
     auto m = mask.get( { (SizeType)x, (SizeType)y } );
     resut += f*m* value;
    }
  }

  return resut;
 }

StereoConvolveMatch::ScalarType 
StereoConvolveMatch::convolve
 ( ImageType const& image, Integer2DType const& location, FilterType const& filter )
 {
  ScalarType resut = 0;
  for( int y=0; y< filter.size()[1]; ++ y )
  {
   auto Y = y+ location[1];
   if( Y< 0 ) continue;
   if( image.rows <= Y ) continue;
   for( int x = 0; x < filter.size()[1]; ++x )
    {
     auto X = x + location[0];
     if( X < 0 ) continue;
     if( image.cols <= X ) continue;
     auto value = image.at<std::uint8_t>(Y,X)/255.0;
     auto f = filter.get( { (SizeType)x, (SizeType)y } );
     resut += f * value;
    }
  }

  return resut;
 }

void       StereoConvolveMatch::convolve( LayerType & layer, ImageType const& image, FilterType const& filter )
 {
  layer.size( { (SizeType)image.cols, (SizeType)image.rows } );
  MaskType mask; mask.size( filter.size() );
  Integer2DType offset;
  offset[0] =(int) filter.size()[0]/2;
  offset[1] =(int) filter.size()[1]/2;

  cv::Mat gray; 
  cv::cvtColor( image, gray, cv::COLOR_BGR2GRAY );
  /* */
  gray.convertTo( gray, CV_64FC1 );
  cv::Mat cvLayer(  (int)layer.size()[1], (int)layer.size()[0], CV_64FC1, layer.data() );
  cv::Mat cvFilter( (int)filter.size()[1], (int)filter.size()[0], CV_64FC1, const_cast< double*>( filter.data() ) );
  cv::filter2D( gray, cvLayer, -1, cvFilter );
  return;

  Integer2DType location;
  for( location[1]= -offset[1]; location[1] < (int)(layer.size()[1] + offset[1]); ++location[1] )
   {
    for( location[0] = -offset[0]; location[0] < (int)(layer.size()[0] + offset[0]); ++location[0] )
     {
      auto value = convolve( gray, location, filter );
      layer.set( { (SizeType)location[0]+ offset[0], (SizeType)location[1] + offset[1] }, value );
     }
   }

 }

void StereoConvolveMatch::getMask( MaskType& mask, ImageType const& image, Integer2DType const& location )
 {
  color::rgb<double> pivot;
  {
   auto X = location[0] + (int)mask.size()[0]/2;
   auto Y = location[1] + (int)mask.size()[1]/2; 
   if( X < 0 ) return;    if( image.cols <= X ) return;
   if( Y < 0 ) return;    if( image.rows <= Y ) return;
   auto const& pixelPivot = image.at<cv::Vec3b>( Y , X );

   pivot[0] = pixelPivot[2] / 255.0;
   pivot[1] = pixelPivot[1] / 255.0; 
   pivot[2] = pixelPivot[0] / 255.0;
  }

  for( int y=0; y< mask.size()[1]; ++y )
   {
    auto Y = location[1]+ y;
    for( int x=0; x < mask.size()[0]; ++x )
     {
      //mask.set( { (SizeType)x,(SizeType)y }, 1 );continue;
      mask.set( { (SizeType)x,(SizeType)y }, 0 );
      if( Y < 0 ) continue;    if( image.rows <= Y ) continue;
      auto X = location[0]+ x;
      if( X < 0 ) continue;    if( image.cols <= X ) continue;

      auto const& pixelCurrent = image.at<cv::Vec3b>( Y, X );
      color::rgb<double> colorCurrent{ pixelCurrent[2] / 255.0,pixelCurrent[1] / 255.0,pixelCurrent[0] / 255.0 };
      auto distance = ::color::operation::distance( pivot, colorCurrent );
      distance = 1.0 - 4*distance/ sqrt( 3 ); if( distance < 0 ) distance = 0;
      mask.set( { (SizeType)x,(SizeType)y}, distance );
     }
   }
 }

void  StereoConvolveMatch::convolveM( LayerType& layer, ImageType const& image, FilterType const& filter )
 {
  layer.size( { (SizeType)image.cols, (SizeType)image.rows } );
  MaskType mask; mask.size( filter.size() );
  Integer2DType offset;
  offset[0] =(int) filter.size()[0]/2;
  offset[1] =(int) filter.size()[1]/2;

  cv::Mat gray;
  cv::cvtColor( image, gray, cv::COLOR_BGR2GRAY );

  Integer2DType location;
  for( location[1]= -offset[1]; location[1] < (int)(layer.size()[1] + offset[1]); ++location[1] )
   {
    for( location[0] = -offset[0]; location[0] < (int)(layer.size()[0] + offset[0]); ++location[0] )
     {
      getMask( mask, image, location );
      auto value = convolve( gray, location, filter, mask );
      layer.set( { (SizeType)location[0]+ offset[0], (SizeType)location[1] + offset[1] }, value );
     }
   }

 }
