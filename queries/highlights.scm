(identifier) @variable

((identifier) @type
  (#match? @type "^T[A-Z][A-Za-z0-9_]*$"))

(keyword) @keyword

(builtin_type) @type.builtin

(boolean) @boolean

(null) @constant.builtin

(number) @number

[
  (string)
  (multiline_string)
] @string

(escape_sequence) @string.escape

[
  (comment)
  (block_comment)
] @comment

(preprocessor) @keyword.directive

(operator) @operator

(punctuation) @punctuation.delimiter

[
  "("
  ")"
  "["
  "]"
  "{"
  "}"
] @punctuation.bracket

";" @punctuation.delimiter

[
  (type_definition
    name: (identifier) @type)
  (struct_definition
    name: (identifier) @type)
  (interface_definition
    name: (identifier) @type)
  (enum_definition
    name: (identifier) @type)
]

[
  (function_definition
    name: (identifier) @function)
  (method_definition
    name: (identifier) @function.method)
  (abstract_function
    name: (identifier) @function)
  (abstract_method
    name: (identifier) @function.method)
  (function_signature
    name: (identifier) @function)
  (method_signature
    name: (identifier) @function.method)
]

(variable_declaration
  storage: (keyword) @_storage
  name: (identifier) @constant
  (#match? @_storage "^[Cc][Oo][Nn][Ss][Tt]$"))
