#include <Rcpp.h>
#include "common.h"

// [[Rcpp::plugins(cpp11)]]

diff_match_patch<std::string> dmp;

// [[Rcpp::export]]
Rcpp::List get_options() {
  return Rcpp::List::create(
    Rcpp::Named("diff_timeout")           = dmp.Diff_Timeout,
    Rcpp::Named("diff_edit_cost")         = dmp.Diff_EditCost,
    Rcpp::Named("match_threshold")        = dmp.Match_Threshold,
    Rcpp::Named("match_distance")         = dmp.Match_Distance,
    Rcpp::Named("patch_delete_threshold") = dmp.Patch_DeleteThreshold,
    Rcpp::Named("patch_margin")           = dmp.Patch_Margin,
    Rcpp::Named("match_max_bits")         = dmp.Match_MaxBits
  );
}

// [[Rcpp::export]]
void set_options(Rcpp::List opts) {
  
  Rcpp::CharacterVector names = opts.names();
  
  for(int i = 0; i < opts.size(); ++i) {
    
    std::string option = Rcpp::as<std::string>(names[i]);
    double value = opts[i];
    
    if (option == "diff_timeout") {
      dmp.Diff_Timeout = (float) value;
    } else if (option == "diff_edit_cost") {
      dmp.Diff_EditCost = (short) value;
    } else if (option == "match_threshold") {
      dmp.Match_Threshold = (float) value;
    } else if (option == "match_distance") {
      dmp.Match_Distance = (int) value;
    } else if (option == "patch_delete_threshold") {
      dmp.Patch_DeleteThreshold = (float) value;
    } else if (option == "patch_margin") {
      dmp.Patch_Margin = (short) value;
    } else if (option == "match_max_bits") {
      dmp.Match_MaxBits = (short) value;
    } else {
      Rcpp::warning("Warning: \"%s\" is not a valid diffmatchpatch option.", option);
    }
  }
}
