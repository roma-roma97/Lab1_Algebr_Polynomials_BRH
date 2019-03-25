#include <gtest.h>
#include "Table.h"
#include "polinom.h"

TEST(HashTable, can_create_hashtable)
{
	ASSERT_NO_THROW(HashTable<TPolinom> tab);
}
TEST(HashTable, can_insert_element)
{
	HashTable<int> tab;
	ASSERT_NO_THROW(tab.Insert(1,1));
}
TEST(HashTable, can_delete_element)
{
	HashTable<int> tab;
	tab.Insert(1, 1);
	ASSERT_NO_THROW(tab.Delete(1));
}
TEST(HashTable, can_search_element)
{
	HashTable<int> tab;
	tab.Insert(1, 1);
	ASSERT_NO_THROW(tab.Search(1));
}
TEST(HashTable, can_get_element)
{
	HashTable<int> tab;
	tab.Insert(1, 1);
	EXPECT_EQ(1,tab.Search(1));
}
TEST(HashTable, cant_get_element_without_right_key)
{
	HashTable<int> tab;
	tab.Insert(1, 1);
	ASSERT_ANY_THROW(tab.Search(2));
}

