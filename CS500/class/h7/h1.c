/* 2 points */
/**
 * Open /var/run/utmp and read utmp records out it (read: man 5 utmp), print
 * those records which are USER_PROCESS in a who/finger like format.
 * - If a file-name is given on the command line, open that instead.
 * - Get their real-name from the GECOS field using getpwnam() on the username.
 * - Functions you will likely need to complete this assignment:
 *   fopen()/fclose(), fread(), getpwnam(), strtok(), printf()
 * - Output is 15,15,7 and unlimited characters for each column with a space
 *   between each.
 * Example input/output:
 * ./h1 test/utmp
 * Login:          Name:           TTY:    Host:
 * cs20111         cs20111         pts/0   10.138.207.55
 * cs61716         Chuan Qi        pts/2   139.102.14.207
 * cs50004         Aditi V Kulkarn pts/4   98.157.235.98
 * ...
 */

