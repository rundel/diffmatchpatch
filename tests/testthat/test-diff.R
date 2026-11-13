# Cases ported from upstream diff_match_patch_test_string.cpp

test_that("diff_make handles basic cases", {
  expect_equal(nrow(diff_make("", "", cleanup = "none", checklines = FALSE)), 0)

  expect_diff(
    diff_make("abc", "abc", cleanup = "none", checklines = FALSE),
    diff_df(c("EQUAL", "abc"))
  )
  expect_diff(
    diff_make("abc", "ab123c", cleanup = "none", checklines = FALSE),
    diff_df(c("EQUAL", "ab"), c("INSERT", "123"), c("EQUAL", "c"))
  )
  expect_diff(
    diff_make("a123bc", "abc", cleanup = "none", checklines = FALSE),
    diff_df(c("EQUAL", "a"), c("DELETE", "123"), c("EQUAL", "bc"))
  )
  expect_diff(
    diff_make("abc", "a123b456c", cleanup = "none", checklines = FALSE),
    diff_df(c("EQUAL", "a"), c("INSERT", "123"), c("EQUAL", "b"), c("INSERT", "456"), c("EQUAL", "c"))
  )
  expect_diff(
    diff_make("a123b456c", "abc", cleanup = "none", checklines = FALSE),
    diff_df(c("EQUAL", "a"), c("DELETE", "123"), c("EQUAL", "b"), c("DELETE", "456"), c("EQUAL", "c"))
  )
})

test_that("diff_make handles real diffs", {
  with_dmp_options(list(diff_timeout = 0), {
    expect_diff(
      diff_make("a", "b", cleanup = "none", checklines = FALSE),
      diff_df(c("DELETE", "a"), c("INSERT", "b"))
    )
    expect_diff(
      diff_make("Apples are a fruit.", "Bananas are also fruit.", cleanup = "none", checklines = FALSE),
      diff_df(
        c("DELETE", "Apple"), c("INSERT", "Banana"), c("EQUAL", "s are a"),
        c("INSERT", "lso"), c("EQUAL", " fruit.")
      )
    )
    expect_diff(
      diff_make("1ayb2", "abxab", cleanup = "none", checklines = FALSE),
      diff_df(
        c("DELETE", "1"), c("EQUAL", "a"), c("DELETE", "y"), c("EQUAL", "b"),
        c("DELETE", "2"), c("INSERT", "xab")
      )
    )
    expect_diff(
      diff_make("abcy", "xaxcxabc", cleanup = "none", checklines = FALSE),
      diff_df(c("INSERT", "xaxcx"), c("EQUAL", "abc"), c("DELETE", "y"))
    )
    expect_diff(
      diff_make("a [[Pennsylvania]] and [[New", " and [[Pennsylvania]]", cleanup = "none", checklines = FALSE),
      diff_df(
        c("INSERT", " "), c("EQUAL", "a"), c("INSERT", "nd"),
        c("EQUAL", " [[Pennsylvania]]"), c("DELETE", " and [[New")
      )
    )
  })
})

test_that("line mode matches character mode", {
  a = strrep("1234567890\n", 13)
  b = strrep("abcdefghij\n", 13)
  expect_identical(
    diff_make(a, b, cleanup = "none", checklines = TRUE),
    diff_make(a, b, cleanup = "none", checklines = FALSE)
  )

  a = strrep("1234567890", 13)
  b = strrep("abcdefghij", 13)
  expect_identical(
    diff_make(a, b, cleanup = "none", checklines = TRUE),
    diff_make(a, b, cleanup = "none", checklines = FALSE)
  )

  a = strrep("1234567890\n", 13)
  b = strrep("abcdefghij\n1234567890\n1234567890\n1234567890\n", 3)
  b = paste0(b, "abcdefghij\n")
  d_line = diff_make(a, b, cleanup = "none", checklines = TRUE)
  d_char = diff_make(a, b, cleanup = "none", checklines = FALSE)
  expect_identical(diff_text_source(d_line), diff_text_source(d_char))
  expect_identical(diff_text_dest(d_line), diff_text_dest(d_char))
})

line_mode_texts = function(n) {
  i = seq_len(n)
  list(
    x = paste0("line ", i, "\n", collapse = ""),
    y = paste0(ifelse(i %% 3 == 0, paste("new", i), paste("line", i)), "\n", collapse = "")
  )
}

