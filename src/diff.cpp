#include "common.h"
#include <Rcpp.h>

// [[Rcpp::plugins(cpp11)]]

namespace Rcpp {
// chunk wrappers
template <> SEXP wrap(Diffs const& d) {
  Rcpp::CharacterVector text;
  Rcpp::IntegerVector op;
  
  for(Diff const& x : d) {
    text.push_back(x.text);
    op.push_back((int)x.operation + 1);
  }
  
  op.attr("class") = "factor";
  op.attr("levels") = Rcpp::CharacterVector::create("DELETE", "INSERT", "EQUAL");
  
  
  Rcpp::DataFrame res = Rcpp::DataFrame::create(
    Rcpp::Named("text") = text,
    Rcpp::Named("op") = op
  );
  
  res.attr("class") = Rcpp::CharacterVector::create("diff_df", "data.frame");
  
  return res;
}

template <> Diffs as(SEXP obj) {
  if (!Rf_inherits(obj, "diff_df"))
    Rcpp::stop("Object must have class diff_df.");
  
  Rcpp::DataFrame df(obj);
  Rcpp::CharacterVector text = df[0];
  Rcpp::IntegerVector op = df[1];
  
  Diffs d;
  
  for(int i=0; i != text.size(); ++i) {
    Diff x;
    x.text = text[i];
    x.operation = static_cast<Operation>(op[i]-1); 
    
    d.push_back(x);
  }
  
  return d;
}
}


//' @rdname diff
//'
//' @param cleanup Determines the cleanup method applied to the diffs. Allowed values include:
//' `semantic`, `lossless`, `efficiency`, `merge` and `none`. See Details for the behavior of 
//' these methods.
//' @param checklines Performance flag - if `FALSE`, then don't run a
//' line-level diff first to identify the changed areas.
//' If `TRUE`, run a faster slightly less optimal diff. Default: `TRUE`.
//' 
//' @details
//' ## Cleanup methods
//' 
//' * `semantic` - Reduce the number of edits by eliminating semantically trivial equalities.
//' * semantic `lossless` - Look for single edits surrounded on both sides by equalities
//'   which can be shifted sideways to align the edit to a word boundary.
//'   e.g: The c**at c**ame. -> The **cat **came.
//' * `efficiency` - Reduce the number of edits by eliminating operationally trivial equalities.
//' * `merge` - Reorder and merge like edit sections.  Merge equalities.
//'   Any edit section can move as long as it doesn't cross an equality.
//' * `none` - Do not apply any cleanup methods to the diffs.
//'
//' @return * `diff_make()` returns a `diff_df` data frame containing the diffs.
//'
//' @export
// [[Rcpp::export]]
Rcpp::DataFrame diff_make(
    std::string const& x, std::string const& y, 
    std::string cleanup = "semantic", bool checklines = true
) {
  Diffs d = dmp.diff_main(x, y, checklines);
  
  if (cleanup == "semantic") {
    dmp.diff_cleanupSemantic(d);
  } else if (cleanup == "lossless") {
    dmp.diff_cleanupSemanticLossless(d);
  } else if (cleanup == "efficiency") {
    dmp.diff_cleanupEfficiency(d);
  } else if (cleanup == "merge") {
    dmp.diff_cleanupMerge(d);
  } else if (cleanup != "none") {
    Rcpp::stop("Unknown cleanup method."); 
  }
  
  return Rcpp::wrap(d);
}


//' @rdname diff
//' @return * `diff_make()` returns the Levenshtein distance as an integer.
//' @export
// [[Rcpp::export]]
int diff_levenshtein(SEXP diff) {
  return dmp.diff_levenshtein( Rcpp::as<Diffs>(diff) );
}

//' @rdname diff
//' @return * `diff_to_delta()` returns an character string.
//' @export
// [[Rcpp::export]]
std::string diff_to_delta(SEXP diff) {
  return dmp.diff_toDelta( Rcpp::as<Diffs>(diff) );
}

//' @rdname diff
//' @return * `diff_from_delta()` returns a `diff_df` data frame.
//' @export
// [[Rcpp::export]]
Rcpp::DataFrame diff_from_delta(std::string x, std::string delta) {
  Diffs d = dmp.diff_fromDelta(x, delta);
  
  return Rcpp::wrap(d);
}

//' @rdname diff
//' @return * `diff_to_html()` returns a character string.
//' @export
// [[Rcpp::export]]
std::string diff_to_html(SEXP diff) {
  return dmp.diff_prettyHtml( Rcpp::as<Diffs>(diff) );
}

//' @rdname diff
//' @return * `diff_to_patch()` returns a character string.
//' @export
// [[Rcpp::export]]
std::string diff_to_patch(SEXP diff) {
  Patches p = dmp.patch_make( Rcpp::as<Diffs>(diff) );
  return dmp.patch_toText(p);
}

//' @rdname diff
//' @return * `diff_text_source()` returns a character string.
//' @export
// [[Rcpp::export]]
std::string diff_text_source(SEXP diff) {
  return dmp.diff_text1( Rcpp::as<Diffs>(diff) );
}

//' @rdname diff
//' @return * `diff_text_dest()` returns a character string.
//' @export
// [[Rcpp::export]]
std::string diff_text_dest(SEXP diff) {
  return dmp.diff_text2( Rcpp::as<Diffs>(diff) );
}


