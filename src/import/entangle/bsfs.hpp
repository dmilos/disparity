#ifndef Dh_ComputerVision_StereoMatch_EntangleBSFS_HPP
#define Dh_ComputerVision_StereoMatch_EntangleBSFS_HPP

//  S_match::S_feature::S_disparity::BSFS

#include "../square/squareb.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class EntangleBSFS
       {
        public:
          typedef std::size_t SizeType;
          typedef double ScalarType;
          typedef std::array<std::size_t,2> Size2DType;
          typedef ::color::gray<ScalarType> gray_type;

          typedef S_match::S_feature::S_disparity::SquareBase   SquareType;
          typedef std::vector<SizeType>  NearestType;


        public:
          EntangleBSFS();

        public:
          SizeType     global( SquareType const& square );

        private:
          mutable std::vector< std::vector< double> > m_cost;
          double m_occlusion;
          double m_coefficient;

 

        public:
          bool m_debug;
        private:
          ScalarType distance( SizeType const& line, SizeType const& L, SizeType const& R )const;
          static ScalarType min( ScalarType a, ScalarType b, ScalarType c );
          static ScalarType sqr( ScalarType a );
        private:
          NearestType m_bestL;
          NearestType m_bestR;

       };

     }
   }
 }


#endif
