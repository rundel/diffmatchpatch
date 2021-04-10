// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// diff_make
Rcpp::DataFrame diff_make(std::string const& x, std::string const& y, std::string cleanup, bool checklines);
RcppExport SEXP _diffmatchpatch_diff_make(SEXP xSEXP, SEXP ySEXP, SEXP cleanupSEXP, SEXP checklinesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string const& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string const& >::type y(ySEXP);
    Rcpp::traits::input_parameter< std::string >::type cleanup(cleanupSEXP);
    Rcpp::traits::input_parameter< bool >::type checklines(checklinesSEXP);
    rcpp_result_gen = Rcpp::wrap(diff_make(x, y, cleanup, checklines));
    return rcpp_result_gen;
END_RCPP
}
// diff_levenshtein
int diff_levenshtein(SEXP diff);
RcppExport SEXP _diffmatchpatch_diff_levenshtein(SEXP diffSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type diff(diffSEXP);
    rcpp_result_gen = Rcpp::wrap(diff_levenshtein(diff));
    return rcpp_result_gen;
END_RCPP
}
// diff_to_delta
std::string diff_to_delta(SEXP diff);
RcppExport SEXP _diffmatchpatch_diff_to_delta(SEXP diffSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type diff(diffSEXP);
    rcpp_result_gen = Rcpp::wrap(diff_to_delta(diff));
    return rcpp_result_gen;
END_RCPP
}
// diff_from_delta
Rcpp::DataFrame diff_from_delta(std::string x, std::string delta);
RcppExport SEXP _diffmatchpatch_diff_from_delta(SEXP xSEXP, SEXP deltaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string >::type delta(deltaSEXP);
    rcpp_result_gen = Rcpp::wrap(diff_from_delta(x, delta));
    return rcpp_result_gen;
END_RCPP
}
// diff_to_html
std::string diff_to_html(SEXP diff);
RcppExport SEXP _diffmatchpatch_diff_to_html(SEXP diffSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type diff(diffSEXP);
    rcpp_result_gen = Rcpp::wrap(diff_to_html(diff));
    return rcpp_result_gen;
END_RCPP
}
// diff_to_patch
std::string diff_to_patch(SEXP diff);
RcppExport SEXP _diffmatchpatch_diff_to_patch(SEXP diffSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type diff(diffSEXP);
    rcpp_result_gen = Rcpp::wrap(diff_to_patch(diff));
    return rcpp_result_gen;
END_RCPP
}
// diff_text_source
std::string diff_text_source(SEXP diff);
RcppExport SEXP _diffmatchpatch_diff_text_source(SEXP diffSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type diff(diffSEXP);
    rcpp_result_gen = Rcpp::wrap(diff_text_source(diff));
    return rcpp_result_gen;
END_RCPP
}
// diff_text_dest
std::string diff_text_dest(SEXP diff);
RcppExport SEXP _diffmatchpatch_diff_text_dest(SEXP diffSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type diff(diffSEXP);
    rcpp_result_gen = Rcpp::wrap(diff_text_dest(diff));
    return rcpp_result_gen;
END_RCPP
}
// match_find
int match_find(std::string const& text, std::string const& pattern, int loc);
RcppExport SEXP _diffmatchpatch_match_find(SEXP textSEXP, SEXP patternSEXP, SEXP locSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string const& >::type text(textSEXP);
    Rcpp::traits::input_parameter< std::string const& >::type pattern(patternSEXP);
    Rcpp::traits::input_parameter< int >::type loc(locSEXP);
    rcpp_result_gen = Rcpp::wrap(match_find(text, pattern, loc));
    return rcpp_result_gen;
END_RCPP
}
// get_options
Rcpp::List get_options();
RcppExport SEXP _diffmatchpatch_get_options() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(get_options());
    return rcpp_result_gen;
END_RCPP
}
// set_options
void set_options(Rcpp::List opts);
RcppExport SEXP _diffmatchpatch_set_options(SEXP optsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type opts(optsSEXP);
    set_options(opts);
    return R_NilValue;
END_RCPP
}
// patch_make
std::string patch_make(std::string const& x, std::string const& y);
RcppExport SEXP _diffmatchpatch_patch_make(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string const& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string const& >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(patch_make(x, y));
    return rcpp_result_gen;
END_RCPP
}
// patch_apply
Rcpp::CharacterVector patch_apply(std::string const& x, std::string const& patch);
RcppExport SEXP _diffmatchpatch_patch_apply(SEXP xSEXP, SEXP patchSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string const& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string const& >::type patch(patchSEXP);
    rcpp_result_gen = Rcpp::wrap(patch_apply(x, patch));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_diffmatchpatch_diff_make", (DL_FUNC) &_diffmatchpatch_diff_make, 4},
    {"_diffmatchpatch_diff_levenshtein", (DL_FUNC) &_diffmatchpatch_diff_levenshtein, 1},
    {"_diffmatchpatch_diff_to_delta", (DL_FUNC) &_diffmatchpatch_diff_to_delta, 1},
    {"_diffmatchpatch_diff_from_delta", (DL_FUNC) &_diffmatchpatch_diff_from_delta, 2},
    {"_diffmatchpatch_diff_to_html", (DL_FUNC) &_diffmatchpatch_diff_to_html, 1},
    {"_diffmatchpatch_diff_to_patch", (DL_FUNC) &_diffmatchpatch_diff_to_patch, 1},
    {"_diffmatchpatch_diff_text_source", (DL_FUNC) &_diffmatchpatch_diff_text_source, 1},
    {"_diffmatchpatch_diff_text_dest", (DL_FUNC) &_diffmatchpatch_diff_text_dest, 1},
    {"_diffmatchpatch_match_find", (DL_FUNC) &_diffmatchpatch_match_find, 3},
    {"_diffmatchpatch_get_options", (DL_FUNC) &_diffmatchpatch_get_options, 0},
    {"_diffmatchpatch_set_options", (DL_FUNC) &_diffmatchpatch_set_options, 1},
    {"_diffmatchpatch_patch_make", (DL_FUNC) &_diffmatchpatch_patch_make, 2},
    {"_diffmatchpatch_patch_apply", (DL_FUNC) &_diffmatchpatch_patch_apply, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_diffmatchpatch(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
