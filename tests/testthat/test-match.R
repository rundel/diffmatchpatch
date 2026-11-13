# Cases ported from upstream diff_match_patch_test_string.cpp, shifted to
# 1-based locations

test_that("match_find", {
  expect_equal(match_find("abcdef", "abcdef", loc = 1001), 1)
  expect_equal(match_find("", "abcdef", loc = 2), -1)
  expect_equal(match_find("abcdef", "", loc = 4), 4)
  expect_equal(match_find("abcdef", "de", loc = 4), 4)
  expect_equal(
    match_find("I am the very model of a modern major general.", " that berry ", loc = 6, threshold = 0.7),
    5
  )
})

test_that("match_find threshold does not persist", {
  prev = dmp_options("match_threshold")
  match_find("abcdef", "de", threshold = 0.1)
  expect_identical(dmp_options("match_threshold"), prev)
})
