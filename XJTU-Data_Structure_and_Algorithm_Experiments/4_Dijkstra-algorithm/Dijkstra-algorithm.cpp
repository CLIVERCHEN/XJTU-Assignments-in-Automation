#include "Dijkstra-algorithm.h"

void D_algorithm::complete_distance()  // 补全邻接矩阵，由于图为无向图，则生成的是对称矩阵
{
	for (int i = 0; i < NUMBER_OF_LOCATION; i++)
	{
		for (int j = i; j < NUMBER_OF_LOCATION; j++) _distance[j][i] = _distance[i][j];
	}
}

int D_algorithm::input2num(char* input)  // 将输入的位置转换为编码
{
	for (int i = 0; i < NUMBER_OF_LOCATION; i++)
	{
		if (strcmp(input, loc2num[i]) == 0) return i;
	}
}

int D_algorithm::Dijkstra(int p1, int p2)  // Dijkstra算法
{
	int start, end;
	start = p1;
	end = p2;
	if (start > end)  // 若编码后，起点对应的编码小于终点对应的编码，则交换二者位置，因为二者顺序对最短路径没有影响
	{
		int tmp = start;
		start = end;
		end = tmp;
	}

	if (start == NUMBER_OF_LOCATION || end == NUMBER_OF_LOCATION)
	{
		cout << "ERROR_02";
		exit(0);
	}

	int path_count = 0;
	int ans[NUMBER_OF_LOCATION];
	int if_min[NUMBER_OF_LOCATION] = { 0 };  // 用于选择一行数据的最小值
	memcpy(&ans, &_distance[start], NUMBER_OF_LOCATION * sizeof(int));  // 起点对应的矩阵的一行数据

	for (int i = 0; i < NUMBER_OF_LOCATION - 1; i++)  // 遍历矩阵的每一行
	{
		int min = INT_MAX;  // 初始化min为无限大
		int min_loc = -1;

		for (int j = 0; j < NUMBER_OF_LOCATION; j++)  // 选中ans中的最小值
		{
			if (ans[j] < min && ans[j] != -1 && if_min[j] == 0 && j != start)
			{
				min = ans[j];
				min_loc = j;
			}
		}
		if_min[min_loc] = 1;  // 每个位置只能被选为一次最小值

		for (int k = 0; k < NUMBER_OF_LOCATION; k++)  // 更新ans
		{
			if ((ans[k] == -1 || (_distance[min_loc][k] + min < ans[k])) && _distance[min_loc][k] != -1)
			{
				ans[k] = _distance[min_loc][k] + min;
				path[k][path_count] = min_loc;
				path_count++;
			}
		}
	}
	return ans[end];
}

void D_algorithm::output_path(int start, int end)  // 输出起点到终点的最短路径
{
	if (start < end)
	{
		int tmp_max = -1;
		int i;
		for (i = 12; i >= 0; i--)
		{
			if (path[end][i] > tmp_max) tmp_max = path[end][i];
		}
		output_path(start, tmp_max);
		cout << " " << "->" << " " << loc2num[end];
	}

	else if (start == end) cout << loc2num[end];

	else  // 当起点编码小于终点编码时，则互换二者，调整递归中输出语句的位置，以实现逆向输出路径
	{
		int tmp_max = -1;
		int i;
		for (i = 12; i >= 0; i--)
		{
			if (path[start][i] > tmp_max) tmp_max = path[start][i];
		}
		cout << loc2num[start] << " " << "->" << " ";
		output_path(tmp_max, end);
	}
}