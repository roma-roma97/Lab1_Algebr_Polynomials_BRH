#include <gtest.h>
#include "Table.h"
#include "polinom.h"


TEST(HashTable, can_create_hashtable_of_polinoms)
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
TEST(HashTable, cant_delete_without_right_key)
{
	HashTable<int> tab;
	tab.Insert(1, 1);
	ASSERT_ANY_THROW(tab.Delete(2));
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
	EXPECT_EQ(1, tab.Search(1));
}
TEST(HashTable, cant_get_element_without_right_key)
{
	HashTable<int> tab;
	tab.Insert(1, 1);
	ASSERT_ANY_THROW(tab.Search(2));
}
TEST(Hash_Table, can_create_hashtable_of_polinoms)
{
	ASSERT_NO_THROW(Hash_Table<TPolinom> tab);
}
TEST(Hash_Table, can_insert_element)
{
	Hash_Table<int> tab;
	ASSERT_NO_THROW(tab.Insert(1, 1));
}
TEST(Hash_Table, can_delete_element)
{
	Hash_Table<int> tab;
	tab.Insert(1, 1);
	ASSERT_NO_THROW(tab.Delete(1));
}
TEST(Hash_Table, cant_delete_without_right_key)
{
	Hash_Table<int> tab;
	tab.Insert(1, 1);
	ASSERT_ANY_THROW(tab.Delete(2));
}
TEST(Hash_Table, can_search_element)
{
	Hash_Table<int> tab;
	tab.Insert(1, 1);
	ASSERT_NO_THROW(tab.Search(1));
}
TEST(Hash_Table, can_get_element)
{
	Hash_Table<int> tab;
	tab.Insert(1, 1);
	EXPECT_EQ(1,tab.Search(1));
}
TEST(Hash_Table, cant_get_element_without_right_key)
{
	Hash_Table<int> tab;
	tab.Insert(1, 1);
	ASSERT_ANY_THROW(tab.Search(2));
}

