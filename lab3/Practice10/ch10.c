#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#define FILE_SIZE 1000  // 파일 크기

int main() {
    const char* src_filename = "ch10_test.txt";
    const char* dest_filename = "ch10_copy.txt";

    int src_fd = open(src_filename, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    int dest_fd = open(dest_filename, O_CREAT | O_RDWR, S_IRWXU);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        exit(EXIT_FAILURE);
    }

    // 파일 사이즈 설정
    ftruncate(dest_fd, FILE_SIZE);

    // 공유 메모리 설정
    void* src_addr = mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, src_fd, 0);
    void* dest_addr = mmap(NULL, FILE_SIZE, PROT_WRITE, MAP_SHARED, dest_fd, 0);

    // 세마포어 생성 및 초기화
    sem_t* semaphore = sem_open("file_semaphore", O_CREAT, 0644, 1);
    if (semaphore == SEM_FAILED) {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 자식 프로세스 (쓰기)
        sem_wait(semaphore);  // 세마포어 획득

        // 파일 복사
        for (int i = 0; i < FILE_SIZE; ++i) {
            *((char*)dest_addr + i) = *((char*)src_addr + i);
        }

        sem_post(semaphore);  // 세마포어 해제
    } else {
        // 부모 프로세스 (읽기)
        sem_wait(semaphore);  // 세마포어 획득

        // 자식 프로세스가 파일 복사를 마칠 때까지 기다림
        wait(1);

        // 작업 완료 후 공유 메모리 및 세마포어 정리
        munmap(src_addr, FILE_SIZE);
        munmap(dest_addr, FILE_SIZE);
        sem_close(semaphore);
        sem_unlink("file_semaphore");

    }

    close(src_fd);
    close(dest_fd);

    return 0;
}

