#include <iostream>
#include<queue> 
#include <stdio.h>
#include "windows.h"
#include <conio.h>
using namespace std;

void gotoRowCol(int rpos, int cpos)

{

	int xpos = cpos, ypos = rpos;

	COORD scrn;



	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);



	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);

}
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void menu()
{
	gotoRowCol(1, 20);
	SetConsoleTextAttribute(console, 15);
	cout << "****************************************************************";
	gotoRowCol(2, 20);
	cout << "*";
	gotoRowCol(2, 83);
	cout << "*";
	SetConsoleTextAttribute(console, 12);
	gotoRowCol(2, 21);
	cout << "            RED ";
	SetConsoleTextAttribute(console, 8);
	cout << "             BLACK";
	SetConsoleTextAttribute(console, 10);
	cout << "             TREE";
	gotoRowCol(3, 20);
	SetConsoleTextAttribute(console, 15);
	cout << "****************************************************************";


}

class Red_Black_Tree
{
private:
	struct node
	{
		int data;
		bool color;//o red , 1 black
		node *left = NULL;
		node *right = NULL;
	};
	node *root = NULL;

	void Level_Traversal(node *rot)
	{
		if (rot == NULL)
		{
			return;
		}
		queue<node *> q;
		q.push(rot);

		while (!q.empty())
		{
			node *p = q.front();
			if (p->color == 0)
			{
				SetConsoleTextAttribute(console, 12);
				cout << p->data;
			}
			else
			{
				SetConsoleTextAttribute(console, 8);
				cout << p->data;
			}
			SetConsoleTextAttribute(console, 15);
			cout << " ";
			q.pop();

			if (p->left != NULL)
			{
				q.push(p->left);
			}
			if (p->right != NULL)
			{
				q.push(p->right);
			}
		}
	}

	void display(node *p)
	{
		if (p != NULL)
		{
			if (p->color == 0)
			{
				SetConsoleTextAttribute(console, 12);
				cout << p->data;
			}
			else
			{
				SetConsoleTextAttribute(console, 8);
				cout << p->data;
			}
			SetConsoleTextAttribute(console, 15);
			cout << " ";
		}
		if (p->right != NULL)
		{
			display(p->right);
		}
		if (p->left != NULL)
		{
			display(p->left);
		}
		if (p == NULL)
		{
			SetConsoleTextAttribute(console, 15);
			cout << " NO DATA ";
			delete p;
			return;
		}
	}

	bool search(int N, node *rot, node *&p)
	{
		if (rot != NULL)
		{
			if (rot->data == N)
			{
				p = rot;
				return 1;
			}
			else
			{
				if (rot->right != NULL)
				{
					search(N, rot->right, p);
				}
				if (rot->left != NULL)
				{
					search(N, rot->left, p);
				}
			}
		}
		else
		{
			delete p;
			return 0;
		}
	}
	int check_node_condition(node *p)
	{
		if ((p->left != NULL && p->right == NULL) || (p->left == NULL && p->right != NULL))
		{
			return 1;//one child
		}
		if (p->left != NULL && p->right != NULL)
		{
			return 2; //two child
		}
		if (p->left == NULL && p->right == NULL)
		{
			return 3;
		}
		return 0;
	}

	bool max_ID(node *&max, node *p)
	{
		if (p != NULL)
		{
			if (max->data < p->data)
			{
				max = p;
				return 1;
			}
			if (p->right != NULL)
			{
				max_ID(max, p->right);
			}
			if (p->left != NULL)
			{
				max_ID(max, p->left);
			}
		}
		else
		{
			delete p;
			return 0;
		}
	}


	void delete_leaf(node *&curr, node *&parent, node *&u, node *&v)
	{
		v->color = curr->color;
		if (parent->left == curr)
		{
			parent->left = NULL;
			curr = NULL;
			delete curr;
		}
		if (parent->right == curr)
		{
			parent->right = NULL;
			curr = NULL;
			delete curr;
		}
		u->color = 1;
		u->left = NULL; u->right = NULL; u->data = 0;
	}

