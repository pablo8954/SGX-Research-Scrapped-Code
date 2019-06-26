# SGX-Research
SGX-Research documents files and work related to SGX Research at Texas A&M. 

# research_timer.cpp
research_timer.cpp is a script which times function execution. Additionally, the 
script will also provide the average runtime and standard deviation as an output.
Currently, this file is incompatable with Graphene OS.  

# timer_remake.c
timer_remake.c serves the same purpose as the script research_timer. This file
can be executed using Graphene OS, however it has conficts with the Graphene OS makefile.
To circumvent this issue, run `gcc -o timer_remake timer_remake.c -lm` prior to running `SGX=1` and `SGX_RUN=1`.
