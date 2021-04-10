#include <Rcpp.h>
#include "common.h"

// [[Rcpp::plugins(cpp11)]]


//' @rdname patch
//' 
//' @title Create and apply patches to a text string
//'
//' @description `patch_make()` computes a list of patches to turn the source string (`x`) into the
//' destination string (`y`).
//'
//' @param x The source string
//' @param y The destination string
//' 
//' @return `patch_make()` returns a string representation of the patch(es).
//'
//' @export
// [[Rcpp::export]]
std::string patch_make(std::string const& x, std::string const& y) {
  return dmp.patch_toText(dmp.patch_make(x, y));
}


//' @rdname patch
//'
//' @description `patch_apply()` applies the `patch` to `x`.
//'
//' @param patch A string representation of the patch(es).
//'
//' @return `patch_apply()` returns the patched version of the string x, the `matches` attribute 
//' contains logical values indicating which patches were successfully applied.
//'
//' @export
// [[Rcpp::export]]
Rcpp::CharacterVector patch_apply(std::string const& x, std::string const& patch) {
  auto out = dmp.patch_apply(dmp.patch_fromText(patch), x);
  
  Rcpp::CharacterVector res(out.first);
  res.attr("matches") = out.second;
  
  return res;
}

