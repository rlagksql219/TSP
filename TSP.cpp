#include<iostream>
#include<cstdio>
using namespace std;

int adjacent_matrix[10][10]; // 초기 그래프에 대한 인접행렬
int visited[10]; // 방문한 vertex
int vertex_num; // vertex의 개수
int minimum_cost = 987654321; // tour의 최소 비용


// Traveling Salesperson Problem을 풀기위한 데이터를 입력하는 함수
void input() {

	printf("방문할 vertex의 개수: ");
	scanf_s("%d", &vertex_num); // 방문할 vertex의 개수 입력

	printf("\n인접행렬(adjacent matrix) 입력");
	for (int i = 0; i < vertex_num; i++) {
		for (int j = 0; j < vertex_num; j++) {
			scanf_s("%d", &adjacent_matrix[i][j]);
			// 2차원 배열을 이용하여 초기 그래프에 대한 인접행렬 입력
		}
	}
}


// 깊이 우선 탐색(재귀적 방식)을 이용하여 가능한 모든 경우 탐색
void depth_first_search(int start, int i, int sum, int count) {

	// 모든 vertex를 다 탐색하고 vertex가 다시 start로 온 경우
	if (count == vertex_num && start == i) {
		if (minimum_cost > sum) // minimum_cost보다 계산한 sum의 cost가 더 작은 경우
			minimum_cost = sum; // sum을 minimum_cost로
		return;
	}

	for (int j = 0; j < vertex_num; j++) {
		if (adjacent_matrix[i][j] == 0)
			// 인접행렬이 0인 경우
			// 1. 그래프가 연결되어있지 않음
			// 2. 시작점과 끝점이 같음
			continue; // 반복문을 빠져나감

		// 기존에 방문하지 않았고, 인접행렬의 weight가 있는 경우
		if (!visited[i] && adjacent_matrix[i][j] > 0) {
			visited[i] = true; // 방문 표시
			sum = sum + adjacent_matrix[i][j]; // 인접행렬의 값을 weight에 더함

			if (sum <= minimum_cost) { // sum이 최소비용보다 작을 경우에 탐색
				depth_first_search(start, j, sum, count + 1); // 재귀함수를 통해 깊이 우선 탐색
			}

			// 재귀호출을 위해 초기값으로 세팅
			visited[i] = false; // 방문 표시를 지움
			sum = sum - adjacent_matrix[i][j]; // sum 초기화
		}
	}
}


// depth_first_search 함수를 여러번 호출하여 minimum_cost를 구하는 함수
void travel() {
	for (int i = 0; i < vertex_num; i++) { // 각각의 vertex에서 시작하는 경우
		depth_first_search(i, i, 0, 0);
	}
}


// 순회하며 minimum cost일 때의 vertex를 기록하는 함수
int travel_vertex(int c) {
	int count, minimum_vertex = 999;
	int minimum = 999, temp;

	for (count = 0; count < vertex_num; count++) { // 각각의 vertex에서 시작하는 경우
		if ((adjacent_matrix[c][count] != 0) && (visited[count] == 0)) { // weight가 있고, 방문하지 않은 경우

			if (adjacent_matrix[c][count] < minimum) { // 인접행렬의 weight가 munimum보다 작은 경우
				minimum = adjacent_matrix[count][0] + adjacent_matrix[c][count]; // minimum 재설정
			}

			temp = adjacent_matrix[c][count];
			minimum_vertex = count;
		}
	}

	if (minimum != 999) { // tour를 하며 minimum값을 재설정한 경우
		minimum_cost = minimum_cost + temp; // minimum_cost 업데이터
	}

	return minimum_vertex; // 최소비용일 떄의 vertex 리턴
}


// 경로 출력하는 함수
void Path(int vertex) {
	int minimum_vertex; // 최소 비용일 떄의 vertex
	visited[vertex] = 1; // 방문 표시

	printf(" %d ->", vertex + 1);

	minimum_vertex = travel_vertex(vertex); // 순회하며 return 한 vertex를 minimum vertex로 설정

	if (minimum_vertex == 999) {
		// tour를 하지 못한 경우
		// 시작점으로 돌아온 경우

		minimum_vertex = 0;
		printf(" %d", minimum_vertex + 1);
		minimum_cost = minimum_cost + adjacent_matrix[vertex][minimum_vertex];
		return;
	}

	Path(minimum_vertex); // 재귀적으로 호출하며 경로 출력
}


// Traveling Salesperson Problem의 결과값을 출력하는 함수
void output() {
	printf("\n최소비용(minimum cost): %d\n", minimum_cost); // minimum cost 출력

	// tour가 minimum cost일 때의 경로 출력
	printf("\nOptimal tour의 Path:");
	Path(0);
	printf("\n");
}


int main(void) {
	input(); // 초기값 입력
	travel(); // 최소비용 계산
	output(); // 결과값 출력
	return 0;
}