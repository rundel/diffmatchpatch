## Submission

This is a patch release addressing the clang-UBSAN issue reported by CRAN for version 0.2.0 (<https://www.stats.ox.ac.uk/pub/bdr/memtests/clang-UBSAN/diffmatchpatch/>).

## Test environments

* local R installation - R 4.6, macOS (aarch64)
* R CMD check via GitHub Actions:
  * macos-latest (release)
  * windows-latest (release)
  * ubuntu-latest (devel)
  * ubuntu-latest (release)
  * ubuntu-latest (oldrel-1)

## R CMD check results

0 errors | 0 warnings | 1 note

* Note - Days since last update: 0. This release is a fix for the UBSAN issue described above.

## Reverse dependencies

We checked 1 reverse dependency (md4r) across CRAN and dev versions of this package.
