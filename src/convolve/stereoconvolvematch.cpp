#include <fstream>
#include "math/math.hpp"
#include "./stereoconvolvematch.hpp"

extern std::string format( int const& value, int w );

void make_gabor0( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;

  /*    2 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 22.5 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*    5 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 45 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
  /*    6 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 67.5 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   12 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 135 ), 0.618975, 0 );  normalize( filter ); bank.push_back( filter );
  /*   15 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 157.5 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
  /*   20 */filter.size( { (SizeType) 9, (SizeType) 9 } ); gabor( filter, math::geometry::deg2rad( 45 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   33 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 0 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
  /*   34 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 22.5 ), 0.618975, 0 );  normalize( filter ); bank.push_back( filter );
  /*   39 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 67.5 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
  /*   40 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 90 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   46 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad( 157.5 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   70 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad( 67.5 ), 0.618975, 0 );  normalize( filter ); bank.push_back( filter );
  /*  106 */filter.size( { (SizeType)19, (SizeType)19 } ); gabor( filter, math::geometry::deg2rad( 112.5 ), 0.618975, 0 ); normalize( filter );  bank.push_back( filter );
  }
void make_gabor1( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;

  Filter filter;
  /*   44 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  15 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*  100 */filter.size( { (SizeType)16, (SizeType)16 } ); gabor( filter, math::geometry::deg2rad(  30 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*    2 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad(  45 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   58 */filter.size( { (SizeType)12, (SizeType)12 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   14 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   47 */filter.size( { (SizeType)11, (SizeType)11 } ); gabor( filter, math::geometry::deg2rad(  60 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*  192 */filter.size( { (SizeType)24, (SizeType)24 } ); gabor( filter, math::geometry::deg2rad(  90 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*    6 */filter.size( { (SizeType) 7, (SizeType) 7 } ); gabor( filter, math::geometry::deg2rad( 105 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   40 */filter.size( { (SizeType)10, (SizeType)10 } ); gabor( filter, math::geometry::deg2rad( 120 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   97 */filter.size( { (SizeType)15, (SizeType)15 } ); gabor( filter, math::geometry::deg2rad( 150 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*  164 */filter.size( { (SizeType)21, (SizeType)21 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   21 */filter.size( { (SizeType) 8, (SizeType) 8 } ); gabor( filter, math::geometry::deg2rad( 165 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );


}
void make_gabor2( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
/*   94 */filter.size( { (SizeType)12, (SizeType)12 } ) ; gabor( filter, math::geometry::deg2rad( 330 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*   92 */filter.size( { (SizeType)12, (SizeType)12 } ) ; gabor( filter, math::geometry::deg2rad( 300 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*   90 */filter.size( { (SizeType)12, (SizeType)12 } ) ; gabor( filter, math::geometry::deg2rad( 270 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*   89 */filter.size( { (SizeType)12, (SizeType)12 } ) ; gabor( filter, math::geometry::deg2rad( 255 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*   87 */filter.size( { (SizeType)12, (SizeType)12 } ) ; gabor( filter, math::geometry::deg2rad( 225 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*   84 */filter.size( { (SizeType)12, (SizeType)12 } ) ; gabor( filter, math::geometry::deg2rad( 180 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*   44 */filter.size( { (SizeType) 8, (SizeType) 8 } ) ; gabor( filter, math::geometry::deg2rad( 300 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*   40 */filter.size( { (SizeType) 8, (SizeType) 8 } ) ; gabor( filter, math::geometry::deg2rad( 240 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*   18 */filter.size( { (SizeType) 6, (SizeType) 6 } ) ; gabor( filter, math::geometry::deg2rad( 270 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*   12 */filter.size( { (SizeType) 6, (SizeType) 6 } ) ; gabor( filter, math::geometry::deg2rad( 180 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );


  }
void make_gabor3( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
  /*   77 */filter.size( { (SizeType)13, (SizeType)13 } );  gabor( filter, math::geometry::deg2rad( 75 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   72 */filter.size( { (SizeType)13, (SizeType)13 } ) ; gabor( filter, math::geometry::deg2rad(   0), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   43 */filter.size( { (SizeType)10, (SizeType)10 } );  gabor( filter, math::geometry::deg2rad( 105 ), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
  /*   16 */filter.size( { (SizeType) 8, (SizeType) 8 } ) ; gabor( filter, math::geometry::deg2rad(  60), 0.618975, 0 ); normalize( filter );  bank.push_back( filter );
  /*    5 */filter.size( { (SizeType)7, (SizeType)7 } );    gabor( filter, math::geometry::deg2rad( 75 ), 0.618975, 0 ); normalize( filter );   bank.push_back( filter );
 }
void make_gabor4( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;

/*    6 */filter.size( { (SizeType) 7, (SizeType) 7 } ) ; gabor( filter, math::geometry::deg2rad(  90.0), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
/*   15 */filter.size( { (SizeType) 8, (SizeType) 8 } ) ; gabor( filter, math::geometry::deg2rad(  45.0), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
/*   22 */filter.size( { (SizeType) 8, (SizeType) 8 } ) ; gabor( filter, math::geometry::deg2rad( 150.0), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
/*   55 */filter.size( { (SizeType)11, (SizeType)11 } ) ; gabor( filter, math::geometry::deg2rad( 105.0), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
/*   62 */filter.size( { (SizeType)12, (SizeType)12 } ) ; gabor( filter, math::geometry::deg2rad(  30.0), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
/*   76 */filter.size( { (SizeType)13, (SizeType)13 } ) ; gabor( filter, math::geometry::deg2rad(  60.0), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
/*   82 */filter.size( { (SizeType)13, (SizeType)13 } ) ; gabor( filter, math::geometry::deg2rad( 150.0), 0.618975, 0 ); normalize( filter ); bank.push_back( filter );
/*  123 */filter.size( { (SizeType) 8, (SizeType) 8 } ) ; gabor( filter, math::geometry::deg2rad( 225.0 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*  129 */filter.size( { (SizeType) 8, (SizeType) 8 } ) ; gabor( filter, math::geometry::deg2rad( 315.0 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*  171 */filter.size( { (SizeType)12, (SizeType)12 } ) ; gabor( filter, math::geometry::deg2rad( 225.0 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );
/*  178 */filter.size( { (SizeType)12, (SizeType)12 } ) ; gabor( filter, math::geometry::deg2rad( 330.0 ), 0.5, math::constants::PHI / 2.0 ); normalize( filter ); bank.push_back( filter );

 }
void make_gabor5( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
 }

void make_laplace0( std::vector<Filter>  & bank )
 {
  typedef std::size_t  SizeType;
  Filter filter;
  bank.push_back( filter );
 }

typedef std::size_t SizeType;
SizeType g_count=0;
std::ofstream g_ofs( "filter-table.txt" );

void make_laplace( std::vector<Filter>& bank, SizeType const& size_begin, SizeType const& size_end  )
 {
  for( auto size = size_begin; size < size_end; size += 1 )
   {
    bank.resize( bank.size() + 1 );
    auto& filter = bank.back();
    filter.size( { (SizeType)size, (SizeType)size } );
    laplace( filter, 0.5, 0 );
    save( "filter_laplace_" + format( (int)g_count, 3 ) +"_"+ format( (int)size, 3 ) +".png", filter );
    normalize( filter );

    g_ofs << "/ * " << std::setw( 4 ) << g_count << " * /";
    g_ofs << "filter.size( { (SizeType)" << size << ", (SizeType)" << size << " } ) ; ";
    g_ofs << "laplace( filter, 0.5, 0 );" << std::endl;
    ++g_count;
   }
  std::cout << "Total: " << g_count << std::endl;
 }

void make_gabor_simetric( std::vector<Filter>  & bank, SizeType const& size_begin, SizeType const& size_end, SizeType const& rotation_total )
 {
  typedef std::size_t  SizeType;
  Filter filter;

  for( int size = (int)size_begin; size < (int)size_end; size += 1 )
  {
    for( int index = 0; index < rotation_total; ++index )
    {
      double angle = index * 180.0 / rotation_total;
      //if( 180 - 10 < angle ) continue;
      //if( angle < 10 ) continue;
      /**/

      bank.resize( bank.size() + 1 );
      auto& filterA = bank.back();
      filterA.size( { (SizeType)size, (SizeType)size } );
      gabor( filterA, math::geometry::deg2rad( angle ), 0.618975, 0 );
      save( "gabor[" + format( (int)g_count, 3 ) + "_A_" + format( size, 3 ) + "_" + format( (int)(angle), 3 ) + "].png", filterA );
      normalize( filterA );

      g_ofs << "/* " << std::setw( 4 ) << g_count << " */";
      g_ofs << "filter.size( { (SizeType)" << std::setw( 2 )<< size << ", (SizeType)" << std::setw( 2 ) << size << " } ) ; ";
      g_ofs << "gabor( filter, math::geometry::deg2rad( " << std::setw( 3 ) << angle << "), 0.618975, 0 );" << std::endl;

      ++g_count;
    }
  }
 }

void make_gabor_non_simetric( std::vector<Filter>  & bank, SizeType const& size_begin, SizeType const& size_end, SizeType const& rotation_total )
 {
  for( int size = (int)size_begin; size < (int)size_end; size += 2 )
  {
    for( int index = 0; index < rotation_total; ++index )
    {
      double angle = index * 360.0 / rotation_total;
      //if( 180 - 10 < angle ) continue;
      //if( angle < 10 ) continue;
      /**/
      bank.resize( bank.size() + 1 );
      auto& filterB = bank.back();
      filterB.size( { (SizeType)size, (SizeType)size } );
      gabor( filterB, math::geometry::deg2rad( angle ), 0.5, math::constants::PHI / 2.0 );
      save( "gabor[" + format( (int)g_count, 3 ) + "_B_" + format( size, 3 ) + "_" + format( (int)(angle), 3 ) + "].png", filterB );

      g_ofs << "/* " << std::setw( 4 ) << g_count << " */";
      g_ofs << "filter.size( { (SizeType)" << std::setw( 2 ) << size << ", (SizeType)" << std::setw( 2 ) << size << " } ) ; ";
      g_ofs << "gabor( filter, math::geometry::deg2rad( " << std::setw( 3 ) <<angle << " ), 0.5, math::constants::PHI / 2.0 );" << std::endl;

      normalize( filterB );
      ++g_count;
    }
  }
 }

StereoConvolveMatch::StereoConvolveMatch()
 {
  g_count = 0;

  //make_gabor0( m_bank );
  // make_gabor1( m_bank );
  //make_gabor2( m_bank );
  //make_gabor3( m_bank );
  make_gabor4( m_bank );  
  //make_gabor5( m_bank );
  //make_laplace0( m_bank );

 //make_laplace( m_bank, 6,65 );

  //make_gabor_simetric( m_bank, 7, 14, 12 );
  //make_gabor_non_simetric( m_bank, 6, 13, 24 );
 
/*
  make_gabor_simetric( m_bank, 7, 10, 12 );
  make_gabor_non_simetric( m_bank, 6, 11, 12 );

  make_gabor_simetric( m_bank, 10, 13, 12 );
  make_gabor_non_simetric( m_bank, 10, 15, 12 );
 
  make_gabor_simetric( m_bank, 13, 16, 12 );
  make_gabor_non_simetric( m_bank, 14, 19, 12 );
 
  make_gabor_simetric( m_bank, 16, 19, 12 );
  make_gabor_non_simetric( m_bank, 18, 23, 12 );

  make_gabor_simetric( m_bank, 19, 22, 12 );
  make_gabor_non_simetric( m_bank, 22, 27, 12 );

  make_gabor_simetric( m_bank, 21, 25, 12 );
  make_gabor_non_simetric( m_bank, 26, 31, 12 );
  */
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

  //for( SizeType line=150; line <  170 ; ++line )
  //for( SizeType line=0; line <  150 ; ++line )
  //for( SizeType line=200; line <  270 ; ++line )
  //for( SizeType line=0; line <  100 ; ++line )
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
    for( SizeType xR = std::max<int>( 0, (int)xL - 100 ); xR < xL; ++xR )
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
