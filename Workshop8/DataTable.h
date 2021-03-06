// OOP345 Workshop 8: STL Algorithms
// File DataTable.h
// Version 1.0
// Date 2017-07-21
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//      copy data from a file into a sequential container
//    accumulate data values using the STL's numeric library
//    specify an operation on each value in a data set using a lambda expression
//    sort the data values in a data set using the STL's algorithm
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
//
///////////////////////////////////////////////////////////
#ifndef DATATABLE_H
#define DATATABLE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iomanip>
#define VERBOSE 0

namespace w8
{
  template < typename T >
  class DataTable
  {
    int m_fw;
    int m_nd;
    std::vector<T> dataTableX;
    std::vector<T> dataTableY;
    T accumulateX;
    T accumulateY;
  public:
    // default parameter constructor
    DataTable() {};
    // three parameters constructor
    DataTable(std::ifstream& ins, int FW, int ND) : m_fw(FW), m_nd(ND)
    {
      if (!ins.is_open())
        std::cerr << "This file cannot be open!" << std::endl;
      else
      {
        if(VERBOSE) std::cout << "This file is open!" << std::endl;
        std::string line;

        while (std::getline(ins, line))
        {
          if (VERBOSE) std::cout << "Line -->" << line << "<--" << std::endl;
          std::stringstream strs;
          if (!line.empty()) {
            strs.str(line);
            T valueX, valueY;
            strs >> valueX >> valueY;
            dataTableX.push_back(valueX);
            if (VERBOSE) std::cout << "x-values:[" << valueX << "]";
            dataTableY.push_back(valueY);
            if (VERBOSE) std::cout << "y-values:[" << valueY << "]\n";
          }
        }
        accumulateX = std::accumulate(dataTableX.begin(), dataTableX.end(), 0.0);
        accumulateY = std::accumulate(dataTableY.begin(), dataTableY.end(), 0.0);

        if (VERBOSE) std::cout << "AccumulateX:[" << accumulateX << ", " << accumulateY << "]\n";
      }

      // close the stream
      ins.close();
    }
    // returns the mean value of the dependent coordinate
    T mean() const
    {
      return accumulateY / dataTableY.size();
    }
    // returns the standard deviation of the dependent coordinates
    T sigma() const
    {
      T mean = this->mean();
      double sq_sum = std::inner_product(dataTableY.begin(), dataTableY.end(), dataTableY.begin(), 0.0);
      return std::sqrt(sq_sum / dataTableY.size() - mean * mean);
    }
    // returns the median value of the dependent coordinate
    T median() const
    {
      std::vector<T> cpy = dataTableY;
      size_t n = dataTableY.size() / 2;
      std::sort(cpy.begin(), cpy.end());
      return cpy[n];
    }
    // returns the slope and intercept for the data set
    void regression(T& slope, T& y_intercept) const
    {
      T meanX = accumulateX / dataTableX.size();
      T meanY = this->mean();;

      T variance = 0.0, covariance = 0.0;
      for (size_t i = 0; i < dataTableX.size(); ++i) {
        variance += (dataTableX[i] - meanX)*(dataTableY[i] - meanY);
        covariance += (dataTableX[i] - meanX)*(dataTableX[i] - meanX);
      }
      slope = variance / covariance;
      y_intercept = this->mean() - (slope*accumulateX/dataTableX.size());
    }
    // Displays the data pairs as shown below
    void display(std::ostream& os) const
    {
      os << std::setw(m_fw) << "x";
      os << std::setw(m_fw) << "y" << std::endl;
      for (size_t i = 0; i < dataTableX.size(); i++)
        os << std::setw(m_fw) << std::fixed << std::setprecision(m_nd) << dataTableX[i] << 
              std::setw(m_fw) << std::fixed << std::setprecision(m_nd) << dataTableY[i] << std::endl;
    }
  };
  // displays a single line 
  template <typename T>
  std::ostream& operator<<(std::ostream& os, const DataTable<T>& data)
  {
    data.display(os);
    return os;
  }
}
#endif
