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

test_that("match_find with patterns that use every bit of the bitmask", {
  pattern = "abcdefghijklmnopqrstuvwxyz012345"
  expect_identical(nchar(pattern), 32L)
  text = paste0("0123456789", pattern, "9876543210")

  expect_equal(match_find(text, pattern, loc = 1), 11)
  expect_equal(match_find(text, pattern, loc = 40), 11)

  fuzzy = "abcdefghijklmnopqrstuvwxyz012345"
  substr(fuzzy, 1, 1) = "X"
  expect_equal(match_find(text, fuzzy, loc = 1), 11)
  substr(fuzzy, 32, 32) = "X"
  expect_equal(match_find(text, fuzzy, loc = 1), 11)
  substr(fuzzy, 16, 17) = "XX"
  expect_equal(match_find(text, fuzzy, loc = 1), 11)

  expect_equal(match_find(text, strrep("Z", 32), loc = 1), -1)
  expect_error(match_find(text, paste0(pattern, "6"), loc = 1))
})
