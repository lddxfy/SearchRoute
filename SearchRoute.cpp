#include<vector>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;
const int YES = 5;
const int NO = 6;
class chessboard {
public:
	chessboard(int x, int y) :_x(x), _y(y) {
		board = new Node * [_x];
		for (int i = 0; i < _x; i++) {
			board[i] = new Node[_y];
		}
		vec.resize(_x * _y);

	};
	void initNode(int x, int y, int value) {
		board[x][y].n_x = x;
		board[x][y].n_y = y;
		board[x][y].val = value;
		for (int i = 0; i < 4; i++) {
			board[x][y].state[i] = NO;
		}
	}

	void initNodestate() {
		for (int i = 0; i < _x; i++) {
			for (int j = 0; j < _y; j++) {
				if (board[i][j].val == 1) {
					continue;
				}
				//右方向
				if (j < _y - 1 && board[i][j + 1].val == 0) {
					board[i][j].state[RIGHT] = YES;
				}
				//下
				if (i < _x - 1 && board[i + 1][j].val == 0) {
					board[i][j].state[DOWN] = YES;
				}
				//左
				if (j > 0 && board[i][j - 1].val == 0) {
					board[i][j].state[LEFT] = YES;
				}
				//上
				if (i > 0 && board[i - 1][j].val == 0) {
					board[i][j].state[UP] = YES;
				}
			}
		}
	}

	void search() {
		if (board[0][0].val == 1) {
			return;
		}
		else {
			board[0][0].val = 9;
		}
		que.push(board[0][0]);
		while (!que.empty())
		{
			Node curnode = que.front();
			int x = curnode.n_x;
			int y = curnode.n_y;
			if (board[x][y].state[RIGHT] == YES) {
				board[x][y].state[RIGHT] = NO;
				board[x][y + 1].state[LEFT] = NO;
				vec[x * _x + y + 1] = board[x][y];
				que.push(board[x][y + 1]);
				if (check(board[x][y + 1])) {
					return;
				}
			}
			if (board[x][y].state[DOWN] == YES) {
				board[x][y].state[DOWN] = NO;
				board[x + 1][y].state[UP] = NO;
				vec[(x + 1) * _x + y] = board[x][y];
				que.push(board[x + 1][y]);
				if (check(board[x + 1][y])) {
					return;
				}
			}
			if (board[x][y].state[LEFT] == YES) {
				board[x][y].state[LEFT] = NO;
				board[x][y - 1].state[RIGHT] = NO;
				vec[x * _x + (y - 1)] = board[x][y];
				que.push(board[x][y - 1]);
				if (check(board[x][y - 1])) {
					return;
				}
			}
			if (board[x][y].state[UP] == YES) {
				board[x][y].state[UP] = NO;
				board[x - 1][y].state[DOWN] = NO;
				vec[(x - 1) * _x + y] = board[x][y];
				que.push(board[x - 1][y]);
				if (check(board[x - 1][y])) {
					return;
				}
			}
			que.pop();
		}
	}

	void printres() {
		if (que.empty()) {
			cout << "没有路径可到达终点" << endl;
			return;
		}
		else {
			int x = _x - 1;
			int y = _y - 1;
			for (;;) {
				board[x][y].val = 9;
				Node n = vec[x * _x + y];
				x = n.n_x;
				y = n.n_y;
				if (x == 0 && y == 0)    break;
			}
		}
		for (int i = 0; i < _x; i++) {
			for (int j = 0; j < _y; j++) {
				if (board[i][j].val == 9) {
					cout << "* ";
				}
				else {
					cout << board[i][j].val << " ";
				}
			}
			cout << endl;
		}
	}

private:
	struct Node {
		int val;
		int n_x;
		int n_y;
		int state[4];
	};
	bool check(Node& n) {
		return n.n_x == _x - 1 && n.n_y == _y - 1;
	}
	int _x;
	int _y;
	Node** board;
	queue<Node> que;
	vector<Node> vec;

};

int main()
{
	int row, col, val;
	cout << "请输入迷宫的行列数：" << endl;
	cin >> row >> col;
	chessboard c(row, col);
	cout << "请输入迷宫的样式：" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> val;
			c.initNode(i, j, val);
		}
	}
	cout << endl;
	c.initNodestate();
	c.search();
	cout << "搜索到的最短迷宫路径为：" << endl;
	c.printres();
	return 0;
}




