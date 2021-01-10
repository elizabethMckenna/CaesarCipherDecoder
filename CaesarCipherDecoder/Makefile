all:  copyrecords add_letters.o create_freq_table.o letter_count.o frequency_table offset.o convertChar.o chi_sq.o decode_shift.o decode

copyrecords: copyrecords.c A3lib.h add_letters.o letter_count.o decode_shift.o chi_sq.o offset.o create_freq_table.o convertChar.o
	gcc -ansi -Wall copyrecords.c -o copyrecords add_letters.o letter_count.o decode_shift.o chi_sq.o offset.o create_freq_table.o convertChar.o

decode: decode.c A3lib.h letter_count.o add_letters.o offset.o create_freq_table.o convertChar.o chi_sq.o decode_shift.o
	gcc -ansi -Wall decode.c -o decode letter_count.o add_letters.o offset.o create_freq_table.o convertChar.o chi_sq.o decode_shift.o

decode_shift.o: decode_shift.c A3lib.h
	gcc -ansi -Wall -c decode_shift.c

chi_sq.o: chi_sq.c  A3lib.h
	gcc -ansi -Wall -c chi_sq.c

convertChar.o: convertChar.c
		gcc -ansi -Wall -c convertChar.c

offset.o: offset.c
	gcc -ansi -Wall -c offset.c

frequency_table: frequency_table.c A3lib.h add_letters.o create_freq_table.o letter_count.o
		gcc -ansi -Wall frequency_table.c -o frequency_table add_letters.o create_freq_table.o letter_count.o

add_letters.o: add_letters.c
		gcc -ansi -Wall -c add_letters.c

create_freq_table.o: create_freq_table.c
		gcc -ansi -Wall -c create_freq_table.c

letter_count.o: letter_count.c
		gcc -ansi -Wall -c letter_count.c

clean:
	rm copyrecords letter_count.o create_freq_table.o add_letters.o frequency_table offset.o convertChar.o chi_sq.o decode_shift.o decode
