#include "common.h"
#include <Rcpp.h>

// [[Rcpp::plugins(cpp11)]]


//' @rdname match
//'
//' @title Fuzzy matching of a text string
//'
//' @description Locate the best instance of `pattern` in the `text` near `loc` using the
//' Bitap algorithm.Returns `-1` if no match found. Assumes R's typical 1-based indexing for `loc` 
//' and the returned value.
//'
//' This algorithm makes use of the `match_distance` and `match_threshold` options to determine 
//' the match.
//'
//' Candidate matches are scored based on a) the number of spelling differences between the pattern
//' and the text and b) the distance between the candidate match and the expected location. The 
//' `match_distance` option determines the relative importance of these two metrics.
//' 
//' @param text The text to search.
//' @param pattern The pattern to search for.
//' @param loc The location to search around.
//' 
//' @return Best match index or -1.
//' 
//' @export
// [[Rcpp::export]]
int match_find(std::string const& text, std::string const& pattern, int loc = 1) {
  loc = (loc < 0) ? 0 : loc-1;
  
  int res = dmp.match_main(text, pattern, loc);
  
  // Adjust for R's 1-based indexing
  return (res == -1) ? -1 : res + 1;
}

