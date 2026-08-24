#ifndef Dh_ComputerVision_StereoMatch_Disparity_Cube_HPP
#define Dh_ComputerVision_StereoMatch_Disparity_Cube_HPP

//  S_match::S_feature::S_disparity::Cube

#include <vector>
#include "./lasagna.hpp"
#include "./square/squareb.hpp"


namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      struct Cube
       {
        public:
          typedef std::size_t                 SizeType;
          typedef double                    ScalarType;

          typedef  std::vector< SizeType >   RestrictionType;

          typedef S_match::S_feature::S_disparity::SquareBase   SquareType;

          typedef S_match::S_feature::S_disparity::Lasagna  LasagnaType;


        public:
          Cube();

          void        process( SizeType    const& y, LasagnaType const& left, LasagnaType const& right );
          void         square( SquareType & square, RestrictionType const& restriction )const;
          ScalarType distance( RestrictionType const& restriction, SizeType    const& left, SizeType    const& right )const;

        private:
          typedef std::vector< ScalarType > VectorType;
          typedef std::vector< VectorType > WallType;
          typedef std::vector< WallType > BlockType;

          BlockType m_block;
       };

     }
   }
 }


#endif
