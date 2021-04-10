#' @exportS3Method
print.diff_df = function(x, ...) {
  text = purrr::pmap_chr(
    x,
    function(text, op) {
      if (op == "EQUAL") {
        cli::col_grey(text)
      } else if (op == "INSERT") {
        cli::bg_green(text)
      } else if (op == "DELETE") {
        cli::style_strikethrough(cli::bg_red(text)) 
      }
    }
  )
  text = paste(text, collapse="")
  
  cli::cat_line(text)
}