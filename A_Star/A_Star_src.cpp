#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

const int ROW = 3;
const int COL = 3;
const int MAXDISTANCE = 10000;
const int MAXNUM = 10000;

typedef struct _Node {
	int digit[ROW][COL];
	int dist;   // h(n)
	int dep;    // g(n)
	int index; // 父节点标记
} Node;
Node src, dest;

vector<Node> node_v;   // open表


//是否有解
bool is_access(int cur[], int aim[]) {
	int inver_count1 = 0;
	for (int i = 0; i < ROW*COL-1; i++) {
		//忽略0
		if (cur[i] == 0) {
			continue;
		}
		int temp = cur[i];
		for (int j = i + 1; j < ROW * COL; j++) {
			//忽略0
			if (cur[j] == 0) {
				continue;
			}
			if (temp > cur[j]) {
				inver_count1++;
			}
		}
	}
	cout << inver_count1 << endl;
	int inver_count2 = 0;
	for (int i = 0; i < ROW * COL-1; i++) {
		if (aim[i] == 0) {
			continue;
		}
		int temp = aim[i];
		for (int j = i + 1; j < ROW * COL; j++) {
			if (aim[j] == 0) {
				continue;
			}
			if (temp > aim[j]) {
				inver_count2++;
			}
		}
	}
	cout << inver_count2 << endl;
	if ((inver_count1 + inver_count2) % 2 == 0) {
		return true;
	}
	else {
		return false;
	}
}

//两节点是否相同
bool is_equal(int index, int digit[][COL]) {
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++) {
			if (node_v[index].digit[i][j] != digit[i][j])
				return false;
		}
	return true;
}

//重写输出流，每次按格式输出
ostream& operator<<(ostream& os, Node& node) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++)
			os << node.digit[i][j] << ' ';
		os << endl;
	}
	return os;
}

//打印每次移动结果
int PrintSteps(int index, vector<Node>& rstep_v) {
	rstep_v.push_back(node_v[index]);
	index = node_v[index].index;
	while (index != 0) {
		rstep_v.push_back(node_v[index]);
		index = node_v[index].index;
	}
	int count = 0;
	for (int i = rstep_v.size() - 1; i >= 0; i--) {
		cout << "Step " << rstep_v.size() - i
			<< endl << rstep_v[i] << endl;
		count++;
	}
	return count;		
}

//交换函数
void Swap(int& a, int& b) {
	int t;
	t = a;
	a = b;
	b = t;
}

//节点赋值
void Assign(Node& node, int index) {
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			node.digit[i][j] = node_v[index].digit[i][j];
}

//获取open表中估价最小的节点
int GetMinNode() {
	int dist = MAXNUM;
	int pos; //最小节点在数组中的位置
	for (int i = 0; i < node_v.size(); i++) {
		if (node_v[i].dist == MAXNUM)
			continue;
		else if ((node_v[i].dist + node_v[i].dep) < dist) {
			pos = i;
			dist = node_v[i].dist + node_v[i].dep;
		}
	}
	return pos;
}

//是否为可扩充节点
bool is_expandable(Node& node) {
	for (int i = 0; i < node_v.size(); i++) {
		if (is_equal(i, node.digit))
			return false;
	}
	return true;
}

//曼哈顿距离计算h(n)
int Distance(Node& node, int digit[][COL]) {
	int distance = 0;
	bool flag = false;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			for (int k = 0; k < ROW; k++) {
				for (int l = 0; l < COL; l++) {
					if (node.digit[i][j] == digit[k][l]) {
						distance += abs(i - k) + abs(j - l);
						flag = true;
						break;
					}
					else
						flag = false;
				}
				if (flag)
					break;
			}
	return distance;
}

int MinDistance(int a, int b) {
	return (a < b ? a : b);
}


void ProcessNode(int index) {
	int x, y;
	bool flag;
	//查找空位
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (node_v[index].digit[i][j] == 0) {
				x = i; y = j;
				flag = true;
				break;
			}
			else flag = false;
		}
		if (flag)
			break;
	}
	//向上移动的子节点进入open表
	Node node_up;
	Assign(node_up, index);
	int dist_up = MAXDISTANCE;
	if (x > 0) {
		Swap(node_up.digit[x][y], node_up.digit[x - 1][y]);
		if (is_expandable(node_up)) {
			dist_up = Distance(node_up, dest.digit);
			node_up.index = index;
			node_up.dist = dist_up;
			node_up.dep = node_v[index].dep + 1;
			node_v.push_back(node_up);
		}
	}
	//向下移动的子节点进入open表
	Node node_down;
	Assign(node_down, index);
	int dist_down = MAXDISTANCE;
	if (x < 2) {
		Swap(node_down.digit[x][y], node_down.digit[x + 1][y]);
		if (is_expandable(node_down)) {
			dist_down = Distance(node_down, dest.digit);
			node_down.index = index;
			node_down.dist = dist_down;
			node_down.dep = node_v[index].dep + 1;
			node_v.push_back(node_down);
		}
	}
	//向左移动的子节点进入open表
	Node node_left;
	Assign(node_left, index);
	int dist_left = MAXDISTANCE;
	if (y > 0) {
		Swap(node_left.digit[x][y], node_left.digit[x][y - 1]);
		if (is_expandable(node_left)) {
			dist_left = Distance(node_left, dest.digit);
			node_left.index = index;
			node_left.dist = dist_left;
			node_left.dep = node_v[index].dep + 1;
			node_v.push_back(node_left);
		}
	}
	//向右移动的子节点进入open表
	Node node_right;
	Assign(node_right, index);
	int dist_right = MAXDISTANCE;
	if (y < 2) {
		Swap(node_right.digit[x][y], node_right.digit[x][y + 1]);
		if (is_expandable(node_right)) {
			dist_right = Distance(node_right, dest.digit);
			node_right.index = index;
			node_right.dist = dist_right;
			node_right.dep = node_v[index].dep + 1;
			node_v.push_back(node_right);
		}
	}
	//index节点进入close表
	node_v[index].dist = MAXNUM;
}

int main() {
	int number;
	int* _src = new int[ROW * COL];
	int* _dest = new int[ROW * COL];
	cout << "Input source:" << endl;
	int k = 0;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++) {
			cin >> number;
			src.digit[i][j] = number;
			_src[k] = number;
			k++;
		}
	src.index = 0;
	src.dep = 1;

	k = 0;
	cout << "Input destination:" << endl;
	for (int m = 0; m < ROW; m++)
		for (int n = 0; n < COL; n++) {
			cin >> number;
			dest.digit[m][n] = number;
			_dest[k] = number;
			k++;
		}

	node_v.push_back(src);
	int tag = 0;
	//定时器
	clock_t start = clock();
	if (!is_access(_src, _dest)) {
		cout << "No Solution!" << endl;
		return -1;
	}
	else {
		while (1) {
			int pos;   //最小节点的数组下标
			pos = GetMinNode();
			cout << node_v[pos] << "   " << ++tag << endl;
			if (is_equal(pos, dest.digit)) {
				vector<Node> rstep_v;
				cout << "Source:" << endl;
				cout << src << endl;
				int count = PrintSteps(pos, rstep_v);
				cout << "Successful!" << endl;
				cout << "Using " << (clock() - start) / CLOCKS_PER_SEC
					<< " seconds and " << count << "steps." << endl;
				break;
			}
			else
				ProcessNode(pos);
		}
	}
	
	return 0;
}