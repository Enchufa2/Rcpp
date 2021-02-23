// do_call.h: Rcpp R/C++ interface class library -- do_call
//
// Copyright (C) 2021 Iñaki Ucar
//
// This file is part of Rcpp.
//
// Rcpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp.  If not, see <http://www.gnu.org/licenses/>.

#ifndef Rcpp__sugar__do_call_h
#define Rcpp__sugar__do_call_h

namespace Rcpp {
namespace sugar {

template <bool NA, typename T, typename Function>
class DoCall {
public:
    typedef Rcpp::VectorBase<VECSXP,NA,T> LIST;

    DoCall(Function fun_, const LIST& args_, SEXP env_)
        : fun(fun_), args(args_), env(env_) {}

    inline SEXP get() const {
        SEXP arglist = R_NilValue;
        for (int i = args.size() - 1; i >= 0; i--) {
            arglist = Rf_cons(args[i], arglist);
        }
        return fun.invoke(arglist, env);
    }

private:
    Function fun;
    const LIST& args;
    SEXP env;

};

} // sugar

template <bool NA, typename T, typename Function>
SEXP do_call(Function fun, const Rcpp::VectorBase<VECSXP,NA,T>& args, SEXP env = R_GlobalEnv){
    return sugar::DoCall<NA,T,Function>(fun, args, env).get();
}

} // Rcpp

#endif
