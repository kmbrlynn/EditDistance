/**********************************************************************
 *  readme template                                                   
 *  DNA Sequence Alignment
 **********************************************************************/

Name: Kim Douglas
Login:


Hours to complete assignment (optional):



/**********************************************************************
 *  Explain what you did to find the alignment itself.
 **********************************************************************/

I used C-style arrays, with pointers to the "current" square and each 
of its "neighboring" squares - right, diagonal, and bottom - in addition
to a flagging pointer that marks the recovered square as "chosen."

Inside a while-loop, there are 3 if-cases for each of the neighboring
squares. These detect (1) that it's in the bounds of the array, and
(2), that the difference between the current square's dereferenced value
and the neighboring square's dereferenced value is correctly evaluated
as either 0, 1, or 2.

If these tests succeed, the pointer to the "current" square assumes
the value of the pointer to the chosen square. It traverses like this
until the end.

/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file? 
 * 
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/
Input:	

	atattat
	tattata

Expected output: 

	Edit distance of 4

What happened:

	Edit distance = 4
	a - 2
	t t 0
	a a 0
	t t 0
	t t 0
	a a 0
	t t 0
	- a 2

	Execution time is: 0.000214 seconds.

	Yes, it seems to have worked correctly.


/**********************************************************************
 *  How much main memory does your computer have? Typical answers
 *  are 2 GB to 16 GB.
 **********************************************************************/

 	16 GB

/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of 
 *  N. Give an answer of the form a * N^b for some constants a 
 *  and b, where b is an integer. Note chars are 2 bytes long, and 
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 8GB (billion bytes) of memory?
 **********************************************************************/
a =
b = 
largest N =

/**********************************************************************
 *  Were you able to run Valgrind's massif tool to verify that your
 *  implementation uses the expected amount of memory?
 *
 *  Answer yes, no, I didn't try, I tried and failed, or I used a 
 *  different tool.
 *
 *  If yes, paste in the ms_print top chart of memory use over time,
 *  and also indicate which file your code was solving.
 * 
 *  Explain if necessary.
/**********************************************************************

Yes - I used ecoli2500.txt


    MB
23.96^                                              :                         
     |#::::::::::::@:::::@:::@::@:::::@::@@:::::@::::@::::@:::::::::::::::::::
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
     |#::::::::::::@:::::@:::@: @: : :@: @ :::::@::::@::::@::                :
   0 +----------------------------------------------------------------------->Gi
     0                                                                   3.837

Number of snapshots: 75
 Detailed snapshots: [1 (peak), 17, 25, 30, 32, 39, 42, 50, 60, 70]


/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *
 *  If you get segmentation fault when allocating memory for the last
 *  two test cases (N=20000 and N=28284), note this, and skip filling
 *  out the last rows of the table.
 **********************************************************************/

data file           distance       time (seconds)     memory (MB)
------------------------------------------------------------------
ecoli2500.txt		118				0.875108			23.96
ecoli5000.txt		160				4.37735				95.58
ecoli7000.txt		194				9.69193				187.2
ecoli10000.txt		223				24.5821				381.9				
ecoli20000.txt		3135			196.47				1.491 GB
ecoli28284.txt		8394			574.302				2.981 GB

Fill out the data here first, then go to the assignment web page for
instructions on sharing your data on iSENSE.

/*************************************************************************
 *  Here are sample outputs from a run on a different machine for 
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730

/**********************************************************************
 *  Enter your data onto iSENSE per the directions on the course web
 *  site. Then, paste a URL to your data set here.
 *
 *  YOU WILL ONLY RECEIVE CREDIT FOR YOUR iSENSE WORK IF YOU PROVIDE
 *  THE URL HERE.
 *
 *  e.g.: http://isenseproject.org/projects/871/data_sets/7893
 ************************************************************************/



/**********************************************************************
 *  For this question assume M=N (which is true for the sample files 
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a 
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use 
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 * 
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/
a = 
b = 
largest N = 

/**********************************************************************
 *  List whatever help (if any) you received from the course TAs,
 *  instructor, classmates, or anyone else.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/



/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
