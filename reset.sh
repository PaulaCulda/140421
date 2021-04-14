while read line 
do
   ONE=`echo $line | cut -d'_' -f1`
   TWO=`echo $line | cut -d'_' -f2`

  rm ${ONE}_rata_${TWO}.txt
  rm ${ONE}_putere_${TWO}.txt
  rm ${ONE}_dup_${TWO}.txt

done < toate_testele.txt

rm aux.txt
rm rezultate_partiale.txt
rm rezultate_finale.txt
rm nr_deja_reluate.txt
rm se_tsteaza_acum.txt
rm toate_testele.txt
rm nr_retestari.txt
