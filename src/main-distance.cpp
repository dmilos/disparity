#include <iostream>
#include <fstream>
#include <cstddef>
#include <iomanip>
#include <vector>
#include <array>
#include <numeric>
#include <filesystem>
#include <algorithm>
#include <random>
#include <math/math.hpp>
#include <color/color.hpp>
#include <opencv2/opencv.hpp>

#include "./convolve/filter.hpp"


typedef ::color::rgb<std::uint8_t> ColorType;
typedef ::math::linear::vector::structure<std::size_t, 2> Size2dType;
typedef ::math::linear::vector::structure<double, 2> Point2dType;
typedef ::math::linear::vector::structure<double, 3> Point3dType;


std::vector<std::string> g_name;
typedef std::vector<Filter> BankType;
BankType g_bank;



void make_gabor( Filter& filter, double const angle, double const& frequency, double const& shift, std::array<double, 2> const& press  )
 {
  gabor( filter, angle, frequency,  shift,  press );
  normalize( filter );
 }

void make_gabor_symetric( BankType& bank, Size2dType const& size, double const &angle_step, std::array<double, 2> const& press )
 {
  for( double angle = 0; angle < math::constants::PHI_double ; angle += angle_step )
   {
    bank.resize( bank.size() + 1 );
    bank.back().size( size );
    make_gabor( bank.back(), angle, 0.500000, math::constants::PHI / 2.0, press );
    {
     std::stringstream ss;
     ss << "gabor( " ;
     ss << "{" << std::setw(4) << size[0] << "," << std::setw(4) <<size[1] << " }" << ", ";
     ss << " math::geometry::deg2rad( " << std::setw(5) << math::geometry::rad2deg( angle ) << " ), ";
     ss << std::setw(8) << 0.500000 << ", ";
     ss << " math::geometry::deg2rad( " << std::setw(5) << math::geometry::rad2deg( math::constants::PHI / 2.0 ) << " ), ";
     ss << "{" << std::setw(4) <<press[0] << ", " << std::setw(4) <<press[1] << " } " ;
     ss << " );/*s*/" ;
     g_name.push_back( ss.str() );
    }

    {
     std::stringstream ss;
     ss<< "img/gabor-non-symetric" 
       << std::setw( 4 ) << std::setfill( '0' ) << (int)math::geometry::rad2deg( angle ) << "_"
       << std::setw( 4 ) << std::setfill( '0' ) << size[0]
       << ".png";
     save( ss.str(), bank.back() );
    }
   }
 }

void make_gabor_non_symetric( BankType& bank, Size2dType const& size, double const &angle_step,  std::array<double, 2> const& press )
 {
  for( double angle = 0; angle < math::constants::PHI; angle += angle_step )
   {
    bank.resize( bank.size() + 1 );
    bank.back().size( size );
    make_gabor( bank.back(), angle, 0.618975, 0.0, press );
    {
     std::stringstream ss;
     ss << "gabor( " ;
     ss << "{" << std::setw(4) << size[0] << "," << std::setw(4) <<size[1] << " }" << ", ";
     ss << " math::geometry::deg2rad( " << std::setw(5) << math::geometry::rad2deg( angle ) << " ), ";
     ss << std::setw(8) << 0.618975 << ", ";
     ss << " math::geometry::deg2rad( " << std::setw(5) << math::geometry::rad2deg( 0.0 ) << " ), ";
     ss << "{" << std::setw(4) <<press[0] << ", " << std::setw(4) <<press[1] << " } " ;
     ss << " );/*!*/" ;
     g_name.push_back( ss.str() );
    }

    {
     std::stringstream ss;
     ss<< "img/gabor-symetric_"
       << std::setw( 4 ) << std::setfill( '0' ) << (int)math::geometry::rad2deg( angle ) << "_"
       << std::setw( 4 ) << std::setfill( '0' ) << size[0]
       << ".png";
     save( ss.str(), bank.back() );
    }
   }
 }

 void make_bank( BankType& bank, Size2dType const& size, double const& angle_step, std::array<double, 2> const& press )
 {
  make_gabor_symetric( bank, size, angle_step, press );
  make_gabor_non_symetric( bank, size, angle_step, press );
 }

 double distance_difference( Filter& temp, Filter const& left, Filter const& right, bool const& ABS  )
 {
  difference( temp, left, right );
  if( true == ABS )  absolute( temp );
  return summae( temp );
 }

 double distance_addition( Filter& temp, Filter const& left, Filter const& right, bool const& ABS )
 {
  addition( temp, left, right );
  if( true == ABS )  absolute( temp );
  return summae( temp );
 }

