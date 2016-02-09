// PSLL_catch.cpp
// 
// unit test using catch
// for (non-polymorphic) singly-linked list implementation
//
// by Wenlan Tian
// for COP 3530 project 1
// Date: 09-28-2014
// 

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <iostream>
#include "PSLL.H"
#include "catch.hpp"

bool same_char( const char& a, const char& b ) { // argument for contains()
  return (a == b); 
}

bool in_list( const cop3530::PSLL<char>& list, char c ) {
  return list.contains( c, same_char ) ? true : false;
}

TEST_CASE("push_front()"){
	cop3530::PSLL<char> l;

	SECTION("when current list is empty"){
		l.push_front('A');

		REQUIRE(l[0]=='A');
	}

	l.push_front('A');

	SECTION("when push 10000 elements"){
		l.push_front('B');

		for(int i =0; i< 10000; ++i){
			l.push_front('O');

			REQUIRE(l[i+1]=='B');
			REQUIRE(l[i+2]=='A');
			REQUIRE(l[i] =='O');
		}
	}


}

TEST_CASE("push_back()"){
	cop3530::PSLL<char> l;

	SECTION("when current list is empty"){
		l.push_back('A');
		REQUIRE(l[0]=='A');
	}

	l.push_back('A');

	SECTION("when push 10000 elements"){
		l.push_back('B');

		for(int i =0; i< 10000; ++i){
			l.push_back('O');

			REQUIRE(l[0]=='A');
			REQUIRE(l[1]=='B');
			REQUIRE(l[i+2] =='O');
		}

		l.push_back('C');
		REQUIRE(l[10002] =='C');
	}
}

TEST_CASE("pop_front()"){
	cop3530::PSLL<char> l;

	SECTION("when current list is empty"){
		REQUIRE_THROWS(l.pop_front());
	}

	SECTION("when current list pop from 10000 elements to 0"){
		for(int i =0; i< 10000; ++i){
			l.push_front('O');
		}

		for(int i =0; i< 10000; ++i){
			REQUIRE(l.pop_front() =='O');
		}
	}
}


TEST_CASE("pop_back()"){
	cop3530::PSLL<char> l;

	SECTION("when current list is empty"){
		REQUIRE_THROWS(l.pop_back());
	}

	SECTION("when current list pop from 10000 elements to 0"){
		for(int i =0; i< 10000; ++i){
			l.push_front('O');
		}

		l.push_front('A');
		l.push_back('B');
		
		REQUIRE(l.pop_back() =='B');

		for(int i =0; i< 10000; ++i){
			REQUIRE(l.pop_back() =='O');
		}

		REQUIRE(l.pop_back() =='A');

	}
}


TEST_CASE("insert(T& element, int position)"){
	cop3530::PSLL<char> l;

	for(int i =0; i< 10000; ++i){
		l.push_front('O');
	}

	SECTION("position >=0 and <=size()"){
		REQUIRE_THROWS(l.insert('A',-5));
		REQUIRE_THROWS(l.insert('A',10009));
	}

	SECTION("position = 0"){
		l.insert('A',0);
		REQUIRE(l[0]=='A');
	}

	SECTION("position = size()"){
		l.insert('A',10000);
		REQUIRE(l[10000]=='A');
	}

	SECTION("random position"){
		l.insert('X',1500);
		REQUIRE (l[1500]=='X');
	}
}

TEST_CASE("remove(int position)"){
	cop3530::PSLL<char> l;

	SECTION("Remove from an empty list"){
		REQUIRE_THROWS(	l.remove(1));
	}

	for(int i =0; i< 10000; ++i){
		l.push_front('O');
	}

	l.push_front('A');
	l.push_back('B');

	SECTION("position >=0 and <=size()"){
		REQUIRE_THROWS(l.remove(-5););
		REQUIRE_THROWS(l.remove(10002););
	}

	SECTION("position == 0"){
		REQUIRE(l.remove(0) == 'A');
	}

	SECTION("position == size()-1"){
		REQUIRE(l[10001]=='B');		
		REQUIRE(l.remove(10001)=='B');
	}

	SECTION("random position"){
		REQUIRE (l.remove(1500)=='O');
	}
}

TEST_CASE("replace(T& element, int position)"){
	cop3530::PSLL<char> l;

	SECTION("when current list is empty"){
		REQUIRE_THROWS(l.replace('A',0));
	}

	for(int i =0; i< 9998; ++i){
		l.push_front('O');
	}
	l.push_front('M');
	l.push_back('N');

	SECTION("position >=0 and <=size()"){
		REQUIRE_THROWS(l.replace('A',-1));
		REQUIRE_THROWS(l.replace('A',10009));
	}

	SECTION("position = 0"){
		REQUIRE(l.replace('A',0)=='M');
		l.replace('A',0);
		REQUIRE(l[0]=='A');
	}

	SECTION("position = size()-1"){
		REQUIRE(l.replace('A',9999)=='N');
		l.replace('A',9999);
		REQUIRE(l[9999]=='A');
	}

	SECTION("random position"){
		REQUIRE(l.replace('A',1500)=='O');
		l.replace('A',1500);
		REQUIRE(l[1500]=='A');
	}
}

