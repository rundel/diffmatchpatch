## Submission

This release fixes a buffer overflow in the bundled `diff_match_patch.h` header (from an upstream fix) that could crash R when diffing texts with more than 127 unique lines, fixes incorrect line mode diffs for texts with more than 255 unique lines, and adds a test suite.

## Test environments

* local R installation - R 4.6, macOS (aarch64)
* R CMD check via GitHub Actions:
  * macos-latest (release)
  * windows-latest (release)
  * ubuntu-latest (devel)
  * ubuntu-latest (release)
  * ubuntu-latest (oldrel-1)

## R CMD check results

0 errors | 0 warnings | 0 notes

## Reverse dependencies

We checked 1 reverse dependency (md4r), comparing R CMD check results across CRAN and dev versions of this package.
