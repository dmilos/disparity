#ifndef Dh_ComputerVision_StereoMatch_Entangler_DominoL_HPP
#define Dh_ComputerVision_StereoMatch_Entangler_DominoL_HPP

//  S_match::S_feature::S_disparity::EntanglDominoL

#include "../square/squareb.hpp"
#include "./base.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class EntanglDominoL
       : public  S_match::S_feature::S_disparity::EntangleBase
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;

          typedef S_match::S_feature::S_disparity::SquareBase   SquareType;

        public:
          EntanglDominoL();

        public:
          SizeType     global( SquareType const& square );

        private:
          SizeType  searchR( SizeType const& L, SquareType const& square, SizeType const& limitR_A, SizeType const& limitR_B )const;

       };

     }
   }
 }

#endif
