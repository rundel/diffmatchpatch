# Fuzzy matching of a text string

Locate the best instance of `pattern` in the `text` near `loc` using the
Bitap algorithm.Returns `-1` if no match found. Assumes R's typical
1-based indexing for `loc` and the returned value.

This algorithm makes use of the `match_distance` and `match_threshold`
options to determine the match. If these values are not set explicitly
via the `threshold` and `distance` arguments - their value will use the
currently set global option value.

Candidate matches are scored based on: a) the number of spelling
differences between the pattern and the text and b) the distance between
the candidate match and the expected location.

The `match_distance` option determines the relative importance of these
two metrics.

## Usage

``` r
match_find(text, pattern, loc = 1L, threshold = NULL, distance = NULL)
```

## Arguments

- text:

  The text to search.

- pattern:

  The pattern to search for.

- loc:

  The expected location of the pattern.

- threshold:

  Threshold for determining a match (0 - perfect match, 1 - very loose).

- distance:

  Distance from expected location scaling for score penalty.

## Value

Index of best match or -1 for no match.

## Examples

``` r
x = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor 
incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud 
exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure 
dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. 
Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt 
mollit anim id est laborum."

match_find(x, "Loren Ibsen")
#> [1] 1
match_find(x, "Loren Ibsen", threshold = 0.1)
#> [1] -1

match_find(x, "minimum")
#> [1] 137
match_find(x, "minimum", threshold = 0.4)
#> [1] -1
```
