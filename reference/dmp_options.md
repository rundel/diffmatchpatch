# diffmatchpatch settings

Allows for examining or setting options that affect the behavior of the
diff, match, and patch related functions in this package.

## Usage

``` r
dmp_options(...)
```

## Arguments

- ...:

  No arguments returns all current options and their values. Character
  values retrieve a subset of options and the current values. Options
  can be set, using name = value. However, only the options named below
  are used. Options can also be passed by giving a single unnamed
  argument which is a named list.

## Value

When getting options returns a named list of options and their current
values, when setting options returns a named list of the previous
value(s).

## Details

### Available options

- `diff_timeout` (float) - Number of seconds to map a diff before giving
  up (0 for infinity).

- `diff_edit_cost` (int) - Cost of an empty edit operation in terms of
  edit characters.

- `match_threshold` (float) - At what point is no match declared (0.0 =
  perfection, 1.0 = very loose).

- `match_distance` (int) - How far to search for a match (0 = exact
  location, 1000+ = broad match). A match this many characters away from
  the expected location will add 1.0 to the score (0.0 is a perfect
  match).

- `patch_delete_threshold` (float) - When deleting a large block of text
  (over ~64 characters), how close does the contents have to match the
  expected contents. (0.0 = perfection, 1.0 = very loose). Note that
  Match_Threshold controls how closely the end points of a delete need
  to match.

- `patch_margin` (int) - Chunk size for context length.

- `match_max_bits` (int) - The number of bits in an int.

## Examples

``` r
dmp_options()
#> $diff_timeout
#> [1] 1
#> 
#> $diff_edit_cost
#> [1] 4
#> 
#> $match_threshold
#> [1] 0.5
#> 
#> $match_distance
#> [1] 1000
#> 
#> $patch_delete_threshold
#> [1] 0.5
#> 
#> $patch_margin
#> [1] 4
#> 
#> $match_max_bits
#> [1] 32
#> 

dmp_options("diff_timeout")
#> $diff_timeout
#> [1] 1
#> 

prev = dmp_options(diff_timeout = 5)
prev
#> $diff_timeout
#> [1] 1
#> 
```