double evaluate_minimum( BankType const& bank, Filter  & temp, std::vector<int> const& subset )
 {
  double result = 1000000;
  for( int i=0; i< subset.size(); i++ )
   {
    for( int j = i+1; j < subset.size(); j++ )
     {
      auto A = distance_addition  ( temp, g_bank[subset[i]], g_bank[subset[j]], true );
      auto D = distance_difference( temp, g_bank[subset[i]], g_bank[subset[j]], true );

      auto current = std::min( A, D );
      if( current < result )
       {
        result = current;
       }
     }
   }
  return result;
 }

 double evaluate_average( BankType const& bank, Filter  & temp, std::vector<int> const& subset )
 {
  double result = 0;
  for( int i=0; i< subset.size(); i++ )
   {
    for( int j = i+1; j < subset.size(); j++ )
     {
      auto A = distance_addition  ( temp, g_bank[subset[i]], g_bank[subset[j]], true );
      auto D = distance_difference( temp, g_bank[subset[i]], g_bank[subset[j]], true );

      auto current = std::min( A, D );
      result += current;
     }
   }
  return result;
 }

 void elevate( BankType & bank )
 {
  Filter::Size2DType size = bank[0].size();

  for( auto const& filter: bank )
   {
    if( size[0] < filter.size()[0] )
     {
      size = filter.size();
     }
   }
  
  Filter temp;
  for( auto & filter: bank )
   {
    if( size == filter.size() )
     {
      continue;
     }
    frame( temp, filter,   (size[0] - filter.size()[0])/2  );
    filter = temp;
   }

 }

void make_main_bank( )
 {
  make_bank( g_bank, {  9,  9 }, 15.0 * math::constants::PHI_double / 360.0, { 1,1 } );
  make_bank( g_bank, {  9,  9 }, 15.0 * math::constants::PHI_double / 360.0, { 1,2 } );
  make_bank( g_bank, {  9,  9 }, 15.0 * math::constants::PHI_double / 360.0, { 1,3 } );
  make_bank( g_bank, {  9,  9 }, 15.0 * math::constants::PHI_double / 360.0, { 3,1 } );
  make_bank( g_bank, {  9,  9 }, 15.0 * math::constants::PHI_double / 360.0, { 3,1 } );

  make_bank( g_bank, { 11, 11 }, 15.0 * math::constants::PHI_double / 360.0, { 1,1 } );
  make_bank( g_bank, { 11, 11 }, 15.0 * math::constants::PHI_double / 360.0, { 1,2 } );
  make_bank( g_bank, { 11, 11 }, 15.0 * math::constants::PHI_double / 360.0, { 1,3 } );
  make_bank( g_bank, { 11, 11 }, 15.0 * math::constants::PHI_double / 360.0, { 3,1 } );
  make_bank( g_bank, { 11, 11 }, 15.0 * math::constants::PHI_double / 360.0, { 3,1 } );

  make_bank( g_bank, { 13, 13 }, 15.0 * math::constants::PHI_double / 360.0, { 1,1 } );
  make_bank( g_bank, { 13, 13 }, 15.0 * math::constants::PHI_double / 360.0, { 1,2 } );
  make_bank( g_bank, { 13, 13 }, 15.0 * math::constants::PHI_double / 360.0, { 1,3 } );
  make_bank( g_bank, { 13, 13 }, 15.0 * math::constants::PHI_double / 360.0, { 2,1 } );
  make_bank( g_bank, { 13, 13 }, 15.0 * math::constants::PHI_double / 360.0, { 3,1 } );

  make_bank( g_bank, { 15, 15 }, 15.0 * math::constants::PHI_double / 360.0, { 1,1 } );
  make_bank( g_bank, { 15, 15 }, 15.0 * math::constants::PHI_double / 360.0, { 1,2 } );
  make_bank( g_bank, { 15, 15 }, 15.0 * math::constants::PHI_double / 360.0, { 1,3 } );
  make_bank( g_bank, { 15, 15 }, 15.0 * math::constants::PHI_double / 360.0, { 2,1 } );
  make_bank( g_bank, { 15, 15 }, 15.0 * math::constants::PHI_double / 360.0, { 3,1 } );
 
  //make_bank( g_bank, { 17, 17 }, 15.0 * math::constants::PHI_double / 360.0, { 1,1 } );
  //make_bank( g_bank, { 17, 17 }, 15.0 * math::constants::PHI_double / 360.0, { 1,2 } );
  //make_bank( g_bank, { 17, 17 }, 15.0 * math::constants::PHI_double / 360.0, { 1,3 } );
  //make_bank( g_bank, { 17, 17 }, 15.0 * math::constants::PHI_double / 360.0, { 2,1 } );
  //make_bank( g_bank, { 17, 17 }, 15.0 * math::constants::PHI_double / 360.0, { 3,1 } );

  //make_bank( g_bank, { 19, 19 }, 1.0 * math::constants::PHI_double / 360.0, { 1,1 } );
  elevate( g_bank );
   std::cout << "Total: " << g_bank.size() << std::endl;

}

int main_partial( int argc, char* argv[] )
 {
  int total = 15;
  int sublen = 2;

  make_main_bank();

  std::vector<int> subset;
  subset.resize( total );
  for( int index = 0; index < subset.size(); ++index )
   {
    subset[index] = ((int)subset.size() - 1) - index;
   }

  std::vector<int> podset; 

  Filter temp;
  int counter=0;
  double maximum = 0;

  while( true )
   {
    podset.resize( sublen, -1 );
    bool winner_big = false;
    for( int pivot=0; pivot <= subset.size()- podset.size(); pivot++ )
     {

      for( int index = 0; index < podset.size(); ++index )
       {
        podset[ index ] = subset[pivot + index];
        subset[pivot+index] = ((int)podset.size() -1) - index;
       }

      bool winner_mini = false;
      while( true == math::algorithm::next_combination<int>( subset.begin()+pivot, subset.begin() + pivot + podset.size(), (int)g_bank.size(), 1 ) )
       {
        auto current = evaluate_average( g_bank, temp, subset );
        if( maximum < current )
         {
          winner_big = true;
          maximum = current;
          std::cout << std::setprecision( 12 ) << maximum << std::endl;
          for( auto index : subset )
           {
            std::cout << "    /*" << std::setw( 6 ) << index << ". */ " << g_name[index] << "; " << std::endl;
           }
          podset.assign( subset.begin() + pivot, subset.begin() + pivot + podset.size() );
         }
        ++counter;
        if( 0 == (counter % 1000000) )
         {
          std::cout << "{ ";
          for( auto index : subset )
           {
            std::cout << std::setw( 5 ) << index << "; ";
           }
          std::cout << "} " << std::endl;
         }
       }
     
      for( int index = 0; index < podset.size(); ++index )
        {
         subset[pivot + index ] = podset[index];
        }
     }
    std::cout << "*" << std::endl;
    if( false == winner_big )
     {
      //++sublen;   
      std::cout << "++" << std::endl;
      std::shuffle( subset.begin(), subset.end(), std::mt19937{ std::random_device{}() } );  
     }
     if( total  < sublen  )
      {
       std::cout << "DONE" << std::endl;
       break;
      }
   }
  return 0;
 }

int main_total( int argc, char* argv[] )
 {
  make_main_bank( );

  Filter temp;
  std::vector<int> subset;
  subset.resize(3);
  int counter = 0;

  double grand = 1;

  for( int index = 0; index < subset.size(); ++index )
   {
    subset[index] = ((int)subset.size() -1) - index;
    grand *= (g_bank.size() - index)/(index+1.0);
   }
  std::cout << "grand: " << std::fixed << grand << std::endl;
  auto B = std::chrono::high_resolution_clock::now();

  double maximum = 0;
   do{
    auto current = evaluate_minimum( g_bank, temp, subset );
    if( maximum < current )
     {
      maximum = current;
      std::cout << std::setprecision( 12 ) << maximum << std::endl;
      for( auto index : subset )
       {
        std::cout << "    /*"<< std::setw( 6 ) << index << ". */ "<< g_name[ index ] <<"; "<< std::endl;
       }
     }
     ++counter;
     if( 0 == (counter%1000000 ) )
      {
       std::cout << std::setw( 9 ) << counter  << ". { ";
       for( auto index : subset )
       {
        std::cout << std::setw( 5 ) << index << "; ";
       }
       std::cout << "} "  ;
       auto C = std::chrono::high_resolution_clock::now();
       std::cout << "Time: " <<  std::chrono::duration<double>( C-B ).count()   << "sec; ";
       std::cout << "ETA: "  << grand * (std::chrono::duration<double>( C-B ).count() / counter) / ( 60.0*60.0 ) << " H; ";
       std::cout  << std::endl;
      }
   }  while( true == math::algorithm::next_combination<int>( subset.begin(), std::end( subset ), (int)g_bank.size(), 1 ) );

  auto E = std::chrono::high_resolution_clock::now();

  std::cout << "Grand Time: " << std::chrono::duration<double>( E-B ).count()  << std::endl;

  return 0;
 }

