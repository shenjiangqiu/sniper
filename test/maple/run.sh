files1='size_4_4_4_i0418_r8.cnf eqsparcl10bpwtrc10.cnf eqspdtlf14bpwtrc14.cnf'
files5='size_5_5_5_i003_r12.cnf sha1r17m148ABCD_p.cnf eqspwtrc16bparrc16.cnf'
files2='Haystacks-ext-12_c18.cnf sha1r17m72a.cnf sha1r17m145ABCD.cnf toughsat_23bits_0.cnf toughsat_25bits_1.cnf Trivium_no_init_out350_known_last142_1.cnf'
files3='toughsat_28bits_0.cnf ASG_96_len112_known_last12_2.cnf toughsat_30bits_0.cnf Grain_no_init_ver1_out200_known_last104_0.cnf MM-23-2-2-2-2-3.cnf '
files4='Bibd-sc-10-03-08_c18.cnf QuasiGroup-4-12_c18.cnf b1904P3-8x8c11h0SAT.cnf b1904P1-8x8c6h5SAT.cnf'
for file in $files1;do
    rm -rf $file.fix $file.unfix
    mkdir $file.fix $file.unfix
    cd $file.fix;
    /home/sjq/git/sniper/run-sniper --roi --no-cache-warming  -n 1 -v -s fixaddress  -- /home/sjq/git/sniper/test/maple/glucose_release /home/sjq/git/sniper/test/maple/cnfs/$file  |head -n1000 > result.txt&
    cd ..;
    cd $file.unfix;
    /home/sjq/git/sniper/run-sniper --roi --no-cache-warming  -n 1 -v   -- /home/sjq/git/sniper/test/maple/glucose_release /home/sjq/git/sniper/test/maple/cnfs/$file |head -n1000 > result.txt&
    cd ..;
done

