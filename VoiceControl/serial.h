int openLine (const char *serialPort);
int writeToLine (int fd, const char *data, int len);
void closeLine (int fd);
