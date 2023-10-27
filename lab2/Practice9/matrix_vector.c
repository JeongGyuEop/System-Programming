#include <iostream>
#include <vector>

using namespace std;

int main() {
    int rows, cols;

    // 행과 열의 크기를 입력 받습니다.
    cout << "행렬의 행 수를 입력하세요: ";
    cin >> rows;
    cout << "행렬의 열 수를 입력하세요: ";
    cin >> cols;

    // 행렬 A를 입력받고 동적으로 할당합니다.
    vector<vector<int>> matrixA(rows, vector<int>(cols));
    cout << "첫 번째 행렬 A의 요소를 입력하세요:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrixA[i][j];
        }
    }

    // 행렬 B를 입력받고 동적으로 할당합니다.
    vector<vector<int>> matrixB(rows, vector<int>(cols));
    cout << "두 번째 행렬 B의 요소를 입력하세요:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrixB[i][j];
        }
    }

    // 두 행렬을 더한 결과를 저장할 행렬을 초기화합니다.
    vector<vector<int>> result(rows, vector<int>(cols));

    // 행렬 덧셈 수행
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    // 결과 행렬 출력
    cout << "두 행렬의 합:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

