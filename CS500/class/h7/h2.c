/* 3 points */
/**
 * Create a program that creates a "hex-dump" of the data it reads either from
 * a file (if the name is given on the command line) or from stdin if no file-
 * name is given.  Each line should print up to 16 bytes of data (it may be less
 * if reading from stdin.) first as hexadecimal values followed by the ASCII
 * values (if it's a printable character (i.e. isgraph())), each line of data
 * should be preceded with its "offset" printed as a hex value.
 * 
 * Example input/output:
 * ./h2 test/testfile
 * 00000000 : 42 6F 62 0A 54 69 66 66  61 6E 79 0A 53 74 65 76 : Bob.Tiffany.Stev
 * 00000010 : 65 0A 4A 69 6D 0A 4C 75  63 79 0A 46 72 65 64 0A : e.Jim.Lucy.Fred.
 * 00000020 : 47 65 6F 72 67 65 0A 4A  69 6C 6C 0A 4D 61 78 0A : George.Jill.Max.
 * 00000030 : 42 75 74 74 65 72 73 0A  52 61 6E 64 79 0A 44 61 : Butters.Randy.Da
 * 00000040 : 76 65 0A 42 75 62 62 6C  65 73 0A                : ve.Bubbles.
 */

