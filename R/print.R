dpm_theme = list(
  "EQUAL"  = function(x) { x },
  "INSERT" = function(x) { cli::style_underline(cli::style_bold(cli::col_green(x))) },
  "DELETE" = function(x) { cli::style_inverse(cli::style_bold(cli::col_red(x))) }
)

#' @exportS3Method
print.diff_df = function(x, ...) {
  text = apply(
    x, 1,
    function(row) {
      text = row[1]
      op = row[2]
      dpm_theme[[op]](text)
    }
  )
  text = paste(text, collapse="")
  
  cli::cat_line(text)
}