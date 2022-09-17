ACL AND EXTENDED ATTRIBUTESS NOT WORKING, MAYBE FIRST NORM AND FREE, THEN TRY TO FIX
EITH XATTTR ITS SYMBOLIC LINK WHICH DONT WORK

Test column and long format for leaks.
Test both with incorrect input
For both test recursion from root
Test rest of the flags also
Test with and without Dir AND file arguments
test with only dir arguments
test with only file arg
test with multiple dir arguments
test with multiple file arguments

ft_ls *

Remember to free ext_attrb from head remember to free acl with free_acl()

./ft_ls -Rl prints invalid argument

If the file or directory has extended
     attributes, the permissions field printed by the -l option is followed by
     a '@' character.  Otherwise, if the file or directory has extended secu-
     rity information (such as an access control list), the permissions field
     printed by the -l option is followed by a '+' character.

Get Extended atrributes in long format (like @ symbol)

Max pathname and max filename

CLOSE AND FREE EVERYTHING

LC_CTYPE=C tr -dc A-Za-z0-9_\!\@\#\$\%\^\&\*\(\)-+= < /dev/urandom | head -c 32 | xargs touch
