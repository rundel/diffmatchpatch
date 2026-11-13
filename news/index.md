# Changelog

## diffmatchpatch 0.2.0

- Updated `diff_match_patch.h` with the upstream fix for a buffer
  overflow in line mode diffs when there are more than 127 unique lines,
  which could crash R (leutloff/diff-match-patch-cpp-stl#19).

- Fixed incorrect line mode diffs when there are more than 255 unique
  lines. The number of line codes is now capped and any remaining text
  is treated as a single line, following the approach used by the other
  diff-match-patch implementations.

- Added a testthat test suite, with cases ported from the upstream test
  harness.

## diffmatchpatch 0.1.0

CRAN release: 2021-04-16

- Initial release with support for the core diff, match, and patch
  functions.

- Added a `NEWS.md` file to track changes to the package.
