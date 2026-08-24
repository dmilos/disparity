#ifndef Dh_ComputerVision_StereoMatch_Stacker_Chroma_HPP
#define Dh_ComputerVision_StereoMatch_Stacker_Chroma_HPP

//  S_match::S_feature::S_disparity::S_PatchM::Instance

#include "../pure.hpp"
#include "../square/squareb.hpp"
#include "../entangle/entangler.hpp"

namespace S_match
 {
  namespace S_feature
   {
    namespace S_disparity
     {

    namespace S_PatchM
     {

      class Instance
       : public S_match::S_feature::S_disparity::Pure
       {
        public:
          typedef  std::size_t SizeType;
          typedef  double ScalarType;

          typedef  std::array<std::size_t,2> Size2DType;

          typedef S_match::S_feature::S_disparity::Pure    PureType;
          typedef PureType::ImageGrayType ImageGrayType;
          typedef PureType::ImageRGBType   ImageRGBType;
          typedef PureType::ImageGrayType   ImageGrayType;

          typedef S_match::S_feature::S_disparity::SquareBase  SquareType;
          typedef S_match::S_feature::S_disparity::Entangler   EntanglerType;


        public:
          Instance();
        public:
          SizeType process( ImageGrayType  & image, ImageRGBType const& left, ImageRGBType const& right )const;

         SizeType m_span;
         ScalarType m_trash;
         ScalarType m_power;
 
        private:
          SizeType process( ImageGrayType & image, SizeType const& y, ImageRGBType const& left, ImageRGBType const& right )const;
        private:
          ScalarType distance_euclid( Size2DType const& leftC, ImageRGBType const& leftI, Size2DType const& rightC, ImageRGBType const& rightI  )const;
          ScalarType distance_L( Size2DType const& leftC, ImageRGBType const& leftI, Size2DType const& rightC, ImageRGBType const& rightI  )const;
          ScalarType distance_R( Size2DType const& leftC, ImageRGBType const& leftI, Size2DType const& rightC, ImageRGBType const& rightI  )const;

          mutable SquareType m_square;
          mutable EntanglerType m_entangler;

          mutable ImageRGBType   m_left, m_right;
          mutable bool  m_debug;
       };

       }
     }
   }
 }


#endif
