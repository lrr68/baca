# Scal language specifications

Scal (Simple calculator) is a interpreter for a calculator focused language. It's main goals are to provide a easy to use and familiar calculator.
To be familiar the syntax borrows commands from c and python, aimming to type less and offering multiple syntaxes for some commands.
Since the goal is to be a calculator, operations like power, factorial and termial have exclusive tokens, so it doesn't require a explicit function call to use them.

This program follows the [suckless](https://suckless.org) philosofy and coding style.
This program is licensed under the GNU GPL3 license.

## Tokens:
+ id       : TODO: ID REGEX
+ const    : TODO: CONST REGEX
+ d_plus   : '++'
+ d_minus  : '--'
+ plus     : '+'
+ minus    : '-'
+ times    : '\*'
+ slash    : '/'
+ b_slash  : '\\'
+ mod      : '%'
+ power    : '\*\*'
+ facto    : '!'
+ termial  : '?'
+ equals   : ':='
+ diff     : '!=' | '<>'
+ bigger   : '>'
+ big_eq   : '>='
+ smaller  : '<'
+ sml_eq   : '<='
+ not      : 'not'
+ and      : '&&' | 'and'
+ or       : '||' | 'or'
+ b_and    : '&'
+ b_or     : '|'
+ equality : '=='
+ while    : 'while'
+ for      : 'for'
+ do       : 'do'
+ if       : 'if'
+ then     : 'then'
+ else     : 'else'
+ elseif   : 'elif' | 'else if'
+ read     : 'read'
+ print    : 'print' | 'write'

## Grammar
TODO: add commands to print binary, octal, decimal, duodecimal, hexadecimal

+ S     -> {comm | exprs}
+ comm  -> exprs | arit | loopf | loopw | loopd | test | read | print | plus | minus | pow | fcto | term

+ attr  -> id ':=' exprs ';'
+ arit  -> id (spops exprs | '++' | '--') ';'
+ spops -> '+=' | '-=' | '/=' | '\*='
+ plus  -> '++' id
+ minus -> '--' id
+ pow   -> id '\*\*' exprs
+ fcto  -> id '!'
+ term  -> id '?'

+ loopf -> 'for' ((attr | id) 'to' exprs 'step' exprs | '(' [attr] ';' exprs ';' exprs ')' ) (comm | '{' {comm} '}')
+ loopw -> 'while' exprs (comm | '{' {comm} '}')
+ loopd -> 'do' (comm | '{' {comm} '}') 'while' exprs ';'

+ exprs -> expr1 [ rel expr2 ]
+ expr  -> [- | 'not'] term1 {( + | - | '|' | '||' | 'or' ) term2}
+ term  -> fact1 {( * | / | % | & | && | 'and' ) fact2}
+ fact  -> '(' exprs ')' | const | id | fcto | term | plus | minus | attr
+ rel   -> '==' | '!=' | '<>' | '>' | '<' | '>=' | '<='

## Future features:
The following is a list of features that i would like to have on Scal.

+ trigonometrical functions

And if you feel like contributing, the following is a list of features that might be usefull but i do not plan on implementing.

+ Calculus functions (integrals, etc)
