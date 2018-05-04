/**
 * Create a main function that takes command line arguments.
 * - This program opens two files (paths provided on the command line) and
 *   combines the two files one line at a time into one output.
 * - The first file provided is a line of text. Remove any trailing white-space
 *   from the end of the its line (white-space includes newlines (\n), tabs (\t)
 *   and spaces ( ).
 * - The second file is a list of numbers, each of which you must add one to
 *   when printing to the output.
 * - The two columns should be separated by a tab character.
 * 
 * To do this, open filea and fileb at the same time.  Use fgets(3) to read from
 * filea and fscanf(3) to read from fileb at the same time.  Stop if either
 * filea or fileb runs out of input.
 *
 * Example input/output:
 * ./h3 test/h3-testa test/h3-testb 
 * Test A  11
 * Test B  51
 * Test C  91
 * Test D  26
 * Test E  17
 * Test F  76
 */

