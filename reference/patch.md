# Create and apply patches to a text string

Patches are constructed via `patch_make()` and applied using
`patch_apply()`.

## Usage

``` r
patch_make(x, y)

patch_apply(x, patch)
```

## Arguments

- x:

  The source string

- y:

  The destination string

- patch:

  A string representation of the patch(es).

## Value

`patch_make()` returns a string representation of the patch(es).

- `patch_apply()` returns the patched version of the string `x`, the
  `matches` attribute contains logical values indicating which patches
  were successfully applied.

## Examples

``` r

(p = patch_make("abcdef", "abchij"))
#> [1] "@@ -1,6 +1,6 @@\n abc\n-def\n+hij\n"

patch_apply("abcdef", p)
#> [1] "abchij"
#> attr(,"matches")
#> [1] TRUE

patch_apply("abc", p)
#> [1] "abchij"
#> attr(,"matches")
#> [1] TRUE

patch_apply("def", p)
#> [1] "hij"
#> attr(,"matches")
#> [1] TRUE

patch_apply("hij", p)
#> [1] "hij"
#> attr(,"matches")
#> [1] FALSE
```
