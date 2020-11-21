/* CISC220 Cameron Frey and Liam Jordan
 * DLL.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: 13027
 */
//Part 1:(20 pts) (addFirst (3pts) ,addAtFront(4 pts),push (4 pts),pop(4 pts)) + getting secret message:5 pts
//In the DLL.cpp class, get push, pop, and addFirst and addAtFront working for a doubly linked list as specified in DLL.hpp and DLL.cpp.
//For this section I've given you the test cases.  You should get the output I've given you for part 1. When you get those methods working, running this will decode the secret code 1
//
//Once you have that working, start on part 2 (note you will have to go into Coder.cpp and toggle
//comments for lines 64-110 to run part 2)
//
//Part 2: (15 pts)(insertAt(5 pts), removeAtK(5 pts)) +secret message: 5 pts
//Get  the DLL.cpp methods insertAt and removeAtK methods working for a doubly linked list.
//I've given you the test cases and the output.  When you get them working, you should be able to run this and decode the second secret code
//
//Once you have that working, start on part 3 (note that you will have to go to Coder.cpp and toggle comments for lines 112-137 to run part 3)
//
//Part 3: (8 pts) (reverse (4 pts)) + secret message: 4 pts
//For this part, you will get the method reverse working for the DLL doubly linked list class.
//This method reverses the list.  Note: it doesn't just print out the list in reverse order, it actually reverses the list, so if the original list was 3<->2<->4<->8, with 3 being first and 8 being last, the reversed list would be 8<->4<->2<->3 with 8 being first and 3 being last.
//
//once you have that working, start on part 4 (note that you will have to go to Coder.cpp and toggle
//comments for lines 139-215 to run part 4)
//
//Part 4: (11 pts) (removeX (5 pts), call by pointer) + secret message: 6 pts
//For this part, you will get the method removeX to work.  removeX removes the value x from the linked list, and uses call by pointer to change the index parameter to be the index (count) of where x occurred in the list.  So, for instance if you had:
//7<->8<->3<->5<->2<->6<->1
//And you called: removeX(3,&ind)
//When  you leave the method, you’d have
//7<->8<->5<->2<->6<->1
//And ind would hold 2
//
//Once you have this working, start on part 5.  For this you will have to go to Coder.cpp and toggle comments for lines  217- 251
//
//Part 5: (21 pts)(skip – recursive (13 pts) + secret message: 8 pts
//For this part, you will get the method skip working for the DLL doubly linked list class. This method RECURSIVELY deletes every other node.  If the boolean flag is set to true, it will delete every even node (i.e.,if the list was
//3<->2<->4<->5<->1<->7,
//the list that would result after the skip method was called would be:
//3<->4<->1.
//If the flag is set to false, the resulting list will be
//2<->5<->7
//NOTE:  For efficiency's sake, this method SHOULD NOT call removeAtK



#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

DLL::DLL(){  // constructor - initializes an empty list
	last = NULL;
	first = NULL;
	size = 0;
}
DLL::DLL(int x){  // constructor, initializes a list with one new node with data x
	DNode *n = new DNode (x);
	first = n;
	last = n;
	size=1;
}
/***************************************************************************************************/
/*Part 1																							*/
/***************************************************************************************************/
/* write push, pop, addAtFront */

void DLL::push(int x){
	if(first == NULL && last == NULL){
		addFirst(x);
	}
	else{
		DNode *tmp1 = last;
		DNode *tmp2 = new DNode(x);
		tmp1->next = tmp2;
		tmp2->prev = tmp1;
		last = tmp2;
		size++;
	}
}

int DLL::pop(){
	if(size == 1){
		DNode *tmp = first;
		first = NULL;
		last = NULL;
		delete tmp;
		size--;
		return 0;
	}
	else{
		DNode *tmp1 = last->prev;
		last = tmp1;
		delete tmp1->next;
		last->next = NULL;
		size--;
		return 0;
	}
}

void DLL::addAtFront(int x){
	DNode *tmp = new DNode(x);
	tmp->next = first;
	first->prev = tmp;
	first = tmp;
	size++;
}

void DLL::addFirst(int x){
	while (size > 0) {
		pop();
	}
	DNode *tmp = new DNode(x);
	first = tmp;
	last = tmp;
	size++;
}

/***************************************************************************************************/
/*Part 2																							*/
/***************************************************************************************************/
/* write insertAt, removeAtK  here */
void DLL::insertAt(int ind, int x){
	DNode *list = first;
	for(int i = 0; i < ind-1; i++){
		list = list->next;
	}
	if(list->next == NULL){
		push(x);
	}
	else{
		DNode *tmp = new DNode(x);
		DNode *tmp2 = list->next;
		list->next = tmp;
		tmp->prev = list;
		tmp->next = tmp2;
		tmp2->prev = tmp;
		size++;
	}
}

