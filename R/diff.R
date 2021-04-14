#' @rdname diff
#' @name diff
#' 
#' @title Compute diffs between text strings
#'
#' @description
#' The following functions are used to construct or work with diff(s) between text strings.
#' Specifically, `diff_make()` computes the character level differences between 
#' the source string (`x`) and destination string (`y`). These diffs can be made more human
#' friendly via a secondary cleaning process via the `cleanup` argument.
#' 
#' Once computed, diffs are represented using `diff_df` data frames, which consist of just 
#' two columns: `text` and `op`. Basic convenience functions for pretty printing of these are
#' provided by the package.
#'
#' The following helper functions are provided:
#' * `print()` - prints a diff using ANSI colors if available.
#' * `as.character()` - converts a diff (using ANSI colors if available) to a character vector.
#' * `diff_levenshtein()` calculates the Levenshtein distance of a diff.
#' * `diff_to_delta()` converts a diff to a delta string.
#' * `diff_from_delta()` creates a diff from a source string (`x`) and a `delta` string.
#' * `diff_to_html()` converts a diff to pretty HTML string.
#' * `diff_to_patch()` converts a diff to a patch string.
#' * `diff_text_source()` recovers the source string from a diff.
#' * `diff_text_dest()` recovers the destination string from a diff.
#'
#' @param x The source string
#' @param y The destination string
#' @param diff A `diff_df` data frame.
#' @param delta A delta string.
#'
#' @examples
#' (d = diff_make("abcdef", "abchij"))
#'
#' diff_levenshtein(d)
#'
#' diff_to_html(d)
#' 
#' diff_text_source(d) 
#' 
#' diff_text_dest(d) 
#' 
#' diff_to_patch(d)
#' 
#' (delta = diff_to_delta(d))
#' 
#' diff_from_delta("abcdef", delta)
NULL
