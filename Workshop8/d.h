#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <algorithm>

using namespace std;

namespace w8 {
  template<class T>
  class DataTable {
    vector<T> x, y;
    int m_width;
    int m_decimals;
  public:
    DataTable(ifstream& is, int w, int d) {
      m_width = w;
      m_decimals = d;
      while (is.good()) {
        string l;
        getline(is, l);
        stringstream strs;
        if (!l.empty()) {
          strs.str(l);
          T fx, fy;
          strs >> fx >> fy;
          x.push_back(fx);
          y.push_back(fy);
        }
      }
    }
    T mean()const { //- returns the mean value of the dependent coordinate
      T yTot;
      yTot = accumulate(y.begin(), y.end(), 0.0);
      return yTot / y.size();
    }

    T sigma() const { //- returns the standard deviation of the dependent coordinates
      T meanV = mean(), sumDev = 0.0;
      for (int i = 0; i<y.size(); ++i)
        sumDev += (y[i] - meanV)*(y[i] - meanV);



      return sqrt(sumDev / y.size());
    }

    T median() const { //- returns the median value of the dependent coordinate
      vector<T> cpy = y;
      sort(cpy.begin(), cpy.end());
      T med = cpy[cpy.size() / 2];
      return med;
    }

    void regression(T& slope, T& y_intercept) const { //- returns the slope and intercept for the data set
      T avgX;
      T avgY;
      avgX = accumulate(x.begin(), x.end(), 0.0) / x.size();
      avgY = accumulate(y.begin(), y.end(), 0.0) / y.size();
      T num = 0.0, denom = 0.0;
      for (int i = 0; i < x.size(); ++i) {
        num += (x[i] - avgX)*(y[i] - avgY);
        denom += (x[i] - avgX)*(x[i] - avgX);
      }
      cout << "test:::::-->" << accumulate(x.begin(), x.end(), 0.0) << "<---" << endl;
      cout << "test:::::-->" << x.size() << "<---" << endl;
      cout << "test:::::-->" << avgX << "<---" << endl;
      cout << "test:::::-->" << avgY << "<---" << endl;


      slope = num / denom;
      y_intercept = avgY - (slope*avgX);
    }

    void display(ostream& os) const { //- displays the data pairs as shown below
      os << setw(m_width) << "x" << setw(m_width) << "y" << endl;
      for (int i = 0; i < x.size(); i++)
        os << setw(m_width) << fixed << setprecision(m_decimals) << x[i] << setw(m_width) << fixed << setprecision(m_decimals) << y[i] << endl;
    }
  };
  template<class T>
  ostream& operator<<(ostream& os, const DataTable<T>& dt) {
    dt.display(os);
    return os;
  }
}