test_that("line mode reconstructs texts with many unique lines", {
  # More than 127 unique lines previously indexed out of bounds via signed char
  # and more than 255 wrapped the line codes, giving incorrect diffs.
  for (n in c(50, 100, 200, 300, 1000, 5000)) {
    txt = line_mode_texts(n)
    d = diff_make(txt$x, txt$y, checklines = TRUE)
    expect_identical(diff_text_source(d), txt$x, label = paste("source, n =", n))
    expect_identical(diff_text_dest(d), txt$y, label = paste("dest, n =", n))
  }
})

test_that("line mode handles many unique lines in only one text", {
  i = seq_len(500)
  x = paste0("line ", i, "\n", collapse = "")
  y = paste0("other ", i, "\n", collapse = "")

  for (args in list(list(x, y), list(y, x), list(x, "short\n"), list("short\n", y))) {
    d = diff_make(args[[1]], args[[2]], checklines = TRUE)
    expect_identical(diff_text_source(d), args[[1]])
    expect_identical(diff_text_dest(d), args[[2]])
  }
})

test_that("line mode handles text without trailing newline past the cap", {
  i = seq_len(400)
  x = paste0("line ", i, collapse = "\n")
  y = paste0(ifelse(i %% 2 == 0, "changed", "line"), " ", i, collapse = "\n")
  d = diff_make(x, y, checklines = TRUE)
  expect_identical(diff_text_source(d), x)
  expect_identical(diff_text_dest(d), y)
})

test_that("diff_make rejects unknown cleanup", {
  expect_error(diff_make("a", "b", cleanup = "nope"), "Unknown cleanup")
})

test_that("diff_text_source and diff_text_dest", {
  d = diff_df(
    c("EQUAL", "jump"), c("DELETE", "s"), c("INSERT", "ed"), c("EQUAL", " over "),
    c("DELETE", "the"), c("INSERT", "a"), c("EQUAL", " lazy")
  )
  expect_identical(diff_text_source(d), "jumps over the lazy")
  expect_identical(diff_text_dest(d), "jumped over a lazy")
})

test_that("diff_to_delta and diff_from_delta", {
  d = diff_df(
    c("EQUAL", "jump"), c("DELETE", "s"), c("INSERT", "ed"), c("EQUAL", " over "),
    c("DELETE", "the"), c("INSERT", "a"), c("EQUAL", " lazy"), c("INSERT", "old dog")
  )
  text1 = diff_text_source(d)
  expect_identical(text1, "jumps over the lazy")

  delta = diff_to_delta(d)
  expect_identical(delta, "=4\t-1\t+ed\t=6\t-3\t+a\t=5\t+old dog")
  expect_diff(diff_from_delta(text1, delta), d)

  expect_error(diff_from_delta(paste0(text1, "x"), delta))
  expect_error(diff_from_delta(substring(text1, 2), delta))
  expect_error(diff_from_delta("", "+%c3%xy"))

  chars = "A-Z a-z 0-9 - _ . ! ~ * ' ( ) ; / ? : @ & = + $ , # "
  d = diff_df(c("INSERT", chars))
  expect_identical(diff_text_dest(d), chars)
  delta = diff_to_delta(d)
  expect_identical(delta, paste0("+", chars))
  expect_diff(diff_from_delta("", delta), d)
})

test_that("diff_levenshtein", {
  expect_equal(diff_levenshtein(diff_df(c("DELETE", "abc"), c("INSERT", "1234"), c("EQUAL", "xyz"))), 4)
  expect_equal(diff_levenshtein(diff_df(c("EQUAL", "xyz"), c("DELETE", "abc"), c("INSERT", "1234"))), 4)
  expect_equal(diff_levenshtein(diff_df(c("DELETE", "abc"), c("EQUAL", "xyz"), c("INSERT", "1234"))), 7)
})

test_that("diff_to_html", {
  d = diff_df(c("EQUAL", "a\n"), c("DELETE", "<B>b</B>"), c("INSERT", "c&d"))
  expect_identical(
    diff_to_html(d),
    "<span>a&para;<br></span><del style=\"background:#ffe6e6;\">&lt;B&gt;b&lt;/B&gt;</del><ins style=\"background:#e6ffe6;\">c&amp;d</ins>"
  )
})

test_that("diff functions require a diff_df", {
  expect_error(diff_levenshtein(data.frame(text = "a", op = 1L)), "diff_df")
})