TEST_CASE("item_at(int position)"){
	cop3530::PSLL<char> l;

	SECTION("empty list"){
		REQUIRE_THROWS(	l.item_at(0));
		REQUIRE_THROWS(	l.item_at(5));
	}

	for(int i =0; i< 9998; ++i){
		l.push_front('O');
	}

	l.push_front('A');
	l.push_back('B');

	SECTION("position >=0 and <=size()"){
		REQUIRE_THROWS(l.item_at(-5));
		REQUIRE_THROWS(l.item_at(10000));
	}

	SECTION("position == 0"){
		REQUIRE(l.item_at(0)=='A');
	}

	SECTION("position == size()-1"){
		REQUIRE(l[9999]=='B');
		REQUIRE(l.item_at(9999)=='B');
	}

	SECTION("random position"){
		REQUIRE (l.item_at(1500)=='O');
	}
}

TEST_CASE("is_empty()"){
	cop3530::PSLL<char> l;

	SECTION("Empty list"){
		REQUIRE(l.is_empty());
	}

	SECTION("Not empty list"){
		l.push_front('A');
		REQUIRE_FALSE(l.is_empty());
	}
}


TEST_CASE("clear()"){
	cop3530::PSLL<char> l;

	SECTION("Empty list"){
		REQUIRE(l.is_empty());
		l.clear();
		REQUIRE(l.is_empty());
	}

	SECTION("Not empty list"){

		for(int i =0; i< 9998; ++i){
			l.push_front('O');
		}
		REQUIRE_FALSE(l.is_empty());
		l.clear();
		REQUIRE(l.is_empty());
	}
}


TEST_CASE("contains()"){
	cop3530::PSLL<char> l;

	SECTION("Empty list"){
		REQUIRE_THROWS(in_list(l, 'A'));
	}

	l.push_back('O');
	l.push_back('O');
	l.push_back('A');

	SECTION("contain"){
		REQUIRE(in_list(l,'A'));
	}

	SECTION("not contain"){
		REQUIRE_FALSE(in_list(l, 'a'));
		REQUIRE_FALSE(in_list(l, 'O'));
	}
}

TEST_CASE("PSLL& operator=(const PSLL& src)"){
	cop3530::PSLL<char> src;
	cop3530::PSLL<char> l;

	SECTION("Empty list"){
		REQUIRE_THROWS(l=src);
	}

	for(int i =0; i< 9998; ++i){
		src.push_front('O');
	}

	src.push_front('A');
	src.push_back('B');

	SECTION("=()"){
		l = src;
		REQUIRE(l[0]=='A');
		REQUIRE(l[9999]=='B');
	}
}

TEST_CASE("T& operator[](int i)"){
	cop3530::PSLL<char> l;

	SECTION("empty list"){
		REQUIRE_THROWS(	l[0]);
		REQUIRE_THROWS(	l[5]);
	}

	for(int i =0; i< 9998; ++i){
		l.push_front('O');
	}

	l.push_front('A');
	l.push_back('B');

	SECTION("position >=0 and <=size()"){
		REQUIRE_THROWS(l[-5]);
		REQUIRE_THROWS(l[10000]);
	}

	SECTION("position == 0"){
		REQUIRE(l[0]=='A');
	}

	SECTION("position == size()-1"){
		REQUIRE(l[9999]=='B');
	}

	SECTION("random position"){
		REQUIRE (l[1500]=='O');
		REQUIRE_FALSE(l[1500]=='X');

		l[1500]='X';
		REQUIRE_FALSE (l[1500]=='O');
		REQUIRE (l[1500]=='X');
	}
}

