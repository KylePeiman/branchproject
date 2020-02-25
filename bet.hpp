#include <iostream>
#include <list>
#include <stack>
#include "token.h"

using namespace std;

template <typename T>
BET<T>::BET()
{
	root = NULL;
}

template <typename T>
BET<T>::BET(const list<Token> &postfix)
{
 	int operand = 0;
        int Operator = 0;
        makeEmpty(root);
        for( auto i = postfix.begin( ); i != postfix.end( ); i++){
                if((*i).getValue() == "+" || (*i).getValue() == "-" || (*i).getValue() == "*" || (*i).getValue() == "/"){
                        BinaryNode* t1 = tree.top();
                        tree.pop();
                        BinaryNode* t2 = tree.top();
                        tree.pop();
                        Token s((*i).getValue(), (*i).getType());
                        BinaryNode *temp = new BinaryNode{s,t1,t2};
                        tree.push(temp);
                        Operator++;
                }
                else{
                        Token s((*i).getValue(), (*i).getType());
                        BinaryNode *temp = new BinaryNode{s,nullptr,nullptr};
                        tree.push(temp);
                        operand++;
                }
        }
        root = tree.top();
        tree.pop();
}

template <typename T>
BET<T>::BET(const BET& rhs) : root{ nullptr }
{
	root = clone(rhs.root);
}

template <typename T>
BET<T>::~BET()
{
	makeEmpty(root);
}

template <typename T>
bool BET<T>::buildFromPostfix(const list<Token> & postfix)
{
	int operand = 0;
	int Operator = 0;
	makeEmpty(root);
	for( auto i = postfix.begin( ); i != postfix.end( ); i++){
        	if((*i).getValue() == "+" || (*i).getValue() == "-" || (*i).getValue() == "*" || (*i).getValue() == "/"){
			BinaryNode* t1 = tree.top();
			tree.pop();
			BinaryNode* t2 = tree.top();
			tree.pop();
			Token s((*i).getValue(), (*i).getType());
			BinaryNode *temp = new BinaryNode{s,t1,t2};
			tree.push(temp);
			Operator++;
		}
                else{
			Token s((*i).getValue(), (*i).getType());
			BinaryNode *temp = new BinaryNode{s,nullptr,nullptr};
			tree.push(temp);
			operand++;
		}
        }
	root = tree.top();
	tree.pop();
	if(Operator > (operand-1)){
		cout << "error occured - abort" << endl;
		return false; 
	}
	else
		return true;
}

template <typename T>
const BET<T>& BET<T>::operator=(const BET &rhs)
{
	makeEmpty(root);
	root = clone(rhs.root);
	return *this;
}

template <typename T>
void BET<T>::printInfixExpression()
{
	printInfixExpression(root);
}

template <typename T>
void BET<T>::printPostfixExpression()
{
	printPostfixExpression(root);
}

template <typename T>
size_t BET<T>::size()
{
	return size(root);
}

template <typename T>
size_t BET<T>::leaf_nodes()
{
	return leaf_nodes(root);
}

template <typename T>
bool BET<T>::empty()
{
	if(root->right == nullptr && root->left == nullptr)
		return true;
	else
		return false;
}

template <typename T>
void BET<T>::printInfixExpression(BinaryNode *n)
{
	if(n)
	{
		printInfixExpression( n-> right );
		cout << n->element.getValue() << " ";
		printInfixExpression( n->left );
	}
}

template <typename T>
void BET<T>::printPostfixExpression(BinaryNode *n)
{
	if(n)
	{
		printPostfixExpression( n->right );
		printPostfixExpression( n->left );
		cout << n->element.getValue() << " ";
	}
}

template <typename T>
void BET<T>::makeEmpty(BinaryNode * &t)
{
	if(t != nullptr)
	{
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	t = nullptr;
}

template <typename T>
typename BET<T>::BinaryNode * BET<T>::clone(BinaryNode *t)
{
	if( t == nullptr )
		return nullptr;
	else
		return new BinaryNode( t->element, clone(t->left), clone(t->right));
}

template <typename T>
size_t BET<T>::size(BinaryNode *t)
{
	if(t == nullptr)
		return 0;
	else
		return (size(t->left) + 1 + size(t->right));
}

template <typename T>
size_t BET<T>::leaf_nodes(BinaryNode *t)
{
	if(t->left == nullptr && t->right == nullptr)
		return 1;
	else
		return leaf_nodes(t->left) + leaf_nodes(t->right);
}
