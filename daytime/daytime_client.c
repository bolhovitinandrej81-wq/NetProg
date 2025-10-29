#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DAYTIME_PORT 13
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t n;
    
    // Проверяем аргументы командной строки
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <IP-адрес сервера>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // Создаем UDP сокет
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }
    
    // Заполняем структуру адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DAYTIME_PORT);
    
    // Преобразуем IP-адрес
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("Ошибка преобразования IP-адреса");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    printf("Подключаемся к daytime серверу %s:%d\n", argv[1], DAYTIME_PORT);
    
    // Отправляем пустой датаграмму для получения времени
    if (sendto(sockfd, "", 0, 0, 
               (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка отправки данных");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    // Получаем ответ от сервера
    socklen_t addr_len = sizeof(server_addr);
    n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                 (struct sockaddr *)&server_addr, &addr_len);
    
    if (n < 0) {
        perror("Ошибка получения данных");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    buffer[n] = '\0';
    printf("Текущее время: %s", buffer);
    
    close(sockfd);
    return 0;
}
