#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ECHO_PORT 7
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t n;
    
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <IP-адрес сервера> <сообщение>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // Создаем TCP сокет
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }
    
    // Заполняем структуру адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(ECHO_PORT);
    
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("Ошибка преобразования IP-адреса");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    // Устанавливаем соединение
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка подключения");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    printf("Подключено к echo серверу %s:%d\n", argv[1], ECHO_PORT);
    
    // Отправляем сообщение
    char *message = argv[2];
    size_t message_len = strlen(message);
    ssize_t bytes_sent;
    
    bytes_sent = send(sockfd, message, message_len, 0);
    if (bytes_sent < 0 || (size_t)bytes_sent != message_len) {
        perror("Ошибка отправки данных");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    printf("Отправлено: %s\n", message);
    
    // Получаем ответ
    n = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
    if (n < 0) {
        perror("Ошибка получения данных");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    buffer[n] = '\0';
    printf("Получено: %s\n", buffer);
    
    close(sockfd);
    return 0;
}