	void delete_one_child(node *&curr, node *&parent, node *&u, node *&v)
	{
		node *t = NULL;
		v = curr;
		if (curr->right != NULL)
		{
			u = curr->right;
			if (curr == parent->right)
			{
				u = curr->right;
				//parent->right = curr->right;
				curr = curr->right;
				//t = curr->right;
			}

			if (curr == parent->left)
			{
				u = curr->right;
				//parent->left = curr->right;
				curr = curr->right;
				//t = curr->right;
			}
		}

		if (curr->left != NULL)
		{
			u = curr->left;
			if (curr == parent->left)
			{

				//parent->left = curr->left;
				curr = curr->left;
				parent->left = curr;
				//t = curr->left;
			}

			if (curr == parent->right)
			{
				curr = curr->left;
				parent->right = curr;
			}
		}

		//t = NULL;
		//delete curr;
		return;
	}

	void delete_two_child(node *&curr, node *&parent)
	{

		node *max = NULL, *pmax = NULL, *t = NULL, *t1 = curr->right, *t2 = NULL, *t3 = NULL;
		max->left = NULL, max->right = NULL, max->data = 0;

		if (t1->left == NULL && t1->right == NULL)
		{

			curr->data = t1->data;
			curr->color = t1->color;
			t = curr->right;
		}

		if (t1->left == NULL && t1->right != NULL)
		{
			curr->data = t1->data;
			curr->color = t1->color;
			curr->right = t1->right;
			t = t1->right;
		}

		if (t1->left != NULL && t1->right != NULL)
		{
			if (max_ID(max, t1->left))
			{
				if (search_parent(curr, root, pmax))
				{
					pmax->left = max->left;
					pmax->right = max->right;
					curr->data = max->data;
					curr->color = max->color;
				}
			}
			t = max->right;
		}
		t = NULL;
		delete curr;
		return;
	}

	bool search_G_parent(node *p, node *rot, node *&G_parent)
	{
		if (rot != NULL)
		{
			if (rot->left == p)
			{
				G_parent = rot;
				return 1;
			}
			else if (rot->right == p)
			{
				G_parent = rot;
				return 1;
			}
			else
			{
				if (rot->right != NULL)
				{
					search_G_parent(p, rot->right, G_parent);
				}
				if (rot->left != NULL)
				{
					search_G_parent(p, rot->left, G_parent);
				}
			}
		}
		else
		{
			delete rot;
			return 0;
		}
	}
	bool search_parent(node *p, node *rot, node *&parent)
	{
		if (rot != NULL)
		{
			if (rot->left == p)//|| rot->right ==p)
			{
				parent = rot;
				return 1;
			}
			else if (rot->right == p)
			{
				parent = rot;
				return 1;
			}
			else
			{
				if (rot->right != NULL)
				{
					search_parent(p, rot->right, parent);
				}
				if (rot->left != NULL)
				{
					search_parent(p, rot->left, parent);
				}
			}
		}
		else
		{
			delete rot;
			return 0;
		}
	}

