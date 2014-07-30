# Intrusive linked list

[![Build Status](https://travis-ci.org/wc-duck/intrusive_list.svg?branch=master)](https://travis-ci.org/wc-duck/intrusive_list)
[![Build Status](https://ci.appveyor.com/api/projects/status/s5faxb2u8571s5xf)](https://ci.appveyor.com/project/wc-duck/intrusive-list)

## About:
Implementation of single- and double- intrusive linked lists.

After looking at the interwebs for some intrusive linked lists I found that there is no good alternatives 
available, if you like me do not want to use boost.

So here is an implementation that has served me well for my own private projects.

## Example:

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
	}

	// ... walk through items in list backward ...
	for( my_struct* iter = the_list.tail(); iter != 0x0; iter = the_list.prev( iter ) )
	{
		// ... do stuff with iter ...
	}

	// ... remove some elements from list ...
	the_list.remove( &s2 );
	the_list.remove_head();
	the_list.remove_tail();

	return 0;
};

```

## Licence:

```
   Intrusive single/double linked list for C++.

   version 0.1, augusti, 2013

   Copyright (C) 2013- Fredrik Kihlander

   This software is provided 'as-is', without any express or implied
   warranty.  In no event will the authors be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
      claim that you wrote the original software. If you use this software
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original software.
   3. This notice may not be removed or altered from any source distribution.

   Fredrik Kihlander
```
