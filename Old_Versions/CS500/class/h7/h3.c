/* 2 points */
/**
 * Create a program that when given a list of one or more user-names on the
 * command line, prints a finger like display of information about each user.
 * It should always print their Login, Name (Real name), Directory and Shell
 * fields. If the GECOS field is filled out then it should print as much as
 * possible of their Room (with office number if present) and Home (if present)
 * If their real-name is not set in the GECOS field, use (null).
 * 
 * - The following functions may be needed to complete this assignment:
 *   getpwnam(), strtok(), sprintf() and printf()
 * 
 * - Format of the GECOS field: Real name,Room,Office phone,Home phone,Other
 * 
 * Example input/output:
 * > ./h3 root nobody
 * Login: root                             Name: Bob Smith
 * Directory: /root                        Shell: /bin/tcsh
 * Office: RO A-125, x2138
 * 
 * Login: nobody                           Name: nobody
 * Directory: /u1                          Shell: /bin/tcsh
 * 
 */

