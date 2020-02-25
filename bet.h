#ifndef BET_H
#define BET_H

#include <iostream>
#include <list>
#include <stack>
#include "token.h"

template <typename T>
class BET{
	public:
		BET();					//default
		BET(const list<Token> & postfix);	//one parameter constructor
		BET(const BET& rhs);			//copy constructor
		~BET();					//destructor
		bool buildFromPostfix(const list<Token> & postfix); //if the tree is populated clear the tree, build the tree with the postfix expression in the list
		const BET & operator= (const BET & rhs);//assignment operator
		void printInfixExpression();		//prints the infix expression, should be done by recursion
		void printPostfixExpression();		//prints postfix expression using recusion
		size_t size();				//returns the number of nodes in the tree, recursion
		size_t leaf_nodes();			//returns the numebr of leafe nodes, recursion
		bool empty();				//returns true if empty, false elsewise

	private:
		struct BinaryNode{
			T element;
			BinaryNode *left;
			BinaryNode *right;

			BinaryNode(const T &theElement, BinaryNode *lt, BinaryNode *rt)
				: element{theElement}, left{lt}, right{rt} {}    
			BinaryNode(T && theElement, BinaryNode *lt, BinaryNode *rt)
				: element{std::move(theElement)}, left{lt}, right{rt} {}
		};
		BinaryNode *root;
		stack<BinaryNode*> tree;
		void printInfixExpression(BinaryNode *n);//print the infix expresion 
		void makeEmpty(BinaryNode* &t); 	//delete the nodes in the subtree
		BinaryNode * clone(BinaryNode *t);	//clone nodes in subtree, can be called by operator=
		void printPostfixExpression(BinaryNode *n);//print to standard output the post fix expression
		size_t size(BinaryNode *t);		//return the number of nodes in the subtree
		size_t leaf_nodes(BinaryNode *t);	//retrun the number of leaf nodes

};

#include "bet.hpp"

#endif
