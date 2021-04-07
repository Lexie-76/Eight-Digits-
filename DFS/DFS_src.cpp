#include <iostream>
#include <ctime>
#include <stack>
#include <vector>
using namespace std;

const int ROW = 3;
const int COL = 3;

int tag = 0;
typedef struct _Node {
	int digit[ROW][COL];
	int self;//��ǰ���
	int depth;//���
	bool visit = false;//�Ƿ��Ѿ�������
	int index; // ���ڵ���

} Node;
Node src, dest;

stack<Node> node_s;   // �洢�ڵ�
vector<Node> node_v;

//�Ƿ��н�
bool is_access(int cur[], int aim[]) {
	int inver_count1 = 0;
	for (int i = 0; i < ROW * COL - 1; i++) {
		//����0
		if (cur[i] == 0) {
			continue;
		}
		int temp = cur[i];
		for (int j = i + 1; j < ROW * COL; j++) {
			//����0
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
	for (int i = 0; i < ROW * COL - 1; i++) {
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

//���ڵ��Ƿ���ͬ
bool is_equal(int node_digit[][COL], int digit[][COL]) {
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++) {
			if (node_digit[i][j] != digit[i][j])
				return false;
		}
	return true;
}

//��д�������ÿ�ΰ���ʽ���
ostream& operator<<(ostream& os, Node& node) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++)
			os << node.digit[i][j] << ' ';
		os << endl;
	}
	return os;
}

//��ӡÿ���ƶ����
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

//��������
void Swap(int& a, int& b) {
	int t;
	t = a;
	a = b;
	b = t;
}

//�ڵ㸳ֵ
void Assign(Node& node1, Node& node2 ) {
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			node1.digit[i][j] = node2.digit[i][j];
}


//�Ƿ�Ϊ������ڵ�
bool is_expandable(Node& node) {
	for (int i = 0; i < node_v.size(); i++) {
		if (is_equal(node_v[i].digit, node.digit))
			return false;
	}
	return true;
}

int ProcessNode(int index) {
	Node node_parent = node_s.top();
	int x, y;
	bool flag;
	//���ҿ�λ
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (node_parent.digit[i][j] == 0) {
				x = i; y = j;
				flag = true;
				break;
			}
			else flag = false;
		}
		if (flag)
			break;
	}
	
	//�����ƶ����ӽڵ�
	Node node_up;
	Assign(node_up, node_parent);
	if (x > 0) {
		Swap(node_up.digit[x][y], node_up.digit[x - 1][y]);
		if (is_expandable(node_up)) {
			node_up.index = index;
			node_up.self = node_v.size();
			node_up.depth = node_v[index].depth + 1;
			node_v.push_back(node_up);
			node_s.push(node_up);
			cout << node_up << "   " << ++tag << endl;
			if (is_equal(node_up.digit, dest.digit)) {
				return node_v.size()-1;
			}
			cout << "up false" << endl;
		}
	}
	//�����ƶ����ӽڵ�
	Node node_down;
	Assign(node_down, node_parent);
	if (x < 2) {
		Swap(node_down.digit[x][y], node_down.digit[x + 1][y]);
		if (is_expandable(node_down)) {
			node_down.index = index;
			node_down.self = node_v.size();
			node_down.depth = node_v[index].depth + 1;
			node_v.push_back(node_down);
			node_s.push(node_down);
			cout << node_down << "   " << ++tag << endl;
			if (is_equal(node_down.digit, dest.digit)) {
				return node_v.size() - 1;
			}
			cout << "down false" << endl;
		}
	}
	//�����ƶ����ӽڵ�
	Node node_left;
	Assign(node_left, node_parent);
	if (y > 0) {
		Swap(node_left.digit[x][y], node_left.digit[x][y - 1]);
		if (is_expandable(node_left)) {
			node_left.index = index;
			node_left.self = node_v.size();
			node_left.depth = node_v[index].depth + 1;
			node_v.push_back(node_left);
			node_s.push(node_left);
			cout << node_left << "   " << ++tag << endl;
			if (is_equal(node_left.digit, dest.digit)) {
				return node_v.size() - 1;;
			}
			cout << "left false" << endl;
		}
	}
	//�����ƶ����ӽڵ�
	Node node_right;
	Assign(node_right, node_parent);
	if (y < 2) {
		Swap(node_right.digit[x][y], node_right.digit[x][y + 1]);
		if (is_expandable(node_right)) {
			node_right.index = index;
			node_right.self = node_v.size();
			node_right.depth = node_v[index].depth + 1;
			node_v.push_back(node_right);
			node_s.push(node_right);
			cout << node_right << "   " << ++tag << endl;
			if (is_equal(node_right.digit, dest.digit)) {
				cout << "true" << endl;
				return node_v.size() - 1;
			}
			cout << "right false" << endl;
		}
	}
	cout << "return" << endl;
	return -1;
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
	src.self = 0;
	src.depth = 0;
	
	k = 0;
	cout << "Input destination:" << endl;
	for (int m = 0; m < ROW; m++)
		for (int n = 0; n < COL; n++) {
			cin >> number;
			dest.digit[m][n] = number;
			_dest[k] = number;
			k++;
		}

	node_s.push(src);
	node_v.push_back(src);

	//��ʱ��
	clock_t start = clock();
	if (!is_access(_src, _dest)) {
		cout << "No Solution!" << endl;
		return -1;
	}
	else {
		int i = src.index;
		while (1) {
			int num = ProcessNode(i);
			if (num != -1) {
				cout << "find!" << num << endl;
				vector<Node> rstep_v;
				cout << "Source:" << endl;
				cout << src << endl;
				int count = PrintSteps(num, rstep_v);
				cout << "Successful!" << endl;
				cout << "Using " << (clock() - start) / CLOCKS_PER_SEC
					<< " seconds and " << count << "steps." << endl;
				break;
			}
			else {
				if (node_s.top().depth < 8 && node_s.top().visit == false) {
					i = node_s.top().self;
				}
				else {
					cout << "poping..." << node_s.top().self << endl;
					node_s.pop();
					i = node_s.top().self;
					node_s.top().visit = true;
				}

			}
		}
	}	
	return 0;
}