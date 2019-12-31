CPPFLAGS+=-I/home/sjq/git/sniper/include -O0 -g
test.out:test.o
	g++ -I/home/sjq/git/sniper/include -o test.out test.o
run:test.out
	../../run-sniper -n 1 -- ./test.out

run-fixaddress:glucose_release
	../../run-sniper --roi --no-cache-warming -n 1 -v -s fixaddress  -- ./glucose_release ./cnfs/sha1r17m145ABCD.cnf
