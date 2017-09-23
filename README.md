# CS211-Dictionary-Statistics-Generator
Parse string inputs from files and compare against a dictionary to generate statistics.

FIRST FOLDER FILE README: 
For the first part of this assignment, I chose to implement the Trie data structure. This structure is the most ideal for a 'dictionary'-esque program. 

Using this structure, I read the lines of the dictionary file, parsed out the unique words, and inserted them into the Trie structure. Afterwards, I repeated the process using the data file, and traversed the Trie, updating the prefix and occurrence fields as applicable. In order to print, I traversed the Trie once more, adding the individual characters to a "word" character array. When I reached a point that was marked as the end of an individual dictionary word, I output the "word" array and its corresponding prefix and occurrence statistics.

The worst-case time complexity to build (insert()) the Trie is O(m*k), where m is the number of string entries, and k is the length of the string entries. This is the same complexity for the matchStr(), printResultHelper(), and freeAllNodes() functions as well.

Reading the dictionary and data files takes linear O(n) time, where n is the number of characters in the file as each character has to be examined.

The drawback to using a Trie is the memory requirement, since, in my implementation, each node will have 26 children - one for each letter in the alphabet. 

While completing this project, I ran into an issue where the inclusion of a printf() statement would make my program run correctly (a bit too slow for cases 14-17), and its removal would cause the program to break. Upon some research, I learned this was due to the synchronization of threads in C, a very interesting topic I had not known about prior to this assignment. However, I was not able to figure out how to resolve this issue.

SECOND FOLDER FILE README:
See readme.pdf file for part 1 for in-depth detail.

Essentially, the only changes I made from part 1 to part 2 was in the matchStr() function. Instead of checking to see if the word from the dictionary file was a prefix of the word from the data file, I reversed it.

Unfortunately, I did not have enough time to properly attempt this program, so only the early testcases work properly.
