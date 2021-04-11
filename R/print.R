dpm_theme = list(
  "EQUAL"  = function(x) { x },
  "INSERT" = function(x) { cli::style_inverse(cli::style_bold(cli::col_green(x))) },
  "DELETE" = function(x) { cli::style_inverse(cli::style_bold(cli::col_red(x))) }
)

#' @exportS3Method
print.diff_df = function(x, ...) {
  text = apply(
    x, 1,
    function(row) {
      text = row[1]
      op = row[2]
      if (cli::is_ansi_tty()) {
        dpm_theme[[op]](text)
      } else if (op == "INSERT") {
        paste0("+|", text, "|+")
      } else if (op == "DELETE") {
        paste0("-|", text, "|-")
      } else if (op == "EQUAL") {
        text
      } else {
        stop("Unknow op: ", op, call. = FALSE)
      }
    }
  )
  text = paste(text, collapse="")
  
  cli::cat_line(text)
}