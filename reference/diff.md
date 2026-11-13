# Compute diffs between text strings

The following functions are used to construct or work with diff(s)
between text strings. Specifically, `diff_make()` computes the character
level differences between the source string (`x`) and destination string
(`y`). These diffs can be made more human friendly via a secondary
cleaning process via the `cleanup` argument.

Once computed, diffs are represented using `diff_df` data frames, which
consist of just two columns: `text` and `op`. Basic convenience
functions for pretty printing of these are provided by the package.

The following helper functions are provided:

- [`print()`](https://rdrr.io/r/base/print.html) - prints a diff using
  ANSI colors if available.

- [`as.character()`](https://rdrr.io/r/base/character.html) - converts a
  diff (using ANSI colors if available) to a character vector.

- `diff_levenshtein()` calculates the Levenshtein distance of a diff.

- `diff_to_delta()` converts a diff to a delta string.

- `diff_from_delta()` creates a diff from a source string (`x`) and a
  `delta` string.

- `diff_to_html()` converts a diff to pretty HTML string.

- `diff_to_patch()` converts a diff to a patch string.

- `diff_text_source()` recovers the source string from a diff.

- `diff_text_dest()` recovers the destination string from a diff.

## Usage

``` r
diff_make(x, y, cleanup = "semantic", checklines = TRUE)

diff_levenshtein(diff)

diff_to_delta(diff)

diff_from_delta(x, delta)

diff_to_html(diff)

diff_to_patch(diff)

diff_text_source(diff)

diff_text_dest(diff)
```

## Arguments

- x:

  The source string

- y:

  The destination string

- cleanup:

  Determines the cleanup method applied to the diffs. Allowed values
  include: `semantic`, `lossless`, `efficiency`, `merge` and `none`. See
  Details for the behavior of these methods.

- checklines:

  Performance flag - if `FALSE`, then don't run a line-level diff first
  to identify the changed areas. If `TRUE`, run a faster slightly less
  optimal diff. Default: `TRUE`.

- diff:

  A `diff_df` data frame.

- delta:

  A delta string.

## Value

- `diff_make()` returns a `diff_df` data frame containing the diffs.

&nbsp;

- `diff_make()` returns the Levenshtein distance as an integer.

&nbsp;

- `diff_to_delta()` returns an character string.

&nbsp;

- `diff_from_delta()` returns a `diff_df` data frame.

&nbsp;

- `diff_to_html()` returns a character string.

&nbsp;

- `diff_to_patch()` returns a character string.

&nbsp;

- `diff_text_source()` returns a character string.

&nbsp;

- `diff_text_dest()` returns a character string.

## Details

### Cleanup methods

- `semantic` - Reduce the number of edits by eliminating semantically
  trivial equalities.

- semantic `lossless` - Look for single edits surrounded on both sides
  by equalities which can be shifted sideways to align the edit to a
  word boundary. e.g: The c**at c**ame. -\> The \*\*cat \*\*came.

- `efficiency` - Reduce the number of edits by eliminating operationally
  trivial equalities.

- `merge` - Reorder and merge like edit sections. Merge equalities. Any
  edit section can move as long as it doesn't cross an equality.

- `none` - Do not apply any cleanup methods to the diffs.

## Examples

``` r
(d = diff_make("abcdef", "abchij"))
#> abcdefhij

diff_levenshtein(d)
#> [1] 3

diff_to_html(d)
#> [1] "<span>abc</span><del style=\"background:#ffe6e6;\">def</del><ins style=\"background:#e6ffe6;\">hij</ins>"

diff_text_source(d) 
#> [1] "abcdef"

diff_text_dest(d) 
#> [1] "abchij"

diff_to_patch(d)
#> [1] "@@ -1,6 +1,6 @@\n abc\n-def\n+hij\n"

(delta = diff_to_delta(d))
#> [1] "=3\t-3\t+hij"

diff_from_delta("abcdef", delta)
#> abcdefhij
```
