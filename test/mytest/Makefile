CPPFLAGS+=-I/home/sjq/git/sniper/include -O0 -g
test.out:test.o
	g++ -I/home/sjq/git/sniper/include -o test.out test.o
run:test.out
	../../run-sniper --roi --no-cache-warming -n 1 -- ./test.out

run-fixaddress:test.out
	../../run-sniper --roi --no-cache-warming -n 1 -v -s fixaddress  -- ./test.out
run-branchflag:test.out
	../../run-sniper --roi --no-cache-warming -n 1 -v -s branchflag  -- ./test.out
run-roipause:test.out
	../../run-sniper --roi --no-cache-warming -n 1 -v -s pauseroi  -- ./test.out
run-branchhit:test.out
	../../run-sniper --roi --no-cache-warming -n 1 -v -s branchflag  -s setbranchhit  -- ./test.out