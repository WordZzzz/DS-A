#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct BinaryTreeNode {
	int val;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*	
 *	反序列化二叉树辅助函数
 *	参数：
 *		str：前序遍历的字符串
 *	返回值：
 *		ret：当前根节点
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


/*	
 *	反序列化二叉树：string --》 BinaryTreeNode
 *	参数：
 *		str：前序遍历的字符串，e.g:"1, 2, $, $, 3, $, $,"
 *	返回值：
 *		deserializeHelper(str)：生成树的根节点
 */
BinaryTreeNode* Deserialize(string str)
{
	if (str == "")
		return NULL;
	return deserializeHelper(str);
}

/*	
 *	序列化二叉树辅助函数
 *	参数：
 *		node：树的根节点
 *		str：前序遍历后字符串
 *	返回值：
 *		
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

/*	
 *	序列化二叉树：BinaryTreeNode --》 string
 *	参数：
 *		pRoot：树的根节点
 *	返回值：
 *		ret：前序遍历后的字符串
 */
char* Serialize(BinaryTreeNode *pRoot)
{
	if (pRoot == NULL)
		return NULL;
	string s = "";
	serializeHelper(pRoot, s);

	char *ret = new char[s.length() + 1];
	strcpy_s(ret, strlen(s.c_str()) + 1, s.c_str());
	return ret;
}

/*	
 *	打印二叉树辅助函数
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

/*	
 *	打印二叉树函数
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

/*	
 *	销毁二叉树函数
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

/*	
 *	递归前序遍历
 */
void preOrder1(BinaryTreeNode *pRoot) 
{
	if (pRoot != NULL)
	{
		cout << pRoot->val << " ";
		preOrder1(pRoot->left);
		preOrder1(pRoot->right);
	}
}

/*	
 *	非递归前序遍历
 */
