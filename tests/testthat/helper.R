diff_df = function(...) {
  x = list(...)
  ops = c("DELETE", "INSERT", "EQUAL")
  df = data.frame(
    text = vapply(x, `[[`, character(1), 2),
    op = factor(vapply(x, `[[`, character(1), 1), levels = ops)
  )
  class(df) = c("diff_df", class(df))
  df
}

expect_diff = function(object, expected) {
  expect_identical(as.character(object$text), expected$text)
  expect_identical(as.character(object$op), as.character(expected$op))
}

with_dmp_options = function(opts, code) {
  prev = dmp_options(opts)
  on.exit(dmp_options(prev))
  force(code)
}
