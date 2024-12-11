#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <error.h>
#include <string>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/stat.h>

const uint32_t MAX_BUFFER_SIZE = 4096;

/**
* Safe function for getting user input, with a default max size of 64
*
* If a user does not realize the max is 64 it may cause issues
*/
std::string getInput(const uint32_t maxBufferSize=UINT16_MAX)
{
    printf("Enter input (max %u) > ", maxBufferSize);
    char buffer[maxBufferSize];
    if(fgets(buffer, sizeof(buffer), stdin) == NULL)
        error(-1, 0, "fgets error");
    printf("\n");

    /// = = = = =  BUFFER OVERFLOW protection for obtaining user input

    // obtain pointer to the first occurance of newline character
    char * newline = strchr(buffer, '\n');
    if(newline)
    {
        // replace the newline character with a null terminator
        *newline = '\0';
    }
    else
    {
        // clear each character from stdin one by one
        int ch;
        while((ch = getchar()) != '\n' && ch != EOF);
    }
    /// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  
    
    return std::string(buffer);
}

// creates a file, writes a 32-bit value of 0 to the value and closes it
// on error, returns -1
// on success, returns 0
int createFile(const char * fname)
{
    // create new file with 0600 permissions
    int fd = open(fname, O_CREAT | O_RDWR, 0600);
    if(fd < 0)
    {
        error(-1, 0, "could not create file");
    }
    return fd;
}


// returns file descriptor
int openOrCreateFile(const char * fileName)
{
    int fd = open(fileName, O_RDWR);
    // problem with open call
    if(fd < 0) 
    {
        // check if file exists or not, if it exists then an error occured
        if(access(fileName, F_OK) == 0)
        {
            error(-1, 0, "could not open file");
        }

        // file doesn't exist, create it
        fd = createFile(fileName);
    }

    return fd;
}


// writes 32 bit integer in little endian format to a file
void writeToFile(const int fd, const char * data)
{
    // write bytes starting from least signifcant to most significant because of the way the buffer is set up
    ssize_t bytesWritten = write(fd, data, strlen(data));
    
    if(static_cast<size_t>(bytesWritten) != strlen(data))
    {
        if(bytesWritten < 0)
        {
            error(-1, 0, "could not write to the file");
        }
        
        error(-1, 0, "wrong number of bytes written");
    }
}

// close file descriptor, but check the error output and report it
void closeFile(const int fd)
{
    // attemept to close the file and report any errors
    int res = close(fd);
    if(res < 0)
    {
        error(-1, 0, "problem while closing the file"); 
    }
}


int main(int arc, char *argv[])
{
    char * logData;
    char * fileName;

    logData = (char *) malloc(sizeof(char) * MAX_BUFFER_SIZE);
    if(!logData)
    {
        error(-1, 0, "userInput malloc");
    }

    fileName = (char *) malloc(sizeof(char) * MAX_BUFFER_SIZE);
    if(!fileName)
    {
        error(-1, 0, "fileName malloc");
    }

    // get current time
    std::time_t now = std::time(0);
    struct tm* t = std::localtime(&now);
    
    // format date into fileName
    std::strftime(fileName, sizeof(char) * MAX_BUFFER_SIZE, "LOG_FILE_%Y-%m-%d_%H:%M:%S.log", t);
    // fileName = std::ctime(&now);

    strcpy(logData, getInput().c_str()); 
    

    int fd = openOrCreateFile(fileName);
    writeToFile(fd, logData);
    // change log file to be read only
    fchmod(fd, S_IRUSR | S_IRGRP | S_IROTH);
    closeFile(fd);

    return 0;
}

