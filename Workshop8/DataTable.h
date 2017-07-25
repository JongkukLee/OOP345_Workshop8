#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

namespace w8
{
  template < typename T >
  class DataTable
  {
	  std::vector<T> dataTableX;
	  std::vector<T> dataTableY;
    T accumulateX;
	T accumulateY;
  public:
	DataTable() {};
    // 
    DataTable(std::ifstream& ins, int FW, int ND )
    {
      //std::fstream ins(file, std::ios::in);

	  if (!ins.is_open())
		  std::cerr << "This file cannot be open!" << std::endl;
	  else
	  {
		  std::cout << "This file is open!" << std::endl;
		  std::string line;

		  while (std::getline(ins, line))
		  {
			  std::cout << "Line -->" << line << "<--" << std::endl;
			  unsigned int idx = line.find(' ');
			  dataTableX.push_back(std::stof(line.substr(0, idx)));
			  std::cout << "x-values:[" << std::stof(line.substr(0, idx)) << "]";
			  dataTableY.push_back(std::stof(line.substr(idx)));
			  std::cout << "y-values:[" << std::stof(line.substr(idx)) << "]\n";
		  }
		  accumulateX = static_cast<T>(std::accumulate(dataTableX.begin(), dataTableX.end(), 0));
		  accumulateY = static_cast<T>(std::accumulate(dataTableY.begin(), dataTableY.end(), 0));

		  std::cout << "AccumulateX:[" << accumulateX << ", " << accumulateY << "]\n";

	  }
    }
    // returns the mean value of the dependent coordinate
    T mean() const
    {
		return accumulateY / dataTableY.size();
    }
    // returns the standard deviation of the dependent coordinates
    T sigma() const
    {
		T mean  = this->mean();
		return std::sqrt(accumulateY / dataTableY.size() - mean * mean);
    }
    // returns the median value of the dependent coordinate
    T median() const
    {
		size_t n = dataTableY.size() / 2;
		//nth_element(dataTableY.begin(), dataTableY.begin() + dataTableY, dataTableY.end());
		return dataTableY[n];
    }
    // returns the slope and intercept for the data set
    void regression(T& slope, T& y_intercept) const
    {
		slope = static_cast<T>(std::inner_product(dataTableX.begin(), dataTableX.end(), dataTableX.begin(), 0));
		y_intercept = static_cast<T>(std::inner_product(dataTableY.begin(), dataTableY.end(), dataTableY.begin(), 0));
    }
	// Displays the data pairs as shown below
	void display(std::ostream& os) const
	{

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

