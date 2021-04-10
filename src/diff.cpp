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

//' @export
// [[Rcpp::export]]
int diff_levenshtein(SEXP obj) {
  return dmp.diff_levenshtein( Rcpp::as<Diffs>(obj) );
}

//' @export
// [[Rcpp::export]]
std::string diff_to_delta(SEXP obj) {
  return dmp.diff_toDelta( Rcpp::as<Diffs>(obj) );
}

//' @export
// [[Rcpp::export]]
Rcpp::DataFrame diff_from_delta(std::string x, std::string delta) {
  Diffs d = dmp.diff_fromDelta(x, delta);
  
  return Rcpp::wrap(d);
}

//' @export
// [[Rcpp::export]]
std::string diff_to_html(SEXP obj) {
  return dmp.diff_prettyHtml( Rcpp::as<Diffs>(obj) );
}

//' @export
// [[Rcpp::export]]
std::string diff_to_patch(SEXP obj) {
  Patches p = dmp.patch_make( Rcpp::as<Diffs>(obj) );
  return dmp.patch_toText(p);
}


//' @export
// [[Rcpp::export]]
std::string diff_text_source(SEXP obj) {
  return dmp.diff_text1( Rcpp::as<Diffs>(obj) );
}

//' @export
// [[Rcpp::export]]
std::string diff_text_dest(SEXP obj) {
  return dmp.diff_text2( Rcpp::as<Diffs>(obj) );
}


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

