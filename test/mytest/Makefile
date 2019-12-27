CPPFLAGS+=-I/home/sjq/git/sniper/include
test.out:test.o
	g++ -I/home/sjq/git/sniper/include -o test.out test.o
run:test.out
	../../run-sniper -n 1 -- ./test.out

run-fixaddress:test.out
	../../run-sniper -n 1 -v -s fixaddress  -- ./test.out
