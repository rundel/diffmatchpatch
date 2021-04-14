#ifndef COMMON_H
#define COMMON_H

#include "diff_match_patch.h"

extern diff_match_patch<std::string> dmp;

typedef diff_match_patch<std::string>::Diff Diff;
typedef diff_match_patch<std::string>::Diffs Diffs;
typedef diff_match_patch<std::string>::Operation Operation;
typedef diff_match_patch<std::string>::Patches Patches;

#include <RcppCommon.h>

namespace Rcpp {
  template <> Diffs as(SEXP df);
}

#include <Rcpp.h>

Rcpp::List get_options();
void set_options(Rcpp::List opts);

#endif
