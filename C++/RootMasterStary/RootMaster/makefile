
 
kompilator=g++
standard=-std=c++14
optymalizacja=-O3
# optymalizacja=
# debug=-g
debug=
profilowanie=-pg
dane=dat


__ : main
	./main  -i $(dane)/dane -o $(dane)/wyjscie 
	            
main : RootMaster.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ 
		
	
 
	
	
	

