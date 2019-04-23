Class:		CS 530, Spring 2019
Project: 	Assignment #2
		Disassembler Program for XE variant of the SIC/XE family
Names:		Andrew Botros, 819505044, cssc0457
		Jan Domingo, 820092657, cssc0463
		Anthony Huynh, 819367270, cssc0458
Filename: 	README.txt
Files Included:	README.txt, sample.sym, sample.obj, header.h, main.c, Software Design Document, MakeFile
***********************************************************************************************************************************************
Compile Instructions: 
To compile and execute we used gcc soon.c -o soon -std=c99. This line builds an executable from the .c file and then creates an executable named after the "-o". 


Operating instructions(include any/all command line options/arguments, required inputs, etc):
We have several command line arguments. The first lies in argv[1] which is the name of the .obj file and then we have argv[2] which is the .sym file. Argc should be 3 in all scenarios, as this indicates that we have 3 arguments. These arguments are in order: program name objFile symFile. If we have less than 3 arguments then there isn't the correct amount of files. 


List/description of novel/significant design decisions:
We decided to parse the SymTable as a struct. At first it seemed like overkill but we slowly realized that a struct was the most effecient. We also created functions for each of the formats. We also decided to obviously code our project in C. Specifically C99 as it allowed more freedom with loops and variable declarations. 


List/description of any extra features/algorithms/functionality you included which were not required:
You'll notice in our code a heavy amount of strtol popping up. That's because although our characters were Hex characters it ASCII code. That's much different than the actual values that these characters represent. It was used every single time we needed to convert Hex ASCII to decimal values. This was used in every format instruction and even for the opCode.
For parsing the SymTab we used a struct. We  placed the label and its corresponding address into a struct. So any time we needed to calculate a TA we could look up the address and find it's corresponding label. This proved to be extremely useful as we didn't need to search the entire SymTab file and then somehow parse the address on that line.
We also created an OpTab which contains all the information Appendix A does. The opCode itself, the instruction and the format. By including the format in the opTab we could properly call our format functions and update our PC and LOCCTR. 

List/description of all known deficiencies or bugs:
Several times we had incorrect output when the code looked like it should’ve worked fine. Each of those times we saw that it was not null terminated properly or the size of the array was incorrect. There also another extremely frustrating issue. Sometimes our code in our own IDEs would give different output than what was on Edoras. Memory issues plagued us, it led to segmentation faults and errant output behavior. 
There was also the issue with structs. One of our functions is extremely large the fileParser. It proved to be extremely difficult to return a struct from a function and mallocs just created even more errors. Returning arrays in general for C is very tiresome as most things would need to be passed by reference and then a pointer grabs that data since the function destroys it before returning. 

Lessons Learned:
We learned very quickly that null terminating character arrays in C is absolutely essential. The misplacement of a null character or just a plain omission could result in your entire program messing up.
Passing in structs and arrays  into functions, and returning them is a complicated process. Many times we realized the importance of memory allocation and the importance and need for pointers. 
We also should've spent less time conceptualizing and more time actually working on the code. Many times we drew pictures and diagrams but none of it really compared to actually writing code. Although it is good to conceptualize and plan out before, like everything else in life, balance is required, 


