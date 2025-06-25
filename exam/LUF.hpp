#ifndef __LUF_H__
#define __LUF_H__

#include "../homework/includes/matrix.hpp"

namespace pp {

    class LUF{
        private:
        pp::matrix L,U, A_C;
        pp::vector P;

        public:
        LUF(const pp::matrix& A);
        pp::vector solve(const pp::vector& b);
        double det();
        pp::matrix inverse();

        pp::matrix getL();
        pp::matrix getU();
        pp::vector getP();
        pp::matrix getApivoted();
    }; // LUF




}  //namespace pp


#endif // __LUF_H__