int DLL::removeAtK(int ind){
	if(ind == 0){
		if(size > 1){
			DNode *list = first;
			DNode *tmp = list->next;
			first = tmp;
			tmp->prev = NULL;
			delete list;
			size--;
			return 0;
		}
		else{
			DNode *list = first;
			first = NULL;
			last = NULL;
			delete list;
			size--;
			return 0;
		}
	}
	else if(ind + 1 == size){
		pop();
		return 0;
	}
	else if(ind + 1 > size){
		cout << "Index out of range!" << endl;
		return 0;
	}
	else{
		DNode *list = first;
		for(int i = 0; i < ind-1; i++){
			list = list->next;
		}
		DNode *tmp = list->next;
		list->next = tmp->next;
		tmp->next->prev = list;
		delete tmp;
		size--;
		return 0;
	}
}


/****************************************************************************************/
/* Part 3                                                                                */
/****************************************************************************************/
/* write reverse here */

void DLL::reverse(){
	int tmpData = 0;
	DNode *tmp1 = first;
	DNode *tmp2 = last;
	if(size <= 1){
		cout<<"Can't reverse!" << endl;
	}
	else{
		for(int i = 0; i < size/2; i++){
			tmpData = tmp1->data;
			tmp1->data = tmp2->data;
			tmp2->data = tmpData;
			tmp1 = tmp1->next;
			tmp2 = tmp2->prev;
		}
	}
}

/****************************************************************************************/
/* Part 4                                                                                */
/****************************************************************************************/
/* write removeX here */

void DLL::removeX(int x, int *ind){
	int count = 0;
	if(first->data == x){
		removeAtK(0);
		*ind = count;
	}
	else{
		DNode *tmp1 = first;
		while(tmp1->data != x){
			count++;
			if(count == size-1){
				tmp1 = tmp1->next;
				break;
			}
			else{
				tmp1 = tmp1->next;
			}
		}
		if(tmp1->data != x){
			cout << x << " is not in the list!" << endl;
			*ind = 0;
		}
		else{
			*ind = count;
			removeAtK(count);
		}
	}
}

/****************************************************************************************/
/* Part 5                                                                               */
/****************************************************************************************/
/* write skip here */

void DLL::skip(bool flag, int ct, DNode *tmp){
	if(flag == true){
		if(ct < size-1){
			if(ct == 0){
				DNode *list = first;
				DNode *tmp = list->next;
				first = tmp;
				tmp->prev = NULL;
				delete list;
				size--;
				skip(flag,ct+1,tmp);
			}
			else{
				DNode *list = first;
				for(int i = 0; i < ct-1; i++){
					list = list->next;
				}
				DNode *tmp = list->next;
				list->next = tmp->next;
				tmp->next->prev = list;
				delete tmp;
				size--;
				skip(flag,ct+1,tmp);
			}
		}
	}
	else{
		 if(ct < size-1){
			ct++;
			DNode *list = first;
			for(int i = 0; i < ct-1; i++){
				list = list->next;
			}
			if(ct==size-1 && ct%2==1){
				DNode *tmp = list->next;
				list->next = NULL;
				delete tmp;
				size--;
				last = list;
			}
			else{
				DNode *tmp = list->next;
				list->next = tmp->next;
				tmp->next->prev = list;
				delete tmp;
				size--;
				skip(flag,ct,tmp);
			}
		}
	}
}



/***************************************************************************************************/
/*End of your part																					*/
/***************************************************************************************************/

void DLL::printList() {
	DNode *tmp = first;
	while (tmp != NULL) {
		if(tmp->next == NULL){
			cout << tmp->data;
			tmp = tmp->next;
		}
		else{
			cout << tmp->data << ", ";
			tmp = tmp->next;
			}
	}
	cout << endl;
}
void DLL::printCode() {
	DNode *tmp = first;
	while (tmp != NULL) {
		cout << alpha[tmp->data];
		tmp = tmp->next;
	}
	cout << endl;
}
DLL::~DLL(){
	cout << "DLL Destructor begin" << endl;
	if(size == 0){
		cout << "DLL Empty!" << endl;
	}
	else if(size == 1){
		cout << "Size is 1" << endl;
		delete first;
	}
	else{
		cout << "Size is more than 1" << endl << "Size: ";
		DNode *tmp = first;
		DNode *tmp2 = first->next;
		while (tmp2 != NULL) {
			if(size > 1){
				cout<<size<<", ";
				delete tmp;
				size--;
				tmp = tmp2;
				tmp2 = tmp2->next;
			}
		}
		cout<<size<<endl;
		delete tmp2;
	}
	cout << "DLL Destroyed" << endl;
}
