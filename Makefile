output: e2_1 e2_2 e2_3

e2_1:
	g++ -std=c++17 e2_1.cpp -o e2_1.x

e2_2:
	g++ -std=c++17 e2_2.cpp -o e2_2.x

e2_3:
	g++ -std=c++17 e2_3.cpp -o e2_3.x

clean:
	rm *.x