#ifndef Dh_ComputerVision_StereoMatch_EntangleBase_HPP
#define Dh_ComputerVision_StereoMatch_EntangleBase_HPP

//  S_match::S_feature::S_disparity::EntangleBase

#include "graphics/image/image.hpp"
#include "../square/squareb.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

      class EntangleBase
       {
        public:
          typedef double ScalarType;
          typedef std::size_t SizeType;

          typedef std::vector<SizeType>  NearestType;

          typedef S_match::S_feature::S_disparity::SquareBase   SquareType;

        public:
          EntangleBase();

        public:
          virtual SizeType     global( SquareType const& square )=0;

        public:
           SizeType width( )const{ return m_bestR.size();  }
           SizeType height( )const{ return m_bestL.size();  }

        public:
          //NearestType const& bestL( )const;
          //NearestType const& bestR( )const;

        public:
          bool     connect( SizeType const& L, SizeType const& R ); //!< 2-dim

          bool     tie( SizeType const& L, SizeType const& R )const; //!< 2-dim
          bool     tieL( SizeType const& L )const;              //!< 2-dim
          bool     tieR( SizeType const& R )const;              //!< 2-dim

          bool   untieL( SizeType const& L );                   //!< 2-dim
          bool   untieR( SizeType const& R );                   //!< 2-dim
                                                                //!< 2-dim
          SizeType getR( SizeType const& L )const;  //!< 1-dim
          SizeType getL( SizeType const& R )const;  //!< 1-dim
          bool   spoilR( SizeType const& L );       //!< 1-dim
          bool   spoilL( SizeType const& R );       //!< 1-dim
          bool   checkR( SizeType const& L )const;  //!< 1-dim
          bool   checkL( SizeType const& R )const;  //!< 1-dim

          bool   validL( SizeType const& L )const;  //!< 0-dim
          bool   validR( SizeType const& R )const;  //!< 0-dim

          SizeType   badL( )const;  //!< 0-dim
          SizeType   badR( )const;  //!< 0-dim
        public:
          SizeType purge();

          SizeType limitL( SizeType const& R )const;
          SizeType limitR( SizeType const& L )const;

          NearestType m_bestL;
          NearestType m_bestR;
          ScalarType m_maxR;
          ScalarType m_maxL;
        };

     }
   }
 }


#endif
