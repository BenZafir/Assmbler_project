assembler: assembler.c auxiliary_functions.o constants_table.o error_and_worning_printer.o first_pass.o input_data_base.o line_break_down.o line_syntactic_analysis.o output_printer.o program_counters.o second_pass.o symbol_table.o header.h
	gcc -g -ansi -Wall -pedantic assembler.c auxiliary_functions.o constants_table.o error_and_worning_printer.o first_pass.o input_data_base.o line_break_down.o line_syntactic_analysis.o output_printer.o program_counters.o second_pass.o symbol_table.o -o assembler


auxiliary_functions: auxiliary_functions.c header.h
	gcc -c -ansi -Wall -pedantic auxiliary_functions.c -o auxiliary_functions
constants_table: constants_table.c header.h
	gcc -c -ansi -Wall -pedantic constants_table.c -o constants_table
error_and_worning_printer: error_and_worning_printer.c header.h
	gcc -c -ansi -Wall -pedantic error_and_worning_printer.c -o error_and_worning_printer
first_pass: first_pass.c header.h
	gcc -c -ansi -Wall -pedantic first_pass.c -o first_pass
input_data_base: input_data_base.c header.h
	gcc -c -ansi -Wall -pedantic input_data_base.c -o input_data_base
line_break_down: line_break_down.c header.h
	gcc -c -ansi -Wall -pedantic line_break_down.c -o line_break_down
line_syntactic_analysis: line_syntactic_analysis.c header.h
	gcc -c -ansi -Wall -pedantic line_syntactic_analysis.c -o line_syntactic_analysis
output_printer: output_printer.c header.h
	gcc -c -ansi -Wall -pedantic output_printer.c -o output_printer
program_counters: program_counters.c header.h
	gcc -c -ansi -Wall -pedantic program_counters.c -o program_counters
second_pass: second_pass.c header.h
	gcc -c -ansi -Wall -pedantic second_pass.c -o second_pass
symbol_table: symbol_table.c header.h
	gcc -c -ansi -Wall -pedantic symbol_table.c -o symbol_table




