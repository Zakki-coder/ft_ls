#!/bin/bash
#Execute from root.
make re; ./ft_ls
#Test all file types.
#Test non-existent file
#Test only hidden files
#Max filename and path lengths
#Multiple sort flags
#Test with at least one file which is divisible with tab_size
#Test without files that are not divisible with tabsize
#Test extended attributes (@ symbol for example, at long list)
#When long list, if over six months old, show only year
#Also when long list six months newer shows only year
#+ and @ in long list
#Test memleaks with -R and without, with only files and with files and directories.
#Test leaks with nonexistent files and existing mixed also
#Test extended attributes and @ flag
#Check directory with 000 permissions
#ft_ls *
#test with only . and only ..
#Sticky bit chmod 7777