# About:
Implementation of single- and double- intrusive linked lists.

After looking at the interwebs for some intrusive linked lists I found that there is no good alternatives 
available, if you like me do not want to use boost.

So here is an implementation that has served me well for my own private projects.

# Example:

```c++
#include "list.h"

// ... lets define a struct that should exist in a list ...
struct my_struct
{
	LIST_NODE( my_struct ) list;

	int some_data;
};

// ... and a list to store "my_struct":s in ...
LIST( my_struct, list ) the_list; // arg1 the type to store in list, arg2 name of member in my_struct to use for list.

int main( int argc, char** argv )
{
	// ... create some structs ...
	my_struct s1;
	my_struct s2;
	my_struct s3;
	my_struct s4;

	// ... insert them at list head ...
	the_list.insert_head( &s1 );
	the_list.insert_tail( &s2 );
	the_list.insert_before( &s3, &s1 );
	the_list.insert_after( &s4, &s2 );

	// ... walk through items in list forward ...
	for( my_struct* iter = the_list.head(); iter != 0x0; iter = the_list.next( iter ) )
	{
		// ... do stuff with iter ...

		// ... advance iterator ...
		iter = the_list.next( iter );
	}

	// ... walk through items in list backward ...
	for( my_struct* iter = the_list.tail(); iter != 0x0; iter = the_list.prev( iter ) )
	{
		// ... do stuff with iter ...

		// ... advance iterator ...
		iter = the_list.prev( iter );
	}

	// ... remove some elements from list ...
	the_list.remove( &s2 );
	the_list.remove_head();
	the_list.remove_tail();

	return 0;
};

```
