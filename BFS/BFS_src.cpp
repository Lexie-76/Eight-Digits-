#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

const int ROW = 3;
const int COL = 3;

int tag = 0;
typedef struct _Node {
	int digit[ROW][COL];
	int index; // ���ڵ���
} Node;
Node src, dest;

vector<Node> node_v;   // �洢�ڵ�

//�Ƿ��н�
bool is_access(int cur[], int aim[]) {
	int inver_count1 = 0;
	for (int i = 0; i < 8; i++) {
		//����0
		if (cur[i] == 0) {
			continue;
		}
		int temp = cur[i];
		for (int j = i + 1; j < 9; j++) {
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
	for (int i = 0; i < 8; i++) {
		if (aim[i] == 0) {
			continue;
		}
		int temp = aim[i];
		for (int j = i + 1; j < 9; j++) {
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
void Assign(Node& node, int index) {
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			node.digit[i][j] = node_v[index].digit[i][j];
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
	int x, y;
	bool flag;
	//���ҿ�λ
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
	//�����ƶ����ӽڵ�
	Node node_up;
	Assign(node_up, index);
	if (x > 0) {
		Swap(node_up.digit[x][y], node_up.digit[x - 1][y]);
		if (is_expandable(node_up)) {
			node_up.index = index;
			cout << node_up << "   "<<++tag<<endl;
			if (is_equal(node_up.digit, dest.digit)) {
				node_v.push_back(node_up);
				return node_v.size()-1;
			}
			else {
				node_v.push_back(node_up);
			}			
		}
	}
	//�����ƶ����ӽڵ�
	Node node_down;
	Assign(node_down, index);
	if (x < 2) {
		Swap(node_down.digit[x][y], node_down.digit[x + 1][y]);
		if (is_expandable(node_down)) {
			node_down.index = index;
			cout << node_down << "   " << ++tag << endl;
			if (is_equal(node_down.digit, dest.digit)) {
				node_v.push_back(node_down);
				return node_v.size()-1;
			}
			else {
				node_v.push_back(node_down);
			}
			
		}
	}
	//�����ƶ����ӽڵ�
	Node node_left;
	Assign(node_left, index);
	if (y > 0) {
		Swap(node_left.digit[x][y], node_left.digit[x][y - 1]);
		if (is_expandable(node_left)) {
			node_left.index = index;
			cout << node_left << "   " << ++tag << endl;
			if (is_equal(node_left.digit, dest.digit)) {
				node_v.push_back(node_left);
				return node_v.size()-1;
			}
			else {
				node_v.push_back(node_left);
			}
		}
	}
	//�����ƶ����ӽڵ�
	Node node_right;
	Assign(node_right, index);
	if (y < 2) {
		Swap(node_right.digit[x][y], node_right.digit[x][y + 1]);
		if (is_expandable(node_right)) {
			node_right.index = index;
			cout << node_right << "   " << ++tag << endl;
			if (is_equal(node_right.digit, dest.digit)) {
				node_v.push_back(node_right);
				return node_v.size()-1;
			}
			else {
				node_v.push_back(node_right);
			}
		}
	}
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

	//��ʱ��
	clock_t start = clock();
	if (!is_access(_src, _dest)) {
		cout << "No Solution!" << endl;
		return -1;
	}
	else {
		int i = src.index;
		while (1) {
			int index = ProcessNode(i);
			if (index != -1) {
				vector<Node> rstep_v;
				cout << "Source:" << endl;
				cout << src << endl;
				int count = PrintSteps(index, rstep_v);
				cout << "Successful!" << endl;
				cout << "Using " << (clock() - start) / CLOCKS_PER_SEC
					<< " seconds and " << count << "steps." << endl;
				break;
			}
			else {
				i++;
			}
		}
	}	
	return 0;
}