
(* The type of tokens. *)

type token = 
  | TOK
  | RULES
  | NT
  | IDENTIFIER of (string)
  | EOL
  | EOF
  | CODE of (string)
  | ARROW

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val main: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (string list * string list * (string * string list * string) list)
