#include "common.h"

// [[Rcpp::plugins(cpp11)]]


//' @rdname match
//'
//' @description Locate the best instance of `pattern` in the `text` near `loc` using the
//' Bitap algorithm.Returns `-1` if no match found. Assumes R's typical 1-based indexing for `loc` 
//' and the returned value.
//'
//' This algorithm makes use of the `match_distance` and `match_threshold` options to determine 
//' the match. If these values are not set explicitly via the `threshold` and `distance` arguments - 
//' their value will use the currently set global option value.
//'
//' Candidate matches are scored based on: 
//' a) the number of spelling differences between the pattern and the text and 
//' b) the distance between the candidate match and the expected location. 
//' 
//' The `match_distance` option determines the relative importance of these two metrics.
//' 
//' @param text The text to search.
//' @param pattern The pattern to search for.
//' @param loc The expected location of the pattern.
//' @param threshold Threshold for determining a match (0 - perfect match, 1 - very loose).
//' @param distance Distance from expected location scaling for score penalty.
//' 
//' @return Index of best match or -1 for no match.
//' 
//' @export
// [[Rcpp::export]]
int match_find(std::string const& text, std::string const& pattern, int loc = 1, 
               SEXP threshold = R_NilValue, SEXP distance = R_NilValue) {
  
  Rcpp::List prev_opts = get_options();
  
  dmp.Match_Threshold = (threshold == R_NilValue) ? dmp.Match_Threshold : Rcpp::as<double>(threshold);
  dmp.Match_Distance = (distance == R_NilValue) ? dmp.Match_Distance : Rcpp::as<int>(distance);

  loc = (loc < 0) ? 0 : loc-1;
  
  int res = dmp.match_main(text, pattern, loc);
  
  set_options(prev_opts);
  
  // Adjust for R's 1-based indexing
  return (res == -1) ? -1 : res + 1;
}