/*
TEST_CASE("T const& operator[](int i) const"){
	cop3530::PSLL<char> l;

	SECTION("empty list"){
		REQUIRE_THROWS(l[0] );
		REQUIRE_THROWS(l[5] );
	}

	for(int i =0; i< 9998; ++i){
		l.push_front('O');
	}

	l.push_front('A');
	l.push_back('B');

	SECTION("position >=0 and <=size()"){
		REQUIRE_THROWS(l[-5]);
		REQUIRE_THROWS(l[10000]);
	}

	SECTION("position == 0"){
		REQUIRE(l[0]=='A');
	}

	SECTION("position == size()-1"){
		REQUIRE(l[9999]=='B');
	}

	SECTION("random position"){
		REQUIRE (l[1500]=='O');
		REQUIRE_FALSE(l[1500]=='X');

		l[1500]='X';
		REQUIRE_FALSE (l[1500]=='O');
		REQUIRE (l[1500]=='X');
	}
}

*/
TEST_CASE("Iterator"){
	cop3530::PSLL<char> l;

//	SECTION("empty list"){

//	}

	for(int i =0; i< 9998; ++i){
		l.push_front('O');
	}

	l.push_front('A');
	l.push_back('B');

	SECTION("begin()"){
		cop3530::PSLL<char>::iterator iter = l.begin();

		SECTION("test operator*()"){
			REQUIRE(*iter == 'A');
		}

//		SECTION("test operator->()"){
//			REQUIRE(->iter == 'A');
//		}


		SECTION("Test immutable"){
			*iter = 'Y';
			REQUIRE(*iter =='Y');
		}
	}

	SECTION("test operator=()"){
		cop3530::PSLL<char>::iterator iter = l.begin();

		cop3530::PSLL<char>::iterator iter1;

		iter1 = iter;
		REQUIRE(*iter1 == 'A');
	}

	SECTION("test operator++()"){
		l.push_front('M');
		cop3530::PSLL<char>::iterator iter = l.begin();

		REQUIRE(*(++iter)=='A');
		REQUIRE_FALSE(*(++iter)=='M');
	}

	SECTION("test operator++(int)"){
		l.push_front('M');
		cop3530::PSLL<char>::iterator iter = l.begin();

		REQUIRE(*(iter++) == 'M');
//		REQUIRE_FALSE(*(iter++)=='A');
	}

	SECTION("test operator==()"){
		cop3530::PSLL<char> l1;

		for(int i =0; i< 9998; ++i){
			l1.push_front('O');
		}

		l1.push_front('A');
		l1.push_back('B');

		cop3530::PSLL<char>::iterator iter = l.begin();
		cop3530::PSLL<char>::iterator iter1 = l.end();

		cop3530::PSLL<char>::iterator iter2 = l1.begin();

		while (iter!=iter1){
			REQUIRE(*iter == *iter2);
			iter++;
			iter2++;
		}
	}

	SECTION("test operator==()"){
		cop3530::PSLL<char> l1;

		for(int i =0; i< 9998; ++i){
			l1.push_front('M');
		}

		l1.push_front('B');
		l1.push_back('A');

		cop3530::PSLL<char>::iterator iter = l.begin();
		cop3530::PSLL<char>::iterator iter1 = l.end();

		cop3530::PSLL<char>::iterator iter2 = l1.begin();

		while(iter!=iter1){
			REQUIRE(*iter != *iter2);
			iter++;
			iter2++;
		}
	}

}

TEST_CASE("Const_Iterator"){
	 cop3530::PSLL<char> l;

	for(int i =0; i< 9998; ++i){
		l.push_front('O');
	}

	l.push_front('A');
	l.push_back('B');

	const cop3530::PSLL<char> *const_list = &l;

	SECTION("begin()"){
		cop3530::PSLL<char>::const_iterator const_iter = const_list->begin();

		SECTION("test operator*()"){
			REQUIRE(*const_iter == 'A');
		}

		SECTION("test operator->()"){
			REQUIRE(*(const_iter.operator->()) == 'A');
		}

		SECTION("Test immutable"){
	//		*const_iter = 'Y';  //compile error;
			REQUIRE_FALSE(*const_iter =='Y');
			REQUIRE(*const_iter =='A');
		}
	}

	SECTION("test operator=()"){
		cop3530::PSLL<char>::const_iterator const_iter = const_list->begin();

		cop3530::PSLL<char>::const_iterator const_iter1;

		const_iter1 = const_iter;

		REQUIRE(*const_iter1 == 'A');
	}

	SECTION("test operator++()"){
		cop3530::PSLL<char>::const_iterator const_iter = const_list->begin();

		REQUIRE(*(++const_iter)=='O');
		REQUIRE_FALSE(*(++const_iter)=='A');
	}

	SECTION("test operator++(int)"){
		cop3530::PSLL<char>::const_iterator const_iter = const_list->begin();

		REQUIRE(*(const_iter++) == 'A');
//		REQUIRE_FALSE(*(const_iter++)=='O');
	}

	SECTION("test operator==()"){
		cop3530::PSLL<char> l1;

		for(int i =0; i< 9998; ++i){
			l1.push_front('O');
		}

		l1.push_front('A');
		l1.push_back('B');

		const cop3530::PSLL<char> *const_list1 = &l1;

		cop3530::PSLL<char>::const_iterator const_iter = const_list->begin();
		cop3530::PSLL<char>::const_iterator const_iter1 = const_list->end();

		cop3530::PSLL<char>::const_iterator const_iter2 = const_list->begin();

		while (const_iter!=const_iter1){
			REQUIRE(*const_iter == *const_iter2);
			const_iter++;
			const_iter2++;
		}
	}

	SECTION("test operator!=()"){
		cop3530::PSLL<char> l1;

		for(int i =0; i< 9998; ++i){
			l1.push_front('M');
		}

		l1.push_front('B');
		l1.push_back('A');

		const cop3530::PSLL<char> *const_list1 = &l1;

		cop3530::PSLL<char>::const_iterator const_iter = const_list->begin();
		cop3530::PSLL<char>::const_iterator const_iter1 = const_list->end();

		cop3530::PSLL<char>::const_iterator const_iter2 = const_list1->begin();

		while (const_iter!=const_iter1){
			REQUIRE(*const_iter != *const_iter2);
			const_iter++;
			const_iter2++;
		}
	}
}

