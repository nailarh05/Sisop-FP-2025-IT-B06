# Final Project Sistem Operasi IT

## Peraturan

- Waktu pengerjaan dimulai hari **Kamis (19 Juni 2025)** setelah soal dibagikan hingga hari **Rabu (25 Juni 2025)** pukul **23.59 WIB**.
- Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk **README (GitHub)**.
- Format nama repository GitHub: `Sisop-FP-2025-IT-[Kelas][Kelompok]`  
  _(Contoh: `Sisop-FP-2025-IT-A01`)_
- Setelah pengerjaan selesai, seluruh **source code dan semua script bash, awk, dan file cron job** wajib ditaruh di GitHub masing-masing kelompok, dan **link GitHub dikumpulkan pada form yang disediakan**.  
  Pastikan GitHub di-set ke **publik**.
- **Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir.**  
  Jika melewati, maka akan dinilai berdasarkan commit terakhir yang masuk.
- Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.
- Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada **README** beserta **permasalahan yang ditemukan**.
- Praktikan **tidak diperbolehkan menanyakan jawaban** dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lain.
- Jika ditemukan **indikasi kecurangan dalam bentuk apapun**, maka nilai dianggap **0**.
- Pengerjaan soal **sesuai dengan modul** yang telah diajarkan.

---

## Kelompok 06

| Nama                         | NRP         |
|------------------------------|-------------|
| Zaenal Mustofa               | 5027241018  |
| Muhammad Afrizan Rasya       | 5027241048  |
| Naila Raniyah Hanan          | 5027241078  |
|Raynard Carlent               | 5027241109  |

---

## Deskripsi Soal

**Memahami komunikasi client-server melalui socket TCP. Client mengirimkan nama hewan ke server.**  
Server merespons sesuai input:
- `dragon` → `rawr`
- `wolf` → `awoo`
- `dog` → `woof`
- lainnya → `unknown :(`

Client mencetak respons yang diterima dari server.

---

## Catatan

- Project ini dikerjakan dengan pembagian tugas yang merata antar anggota kelompok.
- Pengetesan dilakukan di sistem Linux (Ubuntu 22.04 / WSL).
- Setiap fitur telah diuji menggunakan skenario normal dan edge-case.

---

## Struktur Repository

Sisop-FP-2025-IT-B06/ 

├── server.c       
├── client.c       
└── README.md      

## Pengerjaan

### Soal 1: Animal Sound RPC via TCP Socket

#### Teori
Communication between processes running on different servers can be done using sockets and TCP/IP protocols. In the operating system context, this mechanism is known as Inter-Process Communication (IPC) through a network.

According to Silberschatz et al. (2020):
`A socket is defined as an endpoint for communication. A pair of processes communicating over a network employs a pair of sockets — one for each process.` 

TCP sockets are **conection-oriented**, meaning they guarantee that data is delivered in full and in order.

In the client-server model, the server must perform the following steps:
- Create a socket (`socket())
- Bind the socket to an address (bind())
- Listen for incoming connections (listen())
- Accept a connection (accept())
- Communicate using `read() ` and `send()`

The client, on other hand, only needs to:
- Create a socket
- Conntect to the server (`connect()`)
- Communicate using `send() ` and `recv()`

According to Kerrisk (2010):
`The combination of socket(), bind(), listen(), and accept() forms the basis of any TCP server, while the client uses socket() and connect().`— (The Linux Programming Interface, Chapter 56: Sockets: Concepts and Unix Domain Sockets)

#### Solusi
Server.c and client.c are the two primary files that make up this program. They work together to create a basic TCP socket communication system in which the server responds with an animal sound when the client sends a string that represents the name of an animal.

**server.c**— TCP Server that Responds with Animal Sounds
1. Socket Setup and Binding:
```c
server_fd = socket(AF_INET, SOCK_STREAM, 0);
bind(server_fd, (struct sockaddr *)&address, sizeof(address));
listen(server_fd, 3);
```
These steps create a TCP socket, bind it to port 8080 (AF_INET, SOCK_STREAM), and make it listen for up to 3 client connections.

2. Accepting Connection:
```c
new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
```
This accepts a connection from a client. Once connected, communication can begin.

3. Message Handling Loop:
```c
while (1) {
    read(new_socket, buffer, BUFFER_SIZE);
    ...
    send(new_socket, response, strlen(response), 0);
}
```
The server continuously reads messages from the client and sends appropriate responses.

4. Message Matching:
```c
if (strcmp(buffer, "dragon") == 0) response = "rawr";
else if (strcmp(buffer, "wolf") == 0) response = "awoo";
else if (strcmp(buffer, "dog") == 0) response = "woof";
else response = "unknown :(";
```
A simple string comparison determines the response based on the input. This simulates a manual remote procedure call based on keywords.

5. Reset Buffer:
```c
memset(buffer, 0, BUFFER_SIZE);
```
Clears the buffer to avoid leftover data mixing with the next message

**client.c** — TCP Client that Sends Animal Names
1. Creating and Connecting Socket:
```c
sock = socket(AF_INET, SOCK_STREAM, 0);
connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
```
The client creates a TCP socket and connects to the server on 127.0.0.1:8080.

2. Message Input and Sending:
```c
fgets(message, BUFFER_SIZE, stdin);
send(sock, message, strlen(message), 0);
```
The client asks for user input (an animal name), then sends it to the server. fgets() is used to safely read a full line of input.

3. Receiving and Displaying Response:
```c
read(sock, buffer, BUFFER_SIZE);
printf("Respons dari server: %s\n\n", buffer);
```
The client receives the server's reply and prints it to the screen.

4. Looping Communication:
```c
while(1) {
    printf("Masukkan pesan untuk server: ");
    fgets(message, BUFFER_SIZE, stdin);

    message[strcspn(message, "\n")] = 0;  // Remove newline character

    send(sock, message, strlen(message), 0);

    int valread = read(sock, buffer, BUFFER_SIZE);
    printf("Respons dari server: %s\n\n", buffer);

    memset(buffer, 0, BUFFER_SIZE);
}
```
This process allows repeated input/output until the client or server is terminated manually.

## Video Menjalankan Program



---

## Daftar Pustaka
1. Silberschatz, A., Galvin, P. B., & Gagne, G. (2020). Operating System Concepts.
2. Kerrisk, Michael. (2010). The Linux Programming Interface
3. Beej's Guide to Network Programming. - https://beej.us/guide/bgnet/html/ : A lightweight and popular guide for socket programming in C.
4. Linux man pages: `man socket`, `man bind`, `man connect`, `man send`, `man recv` : Official documentation for Linux system calls related to networking.

---



