# heap-buffer-overflow-demo

## Usage:
Run this on the departmental linux servers (csx1-csx3)
1. navigate to the folder with the code: `cd vulnerable`
2. compile the code: `make`
3. Run the program:
  * `./logger`
  * `<program output> | ./logger`    ex: (`echo "Hello World!\n Example123" | ./logger`)

## Exploit:
`./exploit1.py | ./logger`
   
### Modifying the exploit: 
Change `payload += b"newFile.txt"` to `payload += b"<FILE NAME>"`


## Description:
This basic program takes user input from the command line or being piped from stdin, and generates a log file named with the timestamp when it was ran. It will set the permissions of the log file to be readable, but not writeable or executable to ensure that the logged data is not modified. Both the data being written to the log file and the log file name itself are allocated on the heap via malloc one after another. The data copied from the user input is significantly bigger than the log data buffer can hold. `Exploit1.py` takes advantage of this, and overflows the heap buffer. This will start overwriting the name of the file the program generates. This allows an attacker to generate their own files, or to overwrite exisitng files that the `logger` program has read/write access to.