	bool search_uncle(node *Gp, node *parent, node *&uncle)
	{
		if (Gp->left == parent && Gp->right != NULL)
		{
			uncle = Gp->right;
			return 1;
		}
		else if (Gp->right == parent && Gp->left != NULL)
		{
			uncle = Gp->left;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	bool straight_right_line(node *&G_parent, node *&parent, node *&uncle, node *&p)
	{
		if (parent->right != NULL && parent->right == p && p->left == NULL && p->right == NULL && G_parent->left == NULL && parent->left == NULL && G_parent->right == parent)
		{
			node *gp = new node;
			gp->left = NULL; gp->right = NULL; gp->color = 0; gp->data = G_parent->data;
			cout << G_parent->data << endl;
			cout << parent->data << endl;
			G_parent->left = gp;
			G_parent->right = p;
			G_parent->data = parent->data;
			G_parent->color = 1;
			parent->left = NULL; parent->right = NULL; delete parent;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	bool straight_left_line(node *&G_parent, node *&parent, node *&uncle, node *&p)
	{
		if (parent->left != NULL && parent->left == p && p->right == NULL && p->left == NULL && G_parent->right == NULL && parent->right == NULL && G_parent->left == parent)
		{
			node *gp = new node;
			gp->left = NULL; gp->right = NULL; gp->color = 0; gp->data = G_parent->data;
			G_parent->right = gp;
			G_parent->left = p;
			G_parent->data = parent->data;
			G_parent->color = 1;
			parent->left = NULL; parent->right = NULL; //delete parent;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	void u_p_both_red(node *&G_parent, node *&parent, node *&uncle, node *&p)
	{
		uncle->color = 1; parent->color = 1;
		if (G_parent != root)//no change in color if gp is root node
		{
			G_parent->color = 0;
			/*node *gp = NULL; node *pp = NULL; node *uu = NULL;
			if (search_parent(G_parent, root, pp))
			{
				while (search_G_parent(pp, root, gp) != 0 && gp != root)//reapeat above until gp not become root node
				{
					if (search_uncle(gp, pp, uu))
					{
						if (uu->color == 0 && pp->color != 1)
						{
							uu->color = 1; pp->color = 1;
						}
					}
				}
			}*/
		}
	}
	void Rotate_Right(node *&parent, node *&G_parent)
	{
		node *gp = new node;
		gp->left = G_parent->left; gp->right = G_parent->right; gp->color = G_parent->color; gp->data = G_parent->data;
		G_parent->left = parent->left;
		G_parent->data = parent->data;
		gp->left = parent->right;
		parent->data = gp->data; parent->left = gp->left; parent->right = gp->right; parent->color = gp->color;
		G_parent->right = parent;

		if (G_parent->color == 0)
		{
			G_parent->color = 1;
		}
		else
		{
			G_parent->color = 0;
		}
		if (parent->color == 0)
		{
			parent->color = 1;
		}
		else
		{
			parent->color = 0;
		}
	}

	void Rotate_Left_P_C(node *&parent, node *&G_parent, node *&p)
	{
		node *pp = new node;
		pp->right = parent->right; pp->left = parent->left; pp->data = parent->data; pp->color = parent->color;
		pp->left = p->left;
		parent->left = pp;
		parent->right = p->right;
		parent->data = p->data; parent->color = p->color;
	}

	void Rotate_right_P_C(node *&parent, node *&G_parent, node *&p)
	{
		node *pp = new node;
		pp->right = parent->right; pp->left = parent->left; pp->data = parent->data; pp->color = parent->color;
		pp->right = p->right;
		parent->right = pp;
		parent->left = p->left;
		parent->data = p->data; parent->color = p->color;
	}

	void Rotate_Left(node *&parent, node *&G_parent)
	{
		node *gp = new node;
		gp->left = G_parent->left; gp->right = G_parent->right; gp->color = G_parent->color; gp->data = G_parent->data;
		int g = G_parent->data;
		G_parent->right = parent->right;
		G_parent->data = parent->data;
		gp->right = parent->left;
		parent->data = gp->data; parent->left = gp->left; parent->right = gp->right; parent->color = gp->color;
		G_parent->left = parent;

		if (G_parent->color == 0)
		{
			G_parent->color = 1;
		}
		else
		{
			G_parent->color = 0;
		}
		if (parent->color == 0)
		{
			parent->color = 1;
		}
		else
		{
			parent->color = 0;
		}
	}

	void sort(node *root, node *p)
	{

		node *G_parent = NULL, *parent = NULL, *uncle = NULL;
		if (search_parent(p, root, parent))
		{
			if (parent != root)
			{
				if (search_G_parent(parent, root, G_parent))
				{
					//cout << G_parent->data << "g " << parent->data << "p " << endl;
					if (straight_right_line(G_parent, parent, uncle, p))// Gp,p and child are in straight right line
						return;

					if (straight_left_line(G_parent, parent, uncle, p))// Gp,p and child are in straight left line
						return;

					if (search_uncle(G_parent, parent, uncle) || !search_uncle(G_parent, parent, uncle))
					{
						//if uncle is red than do recoloring. 
						//if uncle is black than do rotataion.
						//cout << uncle->data << " r" << uncle->color << "U " << parent->color << "r ";
						if (uncle->color == 0 && parent->color == 0)//if uncle and parent both are in red color  
						{
							u_p_both_red(G_parent, parent, uncle, p);
							return;
						}
						if ((uncle->color == 1 && parent->color != 1) || uncle == NULL && parent->color != 1)//if uncle is black and parent in not black
						{
							if (G_parent->left == parent && parent->left == p)//left left case
							{
								Rotate_Right(parent, G_parent);//rotate right and also recolor p and gp||parent become G_parent and G_parent become right of parent
								return;
							}
							if (G_parent->left == parent && parent->right == p)//left right case
							{
								Rotate_Left_P_C(parent, G_parent, p);//rotate child and parent|| child become parent and parent become left of child
								Rotate_Right(parent, G_parent);//than rotate right and do recoloring
								return;
							}
							if (G_parent->right == parent && parent->right == p)//right right case
							{
								Rotate_Left(parent, G_parent);
								return;
							}
							if (G_parent->right == parent && parent->left == p)//right left case
							{
								Rotate_right_P_C(parent, G_parent, p);//rotate child and parent|| child become parent and parent become right of child
								Rotate_Left(parent, G_parent);//than rotate left and do recoloring
								return;
							}
						}

						//cout << G_parent->data << " " << parent->data << " " << uncle->data << endl;
						return;
					}
					else
					{



						return;
					}
				}
			}
		}
		return;
	}
	void s_child_both_red(node *&s, node *&r, node *parent)
	{
		if (s->left->color == 0)
		{
			r->color = s->left->color; r->left = s->left->left; r->right = s->left->right; r->data = s->left->data;
		}
		else
		{
			r->color = s->right->color; r->left = s->right->left; r->right = s->right->right; r->data = s->right->data;
		}
		if (parent->left == s && (r == s->left || (s->left->color == 0 && s->right->color == 0)))
		{//Left Left Case (s is left child of its parent and r is left child of s or both children of s are red)

			Rotate_Right(s, parent);
			return;
		}
		if (s == parent->left && r == s->right)//Left Right Case(s is left child of its parent and r is right child)
		{
			Rotate_Left_P_C(s, parent, r);
			Rotate_Right(s, parent);
			return;
		}
		if (s == parent->right && (r == s->right || (s->left->color == 0 && s->right->color == 0)))
		{//Right Right Case (s is right child of its parent and r is right child of s or both children of s are red)

			Rotate_Left(s, parent);
			return;
		}
		if (s == parent->right && r == s->left)//Right Left Case (s is right child of its parent and r is left child of s)
		{
			Rotate_right_P_C(s, parent, r);
			Rotate_Left(s, parent);
			return;
		}
	}
	void sort_After_deletion(node *&u, node *&v, node *&parent)
	{
		if (u->color == 0 || v->color == 0)
		{
			u->color = 1;
			return;
		}
		if (u == root)
		{
			u->color = 1;
		}
		if (u->color == 1 && v->color == 1)
		{
			if (u != root)
			{
				node *s = new node, *r = new node;
				if (u == parent->right)
				{
					s->color = parent->left->color; s->data = parent->left->data; s->left = parent->left->left; s->right = parent->left->right;
				}
				else
				{
					s->color = parent->right->color; s->data = parent->right->data; s->left = parent->right->left; s->right = parent->right->right;
				}
				//bool c1 = s->left->color, c2 = s->right->color;
				if (s->color == 1 && (s->left != NULL && s->right != NULL) && (s->left->color == 0 || s->right->color == 0) && s!=NULL)
				{//If sibling s is black and at least one of sibling’s children is red

					s_child_both_red(s, r, parent);
					return;
				}
				else if (s->color == 1 && ((s->left->color == 1 && s->right->color == 1) || (s->left == NULL && s->right == NULL)) && s != NULL)
				{//If sibling is black and its both children are black
					if (parent != 0)
					{
						s->color = 0;
					}
					else
					{
						parent->color = 1;
						s->color = 0;
					}
					return;
				}
				else if (s->color == 0 && s != NULL)
				{
					node *p = new node, *s1 = new node;
					if (s == parent->left)
					{

						Rotate_Right(s, parent);
						p = parent->left;
						if (parent->right == NULL)
						{
							s1->color = parent->left->color; s1->data = parent->left->data; s1->left = parent->left->left; s1->right = parent->left->right;
						}
						else
						{
							s1->color = parent->right->color; s1->data = parent->right->data; s1->left = parent->right->left; s1->right = parent->right->right;
						}
						s_child_both_red(s1, r, parent);
						return;
					}
					else if (s == parent->right && s != NULL)
					{
						Rotate_Left(s, parent);
						p = parent->right;
						if (parent->right == NULL)
						{
							s1->color = p->left->color; s1->data = p->left->data; s1->left = p->left->left; s1->right = p->left->right;
						}
						else
						{
							s1->color = p->right->color; s1->data = p->right->data; s1->left = p->right->left; s1->right = p->right->right;
						}
						s_child_both_red(s1, r, parent);
						return;
					}
				}

			}
		}
	}
public:

	void insert()
	{
		int N;
		cout << "Enter data that you want to insert: ";
		cin >> N;
		node *p = new node;
		p->data = N;
		p->color = 0;
		p->left = NULL;
		p->right = NULL;
		if (root == NULL)
		{
			p->color = 1;
			root = p;
		}
		else
		{
			node *parent = NULL;
			node *current = root;
			while (current)
			{
				parent = current;
				if (p->data > current->data)
				{
					current = current->right;
				}
				else if (p->data < current->data)
				{
					current = current->left;
				}
				else
				{
					break;
				}
			}
			if (p->data > parent->data)
			{
				parent->right = p;
			}
			else if (p->data < parent->data)
			{
				parent->left = p;
			}
			else
			{
				if (parent->right != NULL)
				{
					parent->right = p;
				}
				else
				{
					parent->left = p;
				}
			}
			//cout << endl;
			//main_display();
			//cout << endl;
			node *curr = NULL;
			if (search(N, root, curr))
			{
				sort(root, curr);
			}
			//sort(root, p);
		}
	}

	void Delete_Node()
	{
		int id;
		cout << "Enter ID you want to delete: ";
		cin >> id;
		node *curr = NULL, *parent = NULL; node *u = new node, *v = new node;
		if (search(id, root, curr))
		{
			if (curr == root && root->left == NULL && root->right == NULL)
			{
				root = NULL;
				return;
			}
			else if (search_parent(curr, root, parent))
			{
				if (check_node_condition(curr) == 1)//one child
				{
					delete_one_child(curr, parent, u, v);
					sort_After_deletion(u, v, parent);
				}
				/*else if (check_node_condition(curr) == 2)//two child
				{
				delete_two_child(curr, parent,u,v);
				}*/
				else if (check_node_condition(curr) == 3)//leaf
				{
					delete_leaf(curr, parent, u, v);
					sort_After_deletion(u, v, parent);
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}
	}

	void main_display()
	{
		display(root);
	}

	void display_level_traversal()
	{
		Level_Traversal(root);
	}

	void search_data(int x)
	{
		int n = 0;
		SetConsoleTextAttribute(console, 15);
		cout << "Enter data which you want to find: ";
		cin >> n;
		node *p;
		if (search(n, root, p))
		{
			gotoRowCol(x + 6, 49);
			cout << n;
			SetConsoleTextAttribute(console, 10);
			cout << " is present in TREE with color ";
			if (p->color == 0)
			{
				SetConsoleTextAttribute(console, 12);
				cout << " RED ";
			}
			else
			{
				SetConsoleTextAttribute(console, 8);
				cout << " BLACK ";
			}

		}
	}
};

int main()
{
	Red_Black_Tree rbt;
	int opt = 0;
	menu();
	gotoRowCol(6, 35);
	cout << "Enter 1 to INSERT data in TREE.";
	gotoRowCol(8, 35);
	cout << "Enter 2 to SEARCH DATA from TREE.";
	gotoRowCol(10, 35);
	cout << "Enter 3 to DELETE DATA from TREE.";
	gotoRowCol(12, 35);
	cout << "Enter 0 to EXIT your program..";
	int i = 0; int m = 14;
	while (1)
	{
		int x = m + i;
		SetConsoleTextAttribute(console, 15);
		gotoRowCol(x + 1, 28);
		cout << "*************************************************";
		gotoRowCol(x + 2, 40);
		cout << "Enter your choice: ";
		cin >> opt;
		if (opt == 0)
		{
			break;
		}
		else if (opt == 1)
		{
			gotoRowCol(x + 4, 35);
			rbt.insert();
			gotoRowCol(x + 6, 49);
			SetConsoleTextAttribute(console, 10);
			cout << "TREE";
			gotoRowCol(x + 7, 35);
			SetConsoleTextAttribute(console, 15);
			cout << "In order Traversal: ";
			rbt.main_display();
			gotoRowCol(x + 8, 35);
			cout << "Level Order Traversal: ";
			rbt.main_display();
			i = i + 8;
		}
		else if (opt == 2)
		{
			gotoRowCol(x + 4, 35);
			rbt.search_data(x);
			i = i + 8;
		}
		else if (opt == 3)
		{
			gotoRowCol(x + 4, 35);
			rbt.Delete_Node();
			gotoRowCol(x + 6, 49);
			SetConsoleTextAttribute(console, 10);
			cout << "TREE";
			gotoRowCol(x + 7, 30);
			SetConsoleTextAttribute(console, 15);
			cout << "In order Traversal: ";
			rbt.main_display();
			gotoRowCol(x + 8, 28);
			cout << "Level Order Traversal: ";
			rbt.main_display();
			i = i + 8;
		}
		else
		{
			cout << "WRONG CHOICE";
			i = i + 2;
		}

	}
	cout << endl;
	return 0;
}