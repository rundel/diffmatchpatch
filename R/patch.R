#' @name patch
#' @rdname patch
#' 
#' @title Create and apply patches to a text string
#'
#' @description
#' Patches are constructed via `patch_make()` and applied using `patch_apply()`.
#'
#' @param x The source string
#' @param y The destination string
#' @param patch A string representation of the patch(es).
#' 
#' @examples 
#' 
#' (p = patch_make("abcdef", "abchij"))
#' 
#' patch_apply("abcdef", p)
#' 
#' patch_apply("abc", p)
#' 
#' patch_apply("def", p)
#' 
#' patch_apply("hij", p)
#'
NULL 