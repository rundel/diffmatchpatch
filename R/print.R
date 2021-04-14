dpm_theme = list(
  "EQUAL"  = function(x) { x },
  "INSERT" = function(x) { cli::style_inverse(cli::style_bold(cli::col_green(x))) },
  "DELETE" = function(x) { cli::style_inverse(cli::style_bold(cli::col_red(x))) }
)

supports_ansi = function() {
  cli::num_ansi_colors() > 1
}

#' @exportS3Method
as.character.diff_df = function(x, use_ansi = supports_ansi(), theme = dpm_theme, ...) {
  if (nrow(x) == 0)
    return("")
  
  
  text = apply(
    x, 1,
    function(row) {
      text = row[1]
      op = row[2]
      if (use_ansi) {
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
  
  paste(text, collapse="")
}

#' @exportS3Method
print.diff_df = function(x, ...) {
  cli::cat_line(as.character(x, ...))
}