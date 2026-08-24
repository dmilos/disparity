#include "./bsfs.hpp"

#define PREFIX   __FUNCTION__ + std::string( "(" ) + std::to_string(__LINE__ ) + "):"

S_match::S_feature::S_disparity::EntangleBSFS::EntangleBSFS()
 {
  m_debug = false;
  m_coefficient = 10;
  m_occlusion  = 0.5;
 }


S_match::S_feature::S_disparity::EntangleBSFS::SizeType 
S_match::S_feature::S_disparity::EntangleBSFS::global( SquareType const& square )
 {
  SizeType result = 0;
  SizeType width  = square.resolution()[0]; m_bestL.resize( width  ); std::fill( m_bestL.begin(), m_bestL.end(), width  );
  SizeType height = square.resolution()[1]; m_bestR.resize( height ); std::fill( m_bestR.begin(), m_bestR.end(), height );

  m_cost.resize( width + 1 );
  for (int i = 0; i < width+1; i++)
   {
    m_cost[i].resize( width + 1 );
   }

   {
    ScalarType the_max = 0;
    m_cost[0][0] = 0.0;
    for (SizeType i = 1; i < width+1; i++)
     {
      m_cost[i][0] = i * m_occlusion;
      m_cost[0][i] = i * m_occlusion;
     }
    for ( SizeType i = 1; i < width + 1; i++)
     {
      for ( SizeType j = 1; j < width + 1; j++)
       {
        ScalarType no_occlusion = m_cost[i - 1][j - 1] + m_coefficient * square.get( { i - 1, j - 1 } );
        ScalarType i_occlusion = m_cost[i - 1][j] + m_occlusion;
        ScalarType j_occlusion = m_cost[i][j - 1] + m_occlusion;
        m_cost[i][j] = min( no_occlusion, i_occlusion, j_occlusion );
        the_max = std::max( the_max, m_cost[i][j] );
       }
     }

    SizeType i = width, j = width;
    ScalarType cost_val = m_cost[width][width];

    //if(false)
    //{
    // cv::Mat cost_mat( width+1, width+1, CV_8UC1);
    // for (int i = 0; i < width + 1; i++)
    //   for (int j = 0; j < width + 1; j++)
    //     {
    //      cost_mat.at<uchar>( i, j ) = (uchar)( 255 * ( m_cost[i][j]/the_max ) );
    //     }
    // cv::imwrite( ("cost-"  + std::to_string( line ) + ".png" ).c_str(), cost_mat );
    //}

    while( (i > 0) && (j > 0) )
     {
      if( m_cost[i][j] == m_cost[i - 1][j] + m_occlusion)
       {
        m_bestL[ i - 1 ]  = width;
         --i;
       }
      else
       {
        if( m_cost[i][j] == m_cost[i][j - 1] + m_occlusion)
         {
          --j;
         }
        else
         {
          ++result;
          auto d =  j - i;
           m_bestL[ i - 1 ]  = i - 1 - d;
           m_bestR[ m_bestL[ i - 1 ] ]  = i - 1;
          cost_val -= m_coefficient * square.get( { i - 1, j - 1 } );
          --i;
          --j;
         }
       }
     }
   }
  return result;
 }
