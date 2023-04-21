
whack: whack_a_mole.c
	gcc $< -lcrypto -o $@

.PHONY: clean
clean: 
	rm -f whack
