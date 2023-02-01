#include "List.h"
#include "unit_test_framework.h"

using namespace std;

//DONE
TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

//DONE
TEST(test_list_empty) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    ASSERT_EQUAL(empty_list.size(), 0);
}

//DONE
TEST(test_list_char) {
    List<char> list;
    for(int i = 0; i < 200; ++i)
    {
        list.push_back('a');
        char one = list.back();
        list.push_back('n');
        list.push_back('n');
        list.push_back('a');
        char two = list.back();
        ASSERT_EQUAL(one, two);
    }
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.size(), 800);
}

//DONE
TEST(test_list_1500) {
    List<int> list;
    for(int i = 0; i < 500; ++i)
    {
        list.push_back(3);
        if(i % 5 == 0)
        {
            list.pop_back();
            list.push_front(123);
        }
    }
    ASSERT_EQUAL(list.front(), 123);
    ASSERT_EQUAL(list.size(), 500);
    for(int p = 0; p < 500; ++p)
    {
        list.push_front(-1);
        list.push_front(0);
        if(p % 100 == 0)
        {
            list.push_front(2000);
            list.pop_back();
            ASSERT_EQUAL(list.front(), 2000);
        }
    }
    ASSERT_EQUAL(list.size(), 1500);
}

//DONE
TEST(test_list_iterator) {
    List<int> list;
    for(int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }
    list.push_back(4);

    List<int>::Iterator it = list.begin();
    int Old = *it; //0
    ++it;
    int New = *it;  //1
    ++it;
    ASSERT_TRUE(Old != New);
    ++++it;
    Old = *it; //4
    ++it;
    New = *it; //4
    ASSERT_TRUE(Old == New);
}

// Done
TEST(test_list_insert) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it = list.begin();
    ++++it;
    list.insert(it,7);
    ASSERT_TRUE(*it != 2);
}

// Done
TEST(test_list_size) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	ASSERT_EQUAL(list.size(), 3);

	list.push_front(4);

	ASSERT_EQUAL(list.size(), 4);

	list.pop_back();
	list.pop_back();

	ASSERT_EQUAL(list.size(), 2);

	list.pop_back();
	list.pop_back();

	ASSERT_EQUAL(list.size(), 0);
	ASSERT_TRUE(list.empty());
}

// Done
TEST(test_list_front) {
	List<int> list;
	list.push_front(2);
	list.push_front(4);
	list.push_back(3);

	ASSERT_EQUAL(list.front(), 4);

	list.push_front(5);

	ASSERT_EQUAL(list.front(), 5);

}

// Done
TEST(test_list_back) {
	List<int> list;
	list.push_front(2);
	list.push_front(4);
	list.push_back(3);

	ASSERT_EQUAL(list.back(), 3);

	list.push_back(5);

	ASSERT_EQUAL(list.back(), 5);
}

// Done
TEST(test_list_push_front) {
	List<int> list;
	
	ASSERT_TRUE(list.empty());
	list.push_front(2);
	list.push_front(4);
	
	ASSERT_EQUAL(list.size(), 2);
	list.push_front(5);

	ASSERT_EQUAL(list.size(), 3);
	ASSERT_FALSE(list.empty());
	ASSERT_EQUAL(list.front(), 5);
}

// Done
TEST(test_list_push_back) {
	List<int> list;

	ASSERT_TRUE(list.empty());
	list.push_back(2);
	list.push_back(4);

	ASSERT_EQUAL(list.size(), 2);
	list.push_back(5);

	ASSERT_EQUAL(list.size(), 3);
	ASSERT_FALSE(list.empty());
	ASSERT_EQUAL(list.back(), 5);
}

// Done
TEST(test_list_pop_front) {
	List<int> list;

	ASSERT_TRUE(list.empty());
	list.push_back(2);
	list.push_back(4);

	ASSERT_EQUAL(list.size(), 2);
	list.pop_front();
	ASSERT_EQUAL(list.size(), 1);
	ASSERT_EQUAL(list.front(), 4);
	ASSERT_FALSE(list.empty());
	list.pop_front();
	ASSERT_TRUE(list.empty());
}

