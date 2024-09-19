
<!-- README.md is generated from README.Rmd. Please edit that file -->

# diffmatchpatch

<!-- badges: start -->

[![R-CMD-check](https://github.com/rundel/diffmatchpatch/actions/workflows/check-standard.yaml/badge.svg)](https://github.com/rundel/diffmatchpatch/actions/workflows/check-standard.yaml)
[![CRAN
status](https://www.r-pkg.org/badges/version/diffmatchpatch)](https://CRAN.R-project.org/package=diffmatchpatch)
<!-- badges: end -->

`diffmatchpatch` provides an R wrapper for the [STL
variant](https://github.com/leutloff/diff-match-patch-cpp-stl) of
Google’s [diff-match-patch](https://github.com/google/diff-match-patch/)
library.

## Installation

You can install the released version of diffmatchpatch from
[CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("diffmatchpatch")
```

The development version of this library can be installed directly from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("rundel/diffmatchpatch")
```

## Examples

All of the following examples are derived from Neil Fraser’s demos
linked from Google’s [diffmatchpatch
repo](https://github.com/google/diff-match-patch):
[diff](https://neil.fraser.name/software/diff_match_patch/demos/diff.html),
[match](https://neil.fraser.name/software/diff_match_patch/demos/match.html),
[patch](https://neil.fraser.name/software/diff_match_patch/demos/patch.html).

These examples are all run using the default options provided by the
library.

``` r
library(diffmatchpatch)

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
```

### diff

These functions compare two text strings and efficiently return a list
of (character level) differences. Note that the following text indicates
deletions with `-|text|-` and additions with `+|text|+` - within
environments that support ANSI escape strings (e.g. RStudio) these will
be colored red and green respectively.

``` r
src = "I am the very model of a modern Major-General,
I've information vegetable, animal, and mineral,
I know the kings of England, and I quote the fights historical,
From Marathon to Waterloo, in order categorical."

dest = "I am the very model of a cartoon individual,
My animation's comical, unusual, and whimsical,
I'm quite adept at funny gags, comedic theory I have read,
From wicked puns and stupid jokes to anvils that drop on your head."

diff_make(src, dest)
#> I am the very model of a -|modern Major-General,
#> I've information vegetable, animal, and mineral,
#> I know the kings of England, and I quote the fights historical,
#> From Marathon to Waterloo, in order categorical|-+|cartoon individual,
#> My animation's comical, unusual, and whimsical,
#> I'm quite adept at funny gags, comedic theory I have read,
#> From wicked puns and stupid jokes to anvils that drop on your head|+.
```

``` r
diff_make(src, dest, cleanup = "efficiency")
#> I am the very model of a -|modern Major-Gener|-+|cartoon individu|+al,
#> -|I've infor|-+|My ani|+mation-| vegetable, anim|-+|'s comical, unusu|+al, and -|miner|-+|whimsic|+al,
#> I-| know the kings of England, and I quote|-+|'m quite adept at funny gags, comedic|+ the-| fights historical|-+|ory I have read|+,
#> From -|Marathon|-+|wicked puns and stupid jokes|+ to -|Waterloo, in order categorical|-+|anvils that drop on your head|+.
```

``` r
diff_make(src, dest, cleanup = "none")
#> I am the very model of a -|m|-+|carto|+o-|der|-n -|Major-Ge|-+|i|+n-|er|-+|dividu|+al,
#> -|I've|-+|My|+ -|i|-+|a|+n-|for|-+|i|+mation+|'s|+ -|veget|-+|comic|+a-|b|-l-|e|-, -|a|-+|u|+n-|im|-+|usu|+al, and +|whi|+m+|s|+i-|ner|-+|c|+al,
#> I+|'m|+ -|know|-+|quite|+ +|adep|+t-|he|- -|kings|-+|at|+ -|o|-f-| E|-+|u|+n+|ny |+g-|l|-a-|nd|-+|gs|+, -|and I qu|-+|c|+o-|t|-+|m|+e+|dic|+ the+|ory|+ -|fig|-+|I |+h-|ts|-+|ave|+ -|histo|-r-|ic|-+|e|+a-|l|-+|d|+,
#> From -|Mar|-+|wicked puns |+a+|nd s|+t-|h|-+|upid j|+o-|n|-+|kes|+ to -|W|-+|anvils th|+at-|e|-+| d|+r-|l|-o+|p |+o-|, i|-n +|y|+o-|rde|-+|u|+r -|cat|-+|h|+e-|goric|-a-|l|-+|d|+.
```

There are a number of helper functions provided for interacting with the
resulting diff objects.

``` r
d = diff_make(src, dest, cleanup = "efficiency")

diff_levenshtein(d)
#> [1] 167
 
diff_to_patch(d) %>% cat()
#> @@ -22,70 +22,65 @@
#>  f a 
#> -modern Major-Gener
#> +cartoon individu
#>  al,%0A
#> -I've infor
#> +My ani
#>  mation
#> - vegetable, anim
#> +'s comical, unusu
#>  al, and 
#>  mine
#> @@ -79,125 +79,141 @@
#>  and 
#> -miner
#> +whimsic
#>  al,%0AI
#> - know the kings of England, and I quote
#> +'m quite adept at funny gags, comedic
#>   the
#> - fights historical
#> +ory I have read
#>  ,%0AFrom 
#> -Marathon
#> +wicked puns and stupid jokes
#>   to 
#> -Waterloo, in order categorical
#> +anvils that drop on your head
#>  .

diff_to_html(d) %>% cat()
#> <span>I am the very model of a </span><del style="background:#ffe6e6;">modern Major-Gener</del><ins style="background:#e6ffe6;">cartoon individu</ins><span>al,&para;<br></span><del style="background:#ffe6e6;">I've infor</del><ins style="background:#e6ffe6;">My ani</ins><span>mation</span><del style="background:#ffe6e6;"> vegetable, anim</del><ins style="background:#e6ffe6;">'s comical, unusu</ins><span>al, and </span><del style="background:#ffe6e6;">miner</del><ins style="background:#e6ffe6;">whimsic</ins><span>al,&para;<br>I</span><del style="background:#ffe6e6;"> know the kings of England, and I quote</del><ins style="background:#e6ffe6;">'m quite adept at funny gags, comedic</ins><span> the</span><del style="background:#ffe6e6;"> fights historical</del><ins style="background:#e6ffe6;">ory I have read</ins><span>,&para;<br>From </span><del style="background:#ffe6e6;">Marathon</del><ins style="background:#e6ffe6;">wicked puns and stupid jokes</ins><span> to </span><del style="background:#ffe6e6;">Waterloo, in order categorical</del><ins style="background:#e6ffe6;">anvils that drop on your head</ins><span>.</span>

diff_text_source(d) %>% cat()
#> I am the very model of a modern Major-General,
#> I've information vegetable, animal, and mineral,
#> I know the kings of England, and I quote the fights historical,
#> From Marathon to Waterloo, in order categorical.

diff_text_dest(d) %>% cat()
#> I am the very model of a cartoon individual,
#> My animation's comical, unusual, and whimsical,
#> I'm quite adept at funny gags, comedic theory I have read,
#> From wicked puns and stupid jokes to anvils that drop on your head.
```

### match

`match_find` looks for a pattern within a larger text string using fuzzy
matching. This means it can find a match even if the pattern contains
errors and doesn’t exactly match what is found in the text. Candidate
matches are scored based on a) the number of spelling differences
between the pattern and the text and b) the distance between the
candidate match and the expected location.

The returned value indicates the starting index (1-based indexing) of
the matched text. The function returns -1 in cases where a match cannot
be found.

``` r
text = "'Twas brillig, and the slithy toves
Did gyre and gimble in the wabe.
All mimsy were the borogroves,
And the mome raths outgrabe."

match_find(text, pattern = "slimy tools")
#> [1] 24
```

There is an additional `loc` argument that provides a suggested location
of where the pattern is expected to be found.

``` r
match_find(text, pattern = "and", loc = 0)
#> [1] 16
match_find(text, pattern = "and", loc = 30)
#> [1] 16
match_find(text, pattern = "and", loc = 50)
#> [1] 46
```

Finally, the behavior of the fuzzy matching is controlled by the
`match_distance` and `match_threshold` options which can be set via
`dpm_options()`.

``` r
prev = dmp_options(match_threshold = 0.3)
match_find(text, pattern = "slimy tools", loc = 30)
#> [1] -1

dmp_options(prev)
```

### patch

A patch is just a description of how to transform one text string into
another (i.e. a fancy diff) and once constructed can be applied against
a new string (or the original). See this
[article](https://en.wikipedia.org/wiki/Diff#Unified_format) for more
details on the specific formatting of a patch text string.

``` r
source = "Hamlet: Do you see yonder cloud that's almost in shape of a camel?
Polonius: By the mass, and 'tis like a camel, indeed.
Hamlet: Methinks it is like a weasel.
Polonius: It is backed like a weasel.
Hamlet: Or like a whale?
Polonius: Very like a whale.
-- Shakespeare"

dest = "Hamlet: Do you see the cloud over there that's almost the shape of a camel?
Polonius: By golly, it is like a camel, indeed.
Hamlet: I think it looks like a weasel.
Polonius: It is shaped like a weasel.
Hamlet: Or like a whale?
Polonius: It's totally like a whale.
-- Shakespeare"

(p = patch_make(source, dest))
#> [1] "@@ -16,21 +16,29 @@\n see \n-yonder\n+the\n  cloud \n+over there \n that\n@@ -47,18 +47,19 @@\n  almost \n-in\n+the\n  shape o\n@@ -86,24 +86,18 @@\n  By \n-the mass, and 't\n+golly, it \n is l\n@@ -129,21 +129,23 @@\n et: \n-Me\n+I \n think\n-s\n  it \n-i\n+look\n s li\n@@ -177,12 +177,12 @@\n  is \n-back\n+shap\n ed l\n@@ -234,11 +234,19 @@\n us: \n-Ver\n+It's totall\n y li\n"
```

``` r
new_source = "Kirk: Do you see yonder cloud that's almost in shape of a Klingon?
Spock: By the mass, and 'tis like a Klingon, indeed.
Kirk: Methinks it is like a Vulcan.
Spock: It is backed like a Vulcan.
Kirk: Or like a Romulan?
Spock: Very like a Romulan.
-- Trekkie"

patch_apply(new_source, p) %>% cat()
#> Kirk: Do you see the cloud over there that's almost the shape of a Klingon?
#> Spock: By golly, it is like a Klingon, indeed.
#> Kirk: I think it looks like a Vulcan.
#> Spock: It is shaped like a Vulcan.
#> Kirk: Or like a Romulan?
#> Spock: It's totally like a Romulan.
#> -- Trekkie
```
