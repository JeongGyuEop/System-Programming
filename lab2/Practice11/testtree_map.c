#include <iostream>
#include <map>
#include <string>

// 학생 정보를 담는 구조체
struct StudentInfo {
    std::string name;
    double midtermScore;
    double finalScore;
};

int main() {
    int numStudents;
    std::cout << "학생 수를 입력하세요: ";
    std::cin >> numStudents;

    // 학생 정보를 저장할 map 컨테이너
    std::map<std::string, StudentInfo> studentMap;

    for (int i = 0; i < numStudents; ++i) {
        StudentInfo student;
        std::cout << "학생 이름: ";
        std::cin >> student.name;
        std::cout << "중간 점수: ";
        std::cin >> student.midtermScore;
        std::cout << "기말 점수: ";
        std::cin >> student.finalScore;

        // 학생 정보를 map에 삽입
        studentMap[student.name] = student;
    }

    // 학생 정보 출력
    for (const auto& entry : studentMap) {
        const std::string& name = entry.first;
        const StudentInfo& student = entry.second;
        std::cout << "이름: " << name << ", 중간 점수: " << student.midtermScore
                  << ", 기말 점수: " << student.finalScore << std::endl;
    }

    return 0;
}

