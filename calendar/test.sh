g++ ./main.cpp -o main 

cat ./shanghaitech/$1.in | ./main > a.out
cat ./shanghaitech/$1.out > b.out
diff a.out b.out
