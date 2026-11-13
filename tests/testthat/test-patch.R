# Cases ported from upstream diff_match_patch_test_string.cpp

test_that("patch_make", {
  expect_identical(patch_make("", ""), "")

  text1 = "The quick brown fox jumps over the lazy dog."
  text2 = "That quick brown fox jumped over a lazy dog."
  expect_identical(
    patch_make(text2, text1),
    "@@ -1,8 +1,7 @@\n Th\n-at\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+s\n  over \n-a\n+the\n  laz\n"
  )
  expect_identical(
    patch_make(text1, text2),
    "@@ -1,11 +1,12 @@\n Th\n-e\n+at\n  quick b\n@@ -22,18 +22,17 @@\n jump\n-s\n+ed\n  over \n-the\n+a\n  laz\n"
  )
  expect_identical(
    patch_make("`1234567890-=[]\\;',./", "~!@#$%^&*()_+{}|:\"<>?"),
    "@@ -1,21 +1,21 @@\n-%601234567890-=%5B%5D%5C;',./\n+~!@#$%25%5E&*()_+%7B%7D%7C:%22%3C%3E?\n"
  )

  text1 = strrep("abcdef", 100)
  expect_identical(
    patch_make(text1, paste0(text1, "123")),
    "@@ -573,28 +573,31 @@\n cdefabcdefabcdefabcdefabcdef\n+123\n"
  )
})

test_that("diff_to_patch matches patch_make", {
  text1 = "The quick brown fox jumps over the lazy dog."
  text2 = "That quick brown fox jumped over a lazy dog."
  expect_identical(
    diff_to_patch(diff_make(text1, text2, cleanup = "none", checklines = FALSE)),
    patch_make(text1, text2)
  )
})

expect_patch = function(res, text, matches) {
  expect_identical(as.character(res), text)
  expect_identical(attr(res, "matches"), matches)
}

test_that("patch_apply", {
  with_dmp_options(list(match_distance = 1000, match_threshold = 0.5, patch_delete_threshold = 0.5), {
    expect_patch(patch_apply("Hello world.", patch_make("", "")), "Hello world.", logical())

    p = patch_make("The quick brown fox jumps over the lazy dog.", "That quick brown fox jumped over a lazy dog.")
    expect_patch(
      patch_apply("The quick brown fox jumps over the lazy dog.", p),
      "That quick brown fox jumped over a lazy dog.", c(TRUE, TRUE)
    )
    expect_patch(
      patch_apply("The quick red rabbit jumps over the tired tiger.", p),
      "That quick red rabbit jumped over a tired tiger.", c(TRUE, TRUE)
    )
    expect_patch(
      patch_apply("I am the very model of a modern major general.", p),
      "I am the very model of a modern major general.", c(FALSE, FALSE)
    )

    p = patch_make("x1234567890123456789012345678901234567890123456789012345678901234567890y", "xabcy")
    expect_patch(
      patch_apply("x123456789012345678901234567890-----++++++++++-----123456789012345678901234567890y", p),
      "xabcy", c(TRUE, TRUE)
    )
    expect_patch(
      patch_apply("x12345678901234567890---------------++++++++++---------------12345678901234567890y", p),
      "xabc12345678901234567890---------------++++++++++---------------12345678901234567890y", c(FALSE, TRUE)
    )
    with_dmp_options(list(patch_delete_threshold = 0.6), {
      expect_patch(
        patch_apply("x12345678901234567890---------------++++++++++---------------12345678901234567890y", p),
        "xabcy", c(TRUE, TRUE)
      )
    })

    with_dmp_options(list(match_threshold = 0, match_distance = 0), {
      p = patch_make(
        "abcdefghijklmnopqrstuvwxyz--------------------1234567890",
        "abcXXXXXXXXXXdefghijklmnopqrstuvwxyz--------------------1234567YYYYYYYYYY890"
      )
      expect_patch(
        patch_apply("ABCDEFGHIJKLMNOPQRSTUVWXYZ--------------------1234567890", p),
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ--------------------1234567YYYYYYYYYY890", c(FALSE, TRUE)
      )
    })

    expect_patch(patch_apply("", patch_make("", "test")), "test", TRUE)
    expect_patch(patch_apply("XY", patch_make("XY", "XtestY")), "XtestY", TRUE)
    expect_patch(patch_apply("x", patch_make("y", "y123")), "x123", TRUE)
  })
})

test_that("patch_make and patch_apply round trip with many unique lines", {
  i = seq_len(1000)
  x = paste0("line ", i, "\n", collapse = "")
  y = paste0(ifelse(i %% 3 == 0, paste("new", i), paste("line", i)), "\n", collapse = "")
  res = patch_apply(x, patch_make(x, y))
  expect_identical(as.character(res), y)
  expect_true(all(attr(res, "matches")))
})
