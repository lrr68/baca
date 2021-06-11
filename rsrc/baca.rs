use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use std::env;

use lang;
use synan;
use symtable;
use baca;
use lexan;

/* TYPES */
enum BacaErr {
	ER_LEX_EOF,
	ER_LEX_UNID,
	ER_SYN_NE,
}

/* GLOBAL VARIABLES */
const in_file;      /* input file      */
const in_file_name; /* input file name */
BacaErr baca_err;   /* error code      */

/* FUNCTION DEFINITIONS */
fn
baca_abort()
{
	match baca_err {
		ER_LEX_UNID => println!("Character not expected at line {}, col {}", line, column),
		ER_LEX_EOF => println!("Unexpected EOF at line {}", line),
		ER_SYN_NE => println!("Token [%s] not expected at line {}, col {}", lexreg.lex, line, column),
	}

	exit(-(baca_err));
}

fn
start_baca()
{
}

fn
help()
{
	println!("baca [-h] [-i]");
	println!("     -h print this help text and exit");
	println!("     -i interpret file");
	println!("     -  interpret from stdin");
}

fn
main()
{
	let mut open_file: bool = false;
	let mut interactive: bool = true;

    let args: Vec<String> = env::args().collect();

	/* TODO: treat - to interpret from stdin */
	for arg in args.iter() {
		match  {
			'h' =>
				interactive = false;
				help();
				return 0,
			'i' =>
				open_file = 1;
				interactive = 0;
				in_file_name = optarg,
			'?' =>
				interactive = 0;
				if (optopt == 'i')
					printf("No file specified\n");
				else
					help();
			_   =>
				interactive = 0;
				help();
				return 0;
		}
	}

	/* initialize symbol table */
	init_table();
	/* initialize the lexical register */
	init_lexreg();

	/* interactive mode */
	if interactive {
		start_baca();
		return 0;
	}

	/* non interactive mode */
	if open_file {
		if (in_file = fopen(in_file_name, "r")) == () {
			fprintf(stderr, "Error opening file at %s: %s\n", in_file_name, strerror(errno));
			exit(-errno);
		}
	} else {
		in_file = stdin;
	}

	start_synan();

	return 0;
}
