#ifndef FILTER_H
#define FILTER_H

//#include <SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h>


//namespace Filters {
//    template<typename type>
//    type param1;
//    template<typename type>
//    type param2;
//    template<typename type>
//    type filteredValue;

//    template<typename type>
//    type firstOrder(type value2Filter) {
//        filteredValue = (param1/param2)*(value2Filter - filteredValue);
//        return filteredValue;
//    }

//    template<typename type>
//    type simpLowPass(LinAlg::Matrix<type> value2Filter) {
//        return value2Filter+
//    }

//    double simplp (double *x, double *y, double xm1)
//    {
//      int n;
//      y[0] = x[0] + xm1;
//      for (n=1; n < M ; n++) {
//        y[n] =  x[n]  + x[n-1];
//      }
//      return x[M-1];
//    }
//}

template<typename type>
class Filter {

public:
    Filter() {
        param1 = 0.0001;
        param2 = 0.1;
    }

    ~Filter();
    type param1, param2, filteredValue;

    //template<typename type>
    type firstOrder(type value2Filter) {
        filteredValue = (param1/param2)*(value2Filter - filteredValue);
        return filteredValue;
    }

    type accel2Vel(type accelValue, double t){return accelValue/t;}
    type vel2Pos(type velValue, double t){return velValue/t;}

};

#endif // FILTER_H
