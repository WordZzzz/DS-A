#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

struct BinaryTreeNode {
	int val;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*	反序列化二叉树辅助函数
	参数：
		str：前序遍历的字符串
	返回值：
		ret：当前根节点
	*/
BinaryTreeNode *deserializeHelper(string &s)
{
	if (s.empty())
		return NULL;
	if (s[0] == '$')
	{
		s = s.substr(2);
		return NULL;
	}
	BinaryTreeNode *ret = new BinaryTreeNode(stoi(s));
	s = s.substr(s.find_first_of(',') + 1);
	ret->left = deserializeHelper(s);
	ret->right = deserializeHelper(s);
	return ret;
}


/*	反序列化二叉树：string --》 BinaryTreeNode
	参数：
		str：前序遍历的字符串，e.g:"1, 2, $, $, 3, $, $,"
	返回值：
		deserializeHelper(str)：生成树的根节点
	*/
BinaryTreeNode* Deserialize(string str)
{
	if (str == "")
		return NULL;
	return deserializeHelper(str);
}

/*	反序列化二叉树辅助函数
	参数：
		node：树的根节点
		str：前序遍历后字符串
	返回值：
		
	*/
void serializeHelper(BinaryTreeNode *node, string& str)
{
	if (node == NULL)
	{
		str.push_back('$');
		str.push_back(',');
		return;
	}
	str += to_string(node->val);
	str.push_back(',');
	serializeHelper(node->left, str);
	serializeHelper(node->right, str);
}

/*	反序列化二叉树：BinaryTreeNode --》 string
	参数：
		root：树的根节点
	返回值：
		ret：前序遍历后的字符串
	*/
char* Serialize(BinaryTreeNode *root)
{
	if (root == NULL)
		return NULL;
	string s = "";
	serializeHelper(root, s);

	char *ret = new char[s.length() + 1];
	strcpy_s(ret, strlen(s.c_str()) + 1, s.c_str());
	return ret;
}

/*	打印二叉树辅助函数
	*/
void PrintTreeNode(BinaryTreeNode* pNode)
{
	if (pNode != nullptr)
	{
		printf("value of this node is: %d\n", pNode->val);

		if (pNode->left != nullptr)
			printf("value of its left child is: %d.\n", pNode->left->val);
		else
			printf("left child is null.\n");

		if (pNode->right != nullptr)
			printf("value of its right child is: %d.\n", pNode->right->val);
		else
			printf("right child is null.\n");
	}
	else
	{
		printf("this node is null.\n");
	}

	printf("\n");
}

/*	打印二叉树函数
	*/
void PrintTree(BinaryTreeNode* pRoot)
{
	PrintTreeNode(pRoot);

	if (pRoot != nullptr)
	{
		if (pRoot->left != nullptr)
			PrintTree(pRoot->left);

		if (pRoot->right != nullptr)
			PrintTree(pRoot->right);
	}
}

/*	销毁二叉树函数
	*/
void DestroyTree(BinaryTreeNode* pRoot)
{
	if (pRoot != nullptr)
	{
		BinaryTreeNode* pLeft = pRoot->left;
		BinaryTreeNode* pRight = pRoot->right;

		delete pRoot;
		pRoot = nullptr;

		DestroyTree(pLeft);
		DestroyTree(pRight);
	}
}

void preOrder1(BinaryTreeNode *root)     //递归前序遍历 
{
	if (root != NULL)
	{
		cout << root->val << " ";
		preOrder1(root->left);
		preOrder1(root->right);
	}
}

void inOrder1(BinaryTreeNode *root)      //递归中序遍历
{
	if (root != NULL)
	{
		inOrder1(root->left);
		cout << root->val << " ";
		inOrder1(root->right);
	}
}

void postOrder1(BinaryTreeNode *root)    //递归后序遍历
{
	if (root != NULL)
	{
		postOrder1(root->left);
		postOrder1(root->right);
		cout << root->val << " ";
	}
}

void preOrder2(BinaryTreeNode *root)     //非递归前序遍历 
{
	stack<BinaryTreeNode *> s;
	BinaryTreeNode *p = root;
	while (p != NULL || !s.empty())
	{
		while (p != NULL)
		{
			cout << p->val << " ";
			s.push(p);
			p = p->left;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->right;
		}
	}
}

void inOrder2(BinaryTreeNode *root)      //非递归中序遍历
{
	stack<BinaryTreeNode *> s;
	BinaryTreeNode *p = root;
	while (p != NULL || !s.empty())
	{
		while (p != NULL)
		{
			s.push(p);
			p = p->left;
		}
		if (!s.empty())
		{
			p = s.top();
			cout << p->val << " ";
			s.pop();
			p = p->right;
		}
	}
}

void postOrder2(BinaryTreeNode *root)	//非递归后序遍历
{
	stack<BinaryTreeNode *> s;
	BinaryTreeNode *cur;                //当前结点 
	BinaryTreeNode *pre = NULL;         //前一次访问的结点 
	s.push(root);
	while (!s.empty())
	{
		cur = s.top();
		if ((cur->left == NULL && cur->right == NULL) ||
			(pre != NULL && (pre == cur->left || pre == cur->right)))
		{
			cout << cur->val << " ";  //如果当前结点没有孩子结点或者孩子节点都已被访问过 
			s.pop();
			pre = cur;
		}
		else
		{
			if (cur->right != NULL)
				s.push(cur->right);
			if (cur->left != NULL)
				s.push(cur->left);
		}
	}
}


int main(int argc, char *argv[])
{
	string str;
	cin >> str;
	BinaryTreeNode *root = Deserialize(str);
	PrintTree(root);

	preOrder1(root);
	preOrder2(root);
	inOrder1(root);
	inOrder2(root);
	postOrder1(root);
	postOrder2(root);

	return 0;
}