// Done
TEST(test_list_pop_back) {
	List<int> list;

	ASSERT_TRUE(list.empty());
	list.push_back(2);
	list.push_back(4);

	ASSERT_EQUAL(list.size(), 2);
	list.pop_back();
	ASSERT_EQUAL(list.size(), 1);
	ASSERT_EQUAL(list.back(), 2);
	ASSERT_FALSE(list.empty());
	list.pop_back();
	ASSERT_TRUE(list.empty());
}

// Done
TEST(test_list_copy_ctor) {
	List<int> list_orig;
	list_orig.push_front(2);
	list_orig.push_front(4);
	list_orig.push_front(5);


	List<int> list_copy(list_orig);

	ASSERT_EQUAL(list_copy.front(), list_orig.front());
	ASSERT_EQUAL(list_copy.back(), list_orig.back());
	ASSERT_EQUAL(list_copy.size(), list_orig.size());
}

// Done
TEST(test_list_copy_ctor_change_orig) {
	List<int> list_orig;
	list_orig.push_front(2);
	list_orig.push_front(4);
	list_orig.push_front(5);


	List<int> list_copy(list_orig);
	
	list_orig.push_front(8);
	ASSERT_NOT_EQUAL(list_copy.front(), list_orig.front());

	list_orig.push_back(7);
	ASSERT_NOT_EQUAL(list_copy.back(), list_orig.back());
}

// Done
TEST(test_list_copy_ctor_change_copy) {
	List<int> list_orig;
	list_orig.push_front(2);
	list_orig.push_front(4);
	list_orig.push_front(5);


	List<int> list_copy(list_orig);

	list_copy.push_front(8);
	ASSERT_NOT_EQUAL(list_copy.front(), list_orig.front());

	list_copy.push_back(7);
	ASSERT_NOT_EQUAL(list_copy.back(), list_orig.back());
}

// Done
TEST(test_list_assignment) {
	List<int> list_orig;
	list_orig.push_front(2);
	list_orig.push_front(4);
	list_orig.push_front(5);

	List<int> list_copy = list_orig;

	ASSERT_EQUAL(list_copy.front(), list_orig.front());
	ASSERT_EQUAL(list_copy.back(), list_orig.back());
	ASSERT_EQUAL(list_copy.size(), list_orig.size());
}

// Done
TEST(test_list_assignment_on_same_list) {
		List<int> list_orig;
		list_orig.push_front(2);
		list_orig.push_front(4);
		list_orig.push_front(5);
		int front = list_orig.front();
		list_orig = list_orig;
		ASSERT_EQUAL(list_orig.front(), front);
}
// Done
TEST(test_list_assignment_change_orig) {
	List<int> list_orig;
	list_orig.push_front(2);
	list_orig.push_front(4);
	list_orig.push_front(5);

	List<int> list_copy = list_orig;

	list_orig.push_front(8);
	ASSERT_NOT_EQUAL(list_copy.front(), list_orig.front());

	list_orig.push_back(7);
	ASSERT_NOT_EQUAL(list_copy.back(), list_orig.back());
}

// Done
TEST(test_list_assignment_change_copy) {
	List<int> list_orig;
	list_orig.push_front(2);
	list_orig.push_front(4);
	list_orig.push_front(5);

	List<int> list_copy = list_orig;

	list_copy.push_front(8);
	ASSERT_NOT_EQUAL(list_copy.front(), list_orig.front());

	list_copy.push_back(7);
	ASSERT_NOT_EQUAL(list_copy.back(), list_orig.back());
}

// Done
TEST(test_list_iterator_next) {
	List<int> list;
	list.push_back(-2);
	list.push_back(-4);

	List<int>::Iterator it = list.begin();
	ASSERT_EQUAL(*it, -2);
	++it;
	ASSERT_EQUAL(*it, -4);
	ASSERT_EQUAL(*it, list.back());
}

// Done
TEST(test_list_iterator_prev) {
	List<int> list;
	list.push_back(2);
	list.push_back(4);

	List<int>::Iterator it = list.begin();
	ASSERT_EQUAL(*it, 2);
	++it;
	ASSERT_EQUAL(*it, 4);
	--it;
	ASSERT_EQUAL(*it, list.front());
}

// Done
TEST(test_list_iterator_equal_not_equal) {
	List<int> list;
	list.push_back(2);
	list.push_back(4);

	List<int>::Iterator it1 = list.begin();
	List<int>::Iterator it2 = list.begin();
	ASSERT_TRUE(it1 == it2);
	++it1;
	++it2;
	ASSERT_TRUE(it1 == it2);
	--it2;
	ASSERT_TRUE(it1 != it2);

}

// Done
TEST(test_list_iterator_dereference) {
	List<int> list;
	list.push_back(2);
	list.push_back(4);

	List<int>::Iterator it1 = list.begin();
	List<int>::Iterator it2 = list.begin();
	ASSERT_EQUAL(*it1, 2);
	++it1;
	ASSERT_EQUAL(*it1, 4);
	++it2;
	ASSERT_EQUAL(*it1, *it2);
}

// Done
TEST(test_list_iterator_begin) {
	List<int> list;
	list.push_back(2);

	List<int>::Iterator it = list.begin();
	ASSERT_EQUAL(*it, 2);

	ASSERT_EQUAL(*(list.begin()), list.front());
}

// Done
TEST(test_list_iterator_end) {
	List<int> list;
	list.push_back(2);
	list.push_back(3);

	List<int>::Iterator it_ctor;

	List<int>::Iterator it_end = list.end();
	ASSERT_TRUE(it_ctor == it_end);
}

// Done
TEST(test_list_iterator_erase) {
	List<int> list;
	list.push_back(2);
	list.push_back(5);
	list.push_back(8);

	List<int>::Iterator it = list.begin();
	ASSERT_EQUAL(*it, 2);
	++++it;
	list.erase(it);
	ASSERT_EQUAL(list.back(), 5);

	List<int>::Iterator it2 = list.begin();
	list.erase(it2);
	ASSERT_EQUAL(list.back(), 5);
	ASSERT_EQUAL(list.front(), 5);
}

// Done
TEST(test_list_iterator_erase_more) {
	List<int> list;
	list.push_back(2);
	list.push_back(5);
	list.push_back(8);

	List<int>::Iterator it = list.begin();
	list.erase(it);
	ASSERT_EQUAL(list.front(), 5);

	List<int>::Iterator it2 = list.begin();
	list.erase(it2);
	ASSERT_EQUAL(list.front(), 8);

	List<int>::Iterator it3 = list.begin();
	list.erase(it3);
	ASSERT_EQUAL(*it3, 8);
	ASSERT_TRUE(list.empty());
}

// Done
TEST(test_list_iterator_insert_again) {
	List<int> list;
	list.push_back(2);
	list.push_back(5);
	list.push_back(8);

	List<int>::Iterator it = list.begin();
	ASSERT_EQUAL(*it, 2);
	++it;
	list.insert(it, 4);
	list.pop_back();
	list.pop_back();
	ASSERT_EQUAL(list.back(), 4);
}

// Done
TEST(test_list_iterator_insert_at_front) {
	List<int> list;
	list.push_back(2);
	list.push_back(5);
	list.push_back(8);
	int orig_size = 3;

	List<int>::Iterator it = list.begin();
	ASSERT_EQUAL(*it, 2);
	list.erase(it);
	ASSERT_EQUAL(*it, 32);
	it = list.begin();
	list.insert(it, 4);
	ASSERT_EQUAL(list.front(), 4);
	ASSERT_FALSE(list.size() != orig_size);
}

TEST_MAIN()

