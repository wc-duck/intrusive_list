/*
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
*/

#include "greatest.h"
#include "../slist.h"

struct slist_test_struct
{
	int value;

	SLIST_NODE(slist_test_struct) list1;
	SLIST_NODE(slist_test_struct) list2;
};

TEST insert_remove()
{
	// create list
	SLIST(slist_test_struct, list1) list1;

	// insert some elements
	slist_test_struct s1, s2, s3, s4;

	list1.insert_head( &s1 );
	list1.insert_head( &s2 );
	list1.insert_head( &s3 );
	list1.insert_head( &s4 );

	// itterate
	slist_test_struct* elem;

	elem = list1.head();
	ASSERT_EQ( &s4, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s3, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s2, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s1, elem ); elem = list1.next( elem );
	ASSERT_EQ( 0x0, elem );

	ASSERT_EQ( &s4, list1.remove_head() );
	ASSERT_EQ( &s3, list1.remove_head() );

	elem = list1.head();
	ASSERT_EQ( &s2, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s1, elem ); elem = list1.next( elem );
	ASSERT_EQ( 0x0, elem );

	// remove elements
	list1.clear();

	return 0;
}

TEST insert_tail()
{
	// create list
	SLIST(slist_test_struct, list1) list1;

	ASSERT_EQ( 0x0, list1.head() );
	ASSERT_EQ( 0x0, list1.tail() );

	// insert some elements
	slist_test_struct s1, s2, s3, s4;

	list1.insert_tail( &s1 );
	ASSERT_EQ( &s1, list1.tail() );
	ASSERT_EQ( &s1, list1.head() );
	list1.insert_tail( &s2 );
	ASSERT_EQ( &s2, list1.tail() );
	ASSERT_EQ( &s1, list1.head() );
	list1.insert_tail( &s3 );
	ASSERT_EQ( &s3, list1.tail() );
	ASSERT_EQ( &s1, list1.head() );
	list1.insert_tail( &s4 );
	ASSERT_EQ( &s4, list1.tail() );
	ASSERT_EQ( &s1, list1.head() );

	// itterate
	slist_test_struct* elem;

	elem = list1.head();
	ASSERT_EQ( &s1, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s2, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s3, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s4, elem ); elem = list1.next( elem );
	ASSERT_EQ( 0x0, elem );

	list1.remove( &s4 );
	elem = list1.head();
	ASSERT_EQ( &s1, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s2, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s3, elem ); elem = list1.next( elem );
	ASSERT_EQ( 0x0, elem );
	ASSERT_EQ( &s3, list1.tail() );

	list1.remove( &s3 );
	ASSERT_EQ( &s2, list1.tail() );

	elem = list1.head();
	ASSERT_EQ( &s1, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s2, elem ); elem = list1.next( elem );
	ASSERT_EQ( 0x0, elem );

	list1.clear();
	ASSERT_EQ( 0x0, list1.tail() );

	return 0;
}

TEST insert_remove_middle()
{
	// create list
	SLIST(slist_test_struct, list1) list1;

	// insert some elements
	slist_test_struct s1, s2, s3, s4, s5;

	list1.insert_head( &s1 );
	list1.insert_head( &s2 );
	list1.insert_head( &s3 );
	list1.insert_head( &s4 );

	// insert s5 after s2 after
	list1.insert_after( &s5, &s2 );

	// itterate
	slist_test_struct* elem;

	elem = list1.head();
	ASSERT_EQ( &s4, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s3, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s2, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s5, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s1, elem ); elem = list1.next( elem );
	ASSERT_EQ( 0x0, elem );

	list1.remove( &s2 );
	ASSERT_EQ( &s4, list1.head() );
	ASSERT_EQ( &s1, list1.tail() );

	elem = list1.head();
	ASSERT_EQ( &s4, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s3, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s5, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s1, elem ); elem = list1.next( elem );
	ASSERT_EQ( 0x0, elem );

	// remove elements
	list1.clear();

	return 0;
}

TEST in_2_lists()
{
	// create lists
	SLIST(slist_test_struct, list1) list1;
	SLIST(slist_test_struct, list2) list2;

	// insert some elements
	slist_test_struct s1, s2, s3, s4;

	list1.insert_head( &s1 );
	list1.insert_head( &s2 );
	list1.insert_head( &s3 );
	list1.insert_head( &s4 );

	list2.insert_head( &s4 );
	list2.insert_head( &s3 );
	list2.insert_head( &s2 );
	list2.insert_head( &s1 );

	// itterate
	slist_test_struct* elem = list1.head();
	ASSERT_EQ( &s4, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s3, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s2, elem ); elem = list1.next( elem );
	ASSERT_EQ( &s1, elem ); elem = list1.next( elem );
	ASSERT_EQ( 0x0, elem );

	elem = list2.head();
	ASSERT_EQ( &s1, elem ); elem = list2.next( elem );
	ASSERT_EQ( &s2, elem ); elem = list2.next( elem );
	ASSERT_EQ( &s3, elem ); elem = list2.next( elem );
	ASSERT_EQ( &s4, elem ); elem = list2.next( elem );
	ASSERT_EQ( 0x0, elem );

	// remove elements
	list1.clear();

	// list 2 still ok?
	elem = list2.head();
	ASSERT_EQ( &s1, elem ); elem = list2.next( elem );
	ASSERT_EQ( &s2, elem ); elem = list2.next( elem );
	ASSERT_EQ( &s3, elem ); elem = list2.next( elem );
	ASSERT_EQ( &s4, elem ); elem = list2.next( elem );
	ASSERT_EQ( 0x0, elem );

	// remove elements
	list2.clear();

	return 0;
}

TEST empty_list_head_zero()
{
	// create lists
	SLIST(slist_test_struct, list1) list1;

	// insert some elements
	slist_test_struct s1;

	ASSERT( list1.empty() );

	list1.insert_head( &s1 );

	ASSERT( !list1.empty() );

	list1.clear();

	ASSERT( list1.empty() );
	ASSERT_EQ( 0x0, list1.head() );

	return 0;
}

GREATEST_SUITE(slist_tests)
{
    RUN_TEST( insert_remove );
    RUN_TEST( insert_tail );
    RUN_TEST( insert_remove_middle );
    RUN_TEST( in_2_lists );
    RUN_TEST( empty_list_head_zero );
}
