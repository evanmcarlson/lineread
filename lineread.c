#include <unistd.h>
#include <errno.h>
#include <stdio.h>
// strncat
#include <string.h>

// uses read() to read files line by line (seperated by a \n newline character)
ssize_t lineread(int fd, char *buf, size_t sz) {

	ssize_t bytes_read = 0;
	char *ch;

	while(bytes_read < sz) {
		// read one character from file
		int status = read(fd, ch, 1);

		if(status != 0 && *ch != '\n') { // not EOF and not a newline
			strcat(buf, ch);
			bytes_read++;
		}
		else if(bytes_read == 0 && *ch =='\n') { // newline bytes get their own system call
			strcat(buf, ch);
			bytes_read++; // this should always result to 1
			break;
		}
		else if(*ch == '\n') { // indicates that bytes_read > 0
			break;
		}
		else if(status == 0 || status == -1) { // EOF or error codes return nonzero
			return 1;
		}
	}

	return bytes_read;
}