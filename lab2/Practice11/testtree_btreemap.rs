use std::collections::BTreeMap;
use std::io;

// 학생 정보를 담는 구조체
struct StudentInfo {
    name: String,
    midterm_score: f64,
    final_score: f64,
}

fn main() {
    let mut num_students = String::new();
    println!("학생 수를 입력하세요: ");
    io::stdin().read_line(&mut num_students).expect("입력 읽기 실패");

    let num_students: usize = num_students.trim().parse().expect("올바른 숫자를 입력하세요");

    // 학생 정보를 저장할 BTreeMap
    let mut student_map = BTreeMap::new();

    for _ in 0..num_students {
        let mut student = StudentInfo {
            name: String::new(),
            midterm_score: 0.0,
            final_score: 0.0,
        };

        println!("학생 이름: ");
        io::stdin().read_line(&mut student.name).expect("입력 읽기 실패");
        student.name = student.name.trim().to_string();

        println!("중간 점수: ");
        let mut midterm_score = String::new();
        io::stdin().read_line(&mut midterm_score).expect("입력 읽기 실패");
        student.midterm_score = midterm_score.trim().parse().expect("올바른 숫자를 입력하세요");

        println!("기말 점수: ");
        let mut final_score = String::new();
        io::stdin().read_line(&mut final_score).expect("입력 읽기 실패");
        student.final_score = final_score.trim().parse().expect("올바른 숫자를 입력하세요");

        // 학생 정보를 BTreeMap에 삽입
        student_map.insert(student.name.clone(), student);
    }
    
    // 학생 정보 출력
    for (name, student) in student_map.iter() {
        println!("이름: {}, 중간 점수: {}, 기말 점수: {}", name, student.midterm_score, student.final_score);
    }
}

