Sorting, or columns not working perfectly. Just compare ls and ft_ls .

In the long format:      If the modification time of the file is more than 6 months in the past or future, then
     the year of the last modification is displayed in place of the hour and minute fields.

Links at long format

     If no operands are given, the contents of the current directory are displayed.  If more
     than one operand is given, non-directory operands are displayed first; directory and
     non-directory operands are sorted separately and in lexicographical order.

Should create list check if -a flag is on? DONE 
After create_list we should do sorting. After that somekind of function dispatcher. Recursive needs also access to dispatcher. 


In create list function head is marked with is_head flag, after sorting it wont be correct. Recursion uses is_head for printing dir names. Sorter should control that flag, not create_list.