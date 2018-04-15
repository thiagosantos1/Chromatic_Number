/* 5 points */

/**
 * This function prints the file type:
 * '-' for a regular file	'd' for a directory	'b' for a block special
 * 'c' for a character special	'p' for a FIFO(pipe)	'l' for a symbolic link
 * 's' for a socket		'?' for anything else
 * The file type is encoded in the st_mode member of the stat structure
 */
void printtype(struct stat *st)
{

}

/**
 * This prints the permissions for the file or directory in 'ls' format, i.e.:
 *   rwxrwxrwx
 */
void printperm(mode_t mode)
{

}

/**
 * Prints the uid or username.  Use getpwuid() to get the username from the uid.
 * If the user is not found, just print the uid.  Format usernames or uids to
 * 8 characters in width.
 */
void printuser(uid_t uid)
{

}

/**
 * Prints the gid or group name. Use getgrgid() to get the group name from the gid.
 * If the group is not found, just print the gid.  Format groupnames or gids to
 * 8 characters in width.
 */
void printgroup(gid_t gid)
{

}

/**
 * Prints the time (Mmm DD HH:MM YYYY).  Use localtime() to convert the time_t
 * value (gotten from the st.st_mtime field)
 */
void printtime(time_t t)
{

}

/**
 * This function lists a single file.  If the file cannot be stat()'ed, then
 * print that you cannot stat it (with the files name) and return.
 * Otherwise use the above functions to print all the information about the
 * file using the information from the stat() system call.
 * To use stat() given path and name, you must combine path and name into one
 * file path, use sprintf() into a character buffer to do this.
 * The order in which things should be printed, is:
 * 1) file-type 2) user permissions 3) group permissions 4) other permissions
 * 5) number of hard links 6) user-name/uid 7) group-name/gid 8) size in bytes
 * 9) last modification time 10) file-name
 * Just like with the ls command.
 */
void list(char *path, char *name)
{

}

/**
 * Use scandir() to read a list of files from the given directory path, sort
 * the files using the alphasort method. An example of how to use scandir() can
 * be found in its "man" page, which should be quite illuminating.
 */
void listdir(char *path)
{

}

/**
 * Main should use listdir on "." (the current directory) if no arguments are
 * given, otherwise use listdir on each argv[i], i >= 1
 */
int main(int argc, char *argv[])
{

}