void preOrder2(BinaryTreeNode *pRoot)
{
	stack<BinaryTreeNode *> s;
	BinaryTreeNode *p = pRoot;
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

/*	
 *	递归中序遍历
 */
void inOrder1(BinaryTreeNode *pRoot)
{
	if (pRoot != NULL)
	{
		inOrder1(pRoot->left);
		cout << pRoot->val << " ";
		inOrder1(pRoot->right);
	}
}

/*	
 *	非递归中序遍历
 */
void inOrder2(BinaryTreeNode *pRoot)
{
	stack<BinaryTreeNode *> s;
	BinaryTreeNode *p = pRoot;
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

/*	
 *	递归后序遍历
 */
void postOrder1(BinaryTreeNode *pRoot)
{
	if (pRoot != NULL)
	{
		postOrder1(pRoot->left);
		postOrder1(pRoot->right);
		cout << pRoot->val << " ";
	}
}

/*	
 *	非递归后序遍历
 */
void postOrder2(BinaryTreeNode *pRoot)
{
	stack<BinaryTreeNode *> s;
	BinaryTreeNode *cur;					//当前结点 
	BinaryTreeNode *pre = NULL;				//前一次访问的结点 
	s.push(pRoot);
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

/*	
 *	递归求二叉树镜像
 */
void getMirror1(BinaryTreeNode *pRoot)
{
	if (pRoot){
		swap(pRoot->left, pRoot->right);
		getMirror1(pRoot->left);
		getMirror1(pRoot->right);
	}
}

/*	
 *	层序遍历求递归镜像
 */
void getMirror2(BinaryTreeNode *pRoot)
{
	if (!pRoot) return;
	BinaryTreeNode* node;
	queue<BinaryTreeNode *> que;
	que.push(pRoot);
	while (!que.empty()){
		node = que.front();
		que.pop();
		swap(node->left, node->right);
		if (node->left) que.push(node->left);
		if (node->right) que.push(node->right);
	}
}

/*	
 *	递归求二叉树深度
 */
int getTreeDepth1(BinaryTreeNode* pRoot)
{
	if (!pRoot)
		return 0;
	return max(getTreeDepth1(pRoot->left), getTreeDepth1(pRoot->right)) + 1;
}

/*	
 *	层序遍历求二叉树深度
 */
int getTreeDepth2(BinaryTreeNode* pRoot)
{
	if (!pRoot) return 0;
	queue<BinaryTreeNode *> que;
	int depth = 0;
	que.push(pRoot);
	while (!que.empty()){
		int size = que.size();
		depth++;
		for (int i = 0; i < size; i++){
			BinaryTreeNode* node = que.front();
			que.pop();
			if (node->left) que.push(node->left);
			if (node->right) que.push(node->right);
		}
	}
	return depth;
}

/*	
 *	判断是否为平衡二叉树辅助函数
 *	参数：
 *		pRoot：当前根节点
 *		depth：当前深度
 *	返回值：
 *		true or false
 */
int isBalanced(BinaryTreeNode* pRoot, int* depth)
{
	if (pRoot == NULL){
		*depth = 0;
		return true;
	}
	int left, right;
	if (isBalanced(pRoot->left, &left) && isBalanced(pRoot->right, &right)){
		int diff = left - right;
		if (diff <= 1 && diff >= -1){
			*depth = 1 + (left > right ? left : right);
			return true;
		}
	}
	return false;
}

/*	
 *	判断是否为平衡二叉树函数
 *	参数：
 *		pRoot：树的根节点
 *	返回值：
 *		isBalanced(pRoot, &depth)：true or false
 */
bool isBalanced_Solution(BinaryTreeNode* pRoot) 
{
	int depth = 0;
	return isBalanced(pRoot, &depth);
}

/*	
 *	判断是否为对称二叉树辅助函数
 *	参数：
 *		pRoot1：当前根节点
 *		pRoot2：复制的根节点
 *	返回值：
 *		true or false
 */
bool isSymmetricalCore(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot1 == NULL && pRoot2 == NULL)
		return true;
	if (pRoot1 == NULL || pRoot2 == NULL)
		return false;
	if (pRoot1->val != pRoot2->val)
		return false;
	return isSymmetricalCore(pRoot1->left, pRoot2->right)
		&& isSymmetricalCore(pRoot1->right, pRoot2->left);
}

/*	
 *	判断是否为对称二叉树函数
 *	参数：
 *		pRoot：根节点
 *	返回值：
 *		true or false
 */
bool isSymmetrical(BinaryTreeNode* pRoot)
{
	return isSymmetricalCore(pRoot, pRoot);
}


/*	
 *	多行打印二叉树函数
 *	参数：
 *		pRoot：根节点
 *	返回值：
 *		ret：需要打印的vector
 */
vector<vector<int> > Print1(BinaryTreeNode* pRoot) {
	vector<vector<int> > ret;
	queue<BinaryTreeNode*> que;
	if (pRoot) que.push(pRoot);
	while (!que.empty()){
		vector<int> tmp;
		int n = que.size();
		while (n--){
			BinaryTreeNode* node = que.front();
			tmp.push_back(node->val);
			if (node->left) que.push(node->left);
			if (node->right) que.push(node->right);
			que.pop();
		}
		ret.push_back(tmp);
	}
	return ret;
}

/*	
 *	按之字形顺序打印二叉树函数
 *	参数：
 *		pRoot：根节点
 *	返回值：
 *		ret：需要打印的vector
 */
vector<vector<int> > Print2(BinaryTreeNode* pRoot) 
{
	vector<vector<int>> ret;
	if (pRoot == NULL) return ret;
	stack<BinaryTreeNode*> s1;
	stack<BinaryTreeNode*> s2;
	s1.push(pRoot);
	while (!s1.empty() || !s2.empty()){
		vector<int> v1;
		vector<int> v2;
		while (!s1.empty()){
			v1.push_back(s1.top()->val);
			if (s1.top()->left != NULL) s2.push(s1.top()->left);
			if (s1.top()->right != NULL) s2.push(s1.top()->right);
			s1.pop();
		}
		if (v1.size() != 0)
			ret.push_back(v1);
		while (!s2.empty()){
			v2.push_back(s2.top()->val);
			if (s2.top()->right != NULL)   s1.push(s2.top()->right);
			if (s2.top()->left != NULL)  s1.push(s2.top()->left);
			s2.pop();
		}
		if (v2.size() != 0)
			ret.push_back(v2);
	}
	return ret;
}

/*	
 *	二叉树的第k大的结点辅助函数
 *	参数：
 *		pRoot：根节点
 *		k：需要找的第k大
 *	返回值：
 *		target：第k大结点
 */
BinaryTreeNode* KthNodeCore(BinaryTreeNode* pRoot, int &k){
	BinaryTreeNode* target = NULL;
	if (pRoot->left != NULL)
		target = KthNodeCore(pRoot->left, k);
	if (target == NULL){
		if (k == 1)
			target = pRoot;
		k--;
	}
	if (target == NULL && pRoot->right != NULL)
		target = KthNodeCore(pRoot->right, k);
	return target;
}

/*	
 *	二叉树的第k大的结点函数
 *	参数：
 *		pRoot：根节点
 *		k：需要找的第k大
 *	返回值：
 *		KthNodeCore(pRoot, k)：第k大结点
 */
BinaryTreeNode* KthNode(BinaryTreeNode* pRoot, int k)
{
	if (pRoot == NULL || k < 1)
		return NULL;
	return KthNodeCore(pRoot, k);
}

/*	
 *	二叉搜索树转换成双向链表辅助函数
 *	参数：
 *		pNode：根节点
 *		pLastNodeInList：双向链表头节点
 *	返回值：
 *
 */
void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList){
	if (pNode == NULL)
		return;

	BinaryTreeNode* pCurrent = pNode;
	//递归左子树
	if (pCurrent->left != NULL)
		ConvertNode(pCurrent->left, pLastNodeInList);
	//处理指针
	pCurrent->left = *pLastNodeInList;
	if (*pLastNodeInList != NULL)
		(*pLastNodeInList)->right = pCurrent;
	*pLastNodeInList = pCurrent;
	//递归右子树
	if (pCurrent->right != NULL)
		ConvertNode(pCurrent->right, pLastNodeInList);
}

/*	
 *	二叉搜索树转换成双向链表
 *	参数：
 *		pRootOfTree：根节点
 *	返回值：
 *		pHeadOfList：双向链表头节点
 */
BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree)
{
	BinaryTreeNode *pLastNodeInList = NULL;
	ConvertNode(pRootOfTree, &pLastNodeInList);

	//需要返回头结点，所以需要遍历到头结点（最左子叶）
	BinaryTreeNode *pHeadOfList = pLastNodeInList;
	while (pHeadOfList != NULL && pHeadOfList->left != NULL)
		pHeadOfList = pHeadOfList->left;
	return pHeadOfList;
}

int main(int argc, char *argv[])
{
	string str;
	cin >> str;
	BinaryTreeNode *pRoot = Deserialize(str);
	PrintTree(pRoot);

	preOrder1(pRoot);
	cout << endl;
	preOrder2(pRoot);
	cout << endl;
	inOrder1(pRoot);
	cout << endl;
	inOrder2(pRoot);
	cout << endl; 
	postOrder1(pRoot);
	cout << endl; 
	postOrder2(pRoot);
	cout << endl;

	return 0;
}
