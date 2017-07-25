#pragma once

#include <fstream>

namespace w8
{
  template < typename T >
  class DataTable
  {
    T accumulate;
  public:
    // 
    DataTable(const istream& file, int FW, int ND)
    {
      std::fstream ins(filename, std::ios::in);
      if (!ins.is_open())
      {



      }
      else
      {



      }


    }
    // returns the mean value of the dependent coordinate
    T mean() const
    {

    }
    // returns the standard deviation of the dependent coordinates
    T sigma() const
    {

    }
    // returns the standard deviation of the dependent coordinates
    T sigma() const
    {


    }
    // returns the median value of the dependent coordinate
    T median() const
    {


    }
    // returns the slope and intercept for the data set
    void regression(T& slope, T& y_intercept) const
    {


    }

  };
}