# バカ(Baca) language specifications

Baca (Basic calculator) is an interpreter for a calculator focused language. It's main goals are to provide a easy to use and familiar calculator.
To be familiar the syntax borrows commands from c and python, aimming to type less and offering multiple syntaxes for some commands.
Since the goal is to be a calculator, operations like power, factorial and termial have exclusive tokens, so it doesn't require a explicit function call to use them.

This program follows the [suckless](https://suckless.org) philosofy and coding style.
This program is licensed under the GNU GPL3 license.

### Description:

This language is case-sensitive so myvariable and MYVARIABLE and all other case variations are different objects.

Ids can start with letters or a underscore character, after the first character it may contain letters, numbers and underscores. It can not be composed only by underscores.

Literal values can be typed as integers, floating point (left zero may be omited), hexadecimal (0x...), binary(0b...), octal(0o...) or duodecimal(0d...). These last 4 types only support integers currently. Literals typed as 0x, 0b, 0o and 0d are treated as 0. Strings must be enclosed in double quotes while a single character must be enclosed in single quotes, although a string containing only one character is allowed.

Duodecimal values dec and el are represented by the letters D and E respectivelly.

Although types do not have to be specified you can specify a type to a constant.

Aside the boolean type bool, all other types can be checked for true or false. For numerical values, 0 is false, different of 0 is true. For string values, a empty string ("") is considered false and anything else is true.

#### Operations:
+ Sum: defined for numerical types as the mathematical sum, defined to strings as concatenation.
+ Subtraction: defined for numerical types as the mathematical subtraction, undefined to strings.
+ Multiplication: defined for numerical types as the mathematical multiplication, defined to strings as a series of concatenations of that string to itself.
+ Division: defined for numerical types as the mathematical division, undefined to strings.
+ Factorial: defined for numerical types as the mathematical factorial, undefined to strings.
+ Termial: defined for numerical types as termial(x) = x + termial(x-1), undefined to strings.

### Program:
By default baca will go into interactive mode. If a file is passed as a argument, baca will interpret that file. If a single '-' is passed as a argument, baca will interpret input from stdin.

## Tokens:
The values on the right are reserved words.

<pre>
id       | (\_+\[a-z0-9\]([a-z0-9] U \_)\*) U ([a-z])([a-z0-9] U \_)\*
literal  | ([0-9]\*\\.?[0-9]+) U 0x[abcdefABCDEF0-9]\* U 0b[01]\* U 0o[0-8]\* U 0d[0-9DEde]\* U ".[0-9]\*"
constw   | 'const'
int      | 'int'
char     | 'char'
string   | 'string'
double   | 'double'
bool     | 'bool'
def      | 'def'
return   | 'return'
semico   | ';'
period   | '.'
plus_e   | '+='
minus_e  | '-='
slash_e  | '/='
times_e  | '\*='
d_plus   | '++'
d_minus  | '--'
plus     | '+'
minus    | '-'
times    | '\*'
slash    | '/'
b_slash  | '\\'
mod      | '%'
power    | '\*\*'
facto    | '!'
termial  | '?'
equals   | ':=' | '='
diff      | '!=' | '<>'
bigger   | '>'
big_eq   | '>='
smaller  | '<'
sml_eq   | '<='
not      | 'not'
and      | '&&' | 'and'
or       | '||' | 'or'
b_and    | '&'
b_or     | '|'
equality | '=='
o_brack  | '('
c_brack  | ')'
o_curly  | '{'
c_curly  | '}'
o_brace  | '['
c_brace  | ']'
while    | 'while'
for      | 'for'
do       | 'do'
if       | 'if'
then     | 'then'
else     | 'else'
elseif   | 'elif'
read     | 'read' | 'input'
print    | 'print' | 'write'
in       | 'in'
</pre>

## Grammar
The language allows for declarations anywhere on the code. Like C, every command is a expression evaluated to the value of the left side by the end of the command.
++id and --id, are evaluated to the increased or decreased value of id, while id++ and id-- are evaluated to the value of id and then the command occurs.

TODO: make a built in sum command (that greek E)
TODO: builtin avg, mean
TODO: arrays (multidimensional too)
TODO: built in 'in' function to check if element is inside array or string

+ S     -> {decl | comm | def}
+ comm  -> (exprs | loopf | loopw | loopd | test | read | print | plus | minus) _';'_

+ type  -> _'int'_ | _'double'_ | _'string'_ | _'char'_ | _'bool'_ | _'void'_

+ def   -> _'def'_ type id _'('_ idlis _') {'_ {comm}+ [retr] _'}'_
+ idlis -> id_a {_','_ id_a}
+ retr  -> _'return'_ exprs _';'_

+ id_a  -> id { _'['_ exprs _']'_ }
+ decl  -> \[ _'const'_\] type id_a [ ( _':='_ | _'='_ ) exprs ] _';'_

+ id_op -> id_a ( call | attr | arit)
+ fcall -> _'('_ lexpr _')'_
+ attr  -> (_':='_ | _'='_) exprs _';'_
+ arit  -> (spops exprs | _'++'_ | _'--'_) _';'_
+ spops -> _'+='_ | _'-='_ | _'/='_ | _'\*='_

+ plus  -> _'++'_ id_a
+ minus -> _'--'_ id_a

+ loopf -> _'for'_ ((attr | id_a) _'to'_ exprs _'step'_ exprs | _'('_ [attr] _';'_ exprs _';'_ exprs _')'_ ) (comm | _'{'_ {comm} _'}'_)
+ loopw -> _'while'_ exprs (comm | _'{'_ {comm} _'}'_)
+ loopd -> _'do'_ (comm | _'{'_ {comm} _'}'_) _'while'_ exprs _';'_

+ test  -> _'if'_ exprs \[_'then'_\] (comm | _'{'_ {comm} _'}'_) {elif} \[telse\]
+ elif  -> _'elif'_ exprs (comm | _'{'_ {comm} _'}'_)
+ telse -> _'else'_ (test | (comm | _'{'_ {comm} _'}'_))

+ exprs -> expr1 [ rel expr2 ]
+ expr  -> [_'-'_ | _'not'_] term1 {( _'+'_ | _'-'_ | _'|'_ | _'||'_ | _'or'_ ) term2}
+ term  -> fact1 {( _'**'_ | _'*'_ | _'/'_ | _'%'_ | _'&'_ | _'&&'_ | _'and'_) fact2} [ _'!'_ ]
+ fact  -> (_'('_ exprs _')'_ | literal | id_a | plus | minus | id_op) [ _'?'_ ]
+ rel   -> _'=='_ | _'!='_ | _'<>'_ | _'>'_ | _'<'_ | _'>='_ | _'<='_

+ lexpr -> exprs {, exprs}

## Future features:
The following is a list of features that i would like to have on baca.

+ Trigonometrical functions.
+ Other data types like long, short and float.
+ Support floting point on all data types.
+ Add important mathematical constants like e and PI.

And if you feel like contributing, the following is a list of features that might be usefull but i do not plan on implementing.

+ Calculus functions (integrals, etc)
