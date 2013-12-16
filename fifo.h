my_bool fifo_create_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *fifo_create(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void fifo_create_deinit(UDF_INIT *initid);

my_bool fifo_remove_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *fifo_remove(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void fifo_remove_deinit(UDF_INIT *initid);

my_bool fifo_read_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *fifo_read(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void fifo_read_deinit(UDF_INIT *initid);

my_bool fifo_write_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *fifo_write(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void fifo_write_deinit(UDF_INIT *initid);

char* concat(const char* str1, const char* str2)
{
    char* res;
    asprintf(&res, "%s%s", str1, str2);
    return res;
}

char * read_fifo(char * path)  
{  
    int fd;
    char buf[8];
	char *result="";
    /* open, read, and display the message from the FIFO */
    fd = open(path, O_RDONLY);
    while( read(fd, buf, sizeof(buf)) > 0){
		result = concat(result,buf);
		memset(buf, 0, sizeof(buf));
	}
    //printf("Received: %s\n", buf);
    close(fd);
	
    return result; 
}  

int write_fifo(char * path, char * msg)  
{  
    int fd;
    /* write msg to the FIFO */
    fd = open(path, O_WRONLY);
	if (fd == -1) {
		return -1;
	}
    write(fd, msg, strlen(msg) );
    close(fd);
	return 0;
}
int create_fifo(char * path)
{
	/* create the FIFO (named pipe) */
    return mkfifo(path, 0660);
}
int remove_fifo(char *path)
{
	/* remove the FIFO */
    return unlink(path);
}