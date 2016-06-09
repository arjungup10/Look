clear
gcc -Wall -Werror -O3 Look.c -o Look

rm -rf LookTest
mkdir LookTest

cd LookTest
cp ../Look .
cp ../dict .
cp ../z.txt .

echo "---Start Tests---"

echo "---Default Dictionary Tests---"
echo
echo "---Test1: Basic Look---"
echo "./Look look"
./Look look > myOut1
look look > exOut1
diff myOut1 exOut1
echo

echo "---Test1.1: Basic Look---"
echo "./Look 10"
./Look 10 > myOut1.1
look 10 > exOut1.1
diff myOut1.1 exOut1.1
echo

echo "---Test2: Case Sensitivity---"
echo "./Look HEllo"
./Look HEllo > myOut2
look HEllo > exOut2
diff myOut2 exOut2
echo

echo "---Test3: nonAlphanumerics---"
echo "./Look W---Or!l#$%d"
./Look W---Or!l#$%d > myOut3
look W---Or!l#$%d > exOut3
diff myOut3 exOut3
echo

echo "---Test4: No Args Given---"
echo "./Look"
./Look > myOut4 2> myOut4
look > exOut4 2> exOut4
diff myOut4 exOut4
echo

echo "---Test5: Bad Flag---"
echo "./Look -! Hello"
./Look -! Hello > myOut5 2> myOut5
look -! Hello > exOut5 2> exOut5
diff myOut5 exOut5
echo

echo "---Test6: Only Flags---"
echo "./Look -d -f"
./Look -d -f > myOut6 2> myOut6
look -d -f > exOut6 2> exOut6
diff myOut6 exOut6
echo

echo "---Test7: -t Flag---"
echo "./Look -t k Looker"
./Look -t k Looker > myOut7 2> myOut7
look -t k Looker > exOut7 2> exOut7
diff myOut7 exOut7
echo

echo "---Test8: -t Flag (missing char)---"
echo "./Look -t Looker"
./Look -t Looker > myOut8 2> myOut8
look -t Looker > exOut8 2> exOut8
diff myOut8 exOut8
echo

echo "---Test9: -t Flag (char not in String)---"
echo "./Look -t b Looker"
./Look -t b Looker > myOut9 2> myOut9
look -t b Looker > exOut9 2> exOut9
diff myOut9 exOut9
echo

echo "---Test10: -t Flag (char is not alphanumeric)---"
echo "./Look -t + Look+er"
./Look -t + Look+er > myOut10 2> myOut10
look -t + Look+er > exOut10 2> exOut10
diff myOut10 exOut10
echo

echo "---User Dictionary Tests---"
echo
echo "---Test1: Basic Look---"
echo "./Look look dict"
./Look look dict > myOut1
look look dict > exOut1
diff myOut1 exOut1
echo

echo "---Test2: Case Sensitivity---"
echo "./Look HEllo dict"
./Look HEllo dict > myOut2
look HEllo dict > exOut2
diff myOut2 exOut2
echo

echo "---Test3: nonAlphanumerics---"
echo "./Look W---Or!l#$%d dict"
./Look W---Or!l#$%d dict > myOut3
look W---Or!l#$%d dict > exOut3
diff myOut3 exOut3
echo

echo "---Test4: No Args Given---"
echo "./Look dict"
./Look dict > myOut4 2> myOut4
look dict > exOut4 2> exOut4
diff myOut4 exOut4
echo

echo "---Test5: Bad Flag---"
echo "./Look -! Hello dict"
./Look -! Hello dict > myOut5 2> myOut5
look -! Hello dict > exOut5 2> exOut5
diff myOut5 exOut5
echo

echo "---Test6: Only Flags---"
echo "./Look -d -f dict"
./Look -d -f dict > myOut6 2> myOut6
look -d -f dict > exOut6 2> exOut6
diff myOut6 exOut6
echo

echo "---Test7: -t Flag---"
echo "./Look -t k Looker dict"
./Look -t k Looker dict > myOut7 2> myOut7
look -t k Looker dict > exOut7 2> exOut7
diff myOut7 exOut7
echo

echo "---Test8: -t Flag (missing char)---"
echo "./Look -t Looker dict"
./Look -t Looker dict > myOut8 2> myOut8
look -t Looker dict > exOut8 2> exOut8
diff myOut8 exOut8
echo

echo "---Test9: -t Flag (char not in String)---"
echo "./Look -t b Looker dict"
./Look -t b Looker dict > myOut9 2> myOut9
look -t b Looker dict > exOut9 2> exOut9
diff myOut9 exOut9
echo

echo "---Test10: -t Flag (char is not alphanumeric)---"
echo "./Look -t + Look+er dict"
./Look -t + Look+er dict > myOut10 2> myOut10
look -t + Look+er dict > exOut10 2> exOut10
diff myOut10 exOut10
echo

echo "---User Input Tests---"
echo

echo "---Test1: Word---"
echo "./Look The z.txt"
./Look The -d -f z.txt > myOut1
look The -d -f z.txt > exOut1
diff myOut1 exOut1
echo

echo "---Test2: Letter---"
echo "./Look A z.txt"
./Look A z.txt > myOut2
look A z.txt > exOut2
diff myOut2 exOut2
echo

echo "---Test3: Word Not Present---"
echo "./Look Maw z.txt"
./Look Maw z.txt > myOut3
look Maw z.txt > exOut3
diff myOut3 exOut3
echo

cd ..
echo
echo "---All Test End---"
