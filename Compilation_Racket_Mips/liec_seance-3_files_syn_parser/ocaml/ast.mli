type expr =
  And of expr * expr
| Or of expr * expr
| Not of expr
| Bit of bool
