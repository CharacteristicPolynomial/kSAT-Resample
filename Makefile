all:
	g++ allresampling.cpp -o allre
	g++ generator.cpp -o gen
	g++ misresampling.cpp -o misre
	
clean:
	rm allre gen misre
