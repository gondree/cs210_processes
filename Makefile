
whack: whack_a_mole.c
	gcc $< -lcrypto -o $@

clean: 
	rm -f whack
