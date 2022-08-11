Remember to free ext_attrb from head remember to free acl with free_acl()

If the file or directory has extended
     attributes, the permissions field printed by the -l option is followed by
     a '@' character.  Otherwise, if the file or directory has extended secu-
     rity information (such as an access control list), the permissions field
     printed by the -l option is followed by a '+' character.

Get Extended atrributes in long format (like @ symbol)

Max pathname and max filename

CLOSE AND FREE EVERYTHING

LC_CTYPE=C tr -dc A-Za-z0-9_\!\@\#\$\%\^\&\*\(\)-+= < /dev/urandom | head -c 32 | xargs touch
