 
kompilator=g++
standard=-std=c++14
optymalizacja=-O3
# optymalizacja=
# debug=-g
debug=
mem=../../memory-leaks

__ : main
	./main   
	   	   
main : main.o debug_new.o static_mem_pool.o mem_pool_base.o bool_array.o static_mem_pool.o
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ 
	            
main.o : main.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 

debug_new.o : $(mem)/debug_new.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 
	
static_mem_pool.o : $(mem)/static_mem_pool.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

mem_pool_base.o : $(mem)/mem_pool_base.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

bool_array.o : $(mem)/bool_array.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

 	
	
clear :
	rm *.o
	rm main	
	
	
doxy : 
	doxygen Doxyfile	
	

