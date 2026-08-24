#include "./squareb.hpp"

#include <iostream>
#include <iomanip>

S_match::S_feature::S_disparity::SquareBase::SquareBase( )
 {
 }

bool S_match::S_feature::S_disparity::SquareBase::valid( Size2DType const& point )const
 {
  return m_table.get( point )[0];
 }

bool S_match::S_feature::S_disparity::SquareBase::set( Size2DType const& point, ScalarType const& value )
 {
  return m_table.set( point, gray_type( { value } ) );
 }

S_match::S_feature::S_disparity::SquareBase::ScalarType
S_match::S_feature::S_disparity::SquareBase::get( Size2DType const& point )const
 {
  return m_table.get( point )[0];
 }

S_match::S_feature::S_disparity::SquareBase::Size2DType const&
S_match::S_feature::S_disparity::SquareBase::resolution()const
 {
  return m_table.resolution( );
 }

bool
S_match::S_feature::S_disparity::SquareBase::resolution( Size2DType const& r )
 {
  return m_table.resolution( r );
 }

