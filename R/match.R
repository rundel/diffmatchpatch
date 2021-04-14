#' @name match
#' @rdname match
#'
#' @title Fuzzy matching of a text string
#'
#' @examples
#' x = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor 
#' incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud 
#' exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure 
#' dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. 
#' Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt 
#' mollit anim id est laborum."
#' 
#' match_find(x, "Loren Ibsen")
#' match_find(x, "Loren Ibsen", threshold = 0.1)
#' 
#' match_find(x, "minimum")
#' match_find(x, "minimum", threshold = 0.4)
#' 
NULL
