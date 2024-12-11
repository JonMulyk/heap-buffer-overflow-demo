# heap-buffer-overflow-demo

## Usage:
1. navigate to the folder with the code: `cd vulnerable`
2. compile the code: `make`
3. Run the program:
  * `./logger`
  * `<program output> | ./logger`

## Exploit:
1. `./exploit1.py | ./logger`


## Description:
This basic program creates log files that are named with the exact time and date when the log program runs. The program accepts either user input or input being piped into it. Furtheremore, it will write the data to the log file and then it will set the permissions on the file to be read only. This is to ensure that the logged data is not modified, as it will act as true a record of the data given to it. 

## Overflow:
The program is designed specifically to demonstrate a heap-based buffer overflow and a potential danger of these overflows. Both the data being written to the log file and the log file name itself are allocated on the heap via malloc (in that specific order). The function that obtains the input data has a default max size of `UINT16_MAX = 0xFFFF = 65,535`. However, the size that is used for the malloc is only set to 4096, which is significantly less than the max size of the input function. Therefore, if the input function is used without changing the default max size, then an overflow can occur after 4096+x bits (where x is the distance on the heap between the data and the next object on the heap). Since the data is malloc'd first and then the fileName is malloc'd right after, when the data buffer gets overflowed it will start writing into fileName memory. Therefore, the user of the program is able to change the file name as desired, and can create new files or overwrite exisitng ones. 

## Exploit1.py:
`Exploit1.py` takes advantage of this heap-based buffer overflow and demonstrates an example of what you can do with it. It will output `4112` A's and then the name of the desired file, in this case `newFile.txt`. The exact number of bytes to write before the file name was found using gdb. Finding it systematically when the program is compiled with the `-g` involves setting a break point right after the malloc of the file name. Afterwards, we can run `info locals` for the variable names, then `print logData` and print `print fileName`. With that we have the memory addresses and we can find the amount of bytes between them by subtracting them: `print 0x<fileName memory> - 0x<logData memory>`. This will output `0x1010 = 4112`. 
