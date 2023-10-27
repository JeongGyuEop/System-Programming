use std::io;

fn main() {
    // 행과 열의 크기를 입력받습니다.
    let mut input = String::new();
    println!("행렬의 행 수를 입력하세요: ");
    io::stdin().read_line(&mut input).expect("입력 오류");
    let rows: usize = input.trim().parse().expect("올바른 숫자를 입력하세요");
    input.clear();

    println!("행렬의 열 수를 입력하세요: ");
    io::stdin().read_line(&mut input).expect("입력 오류");
    let cols: usize = input.trim().parse().expect("올바른 숫자를 입력하세요");

    // 두 행렬을 입력받아 Vec<Vec<T>>으로 저장
    let mut matrix_a = vec![vec![0; cols]; rows];
    let mut matrix_b = vec![vec![0; cols]; rows];

    println!("첫 번째 행렬 A의 요소를 입력하세요:");
    for i in 0..rows {
        for j in 0..cols {
            input.clear();
            io::stdin().read_line(&mut input).expect("입력 오류");
            matrix_a[i][j] = input.trim().parse().expect("올바른 숫자를 입력하세요");
        }
    }

    println!("두 번째 행렬 B의 요소를 입력하세요:");
    for i in 0..rows {
        for j in 0..cols {
            input.clear();
            io::stdin().read_line(&mut input).expect("입력 오류");
            matrix_b[i][j] = input.trim().parse().expect("올바른 숫자를 입력하세요");
        }
    }

    // 결과 행렬을 초기화
    let mut result = vec![vec![0; cols]; rows];

    // 행렬 덧셈 수행
    for i in 0..rows {
        for j in 0..cols {
            result[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }

    // 결과 행렬 출력
    println!("두 행렬의 합:");
    for row in &result {
        for val in row {
            print!("{} ", val);
        }
        println!();
    }
}

