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

**Understanding client-server communication via TCP socket. The client sends the name of the animal to the server.**  
There are two programs: a Server and a Client. The Client sends a message to the Server, and the Server checks the message and responds based on the following rules:

If the message is "dragon", the Server replies with "rawr".

If the message is "wolf", the Server replies with "awoo".

If the message is "dog", the Server replies with "woof".

For any other message, the Server responds with "unknown :(".

This way, the Server only gives specific responses for "dragon", "wolf", or "dog", while any other message will be considered unrecognized.

---

## Catatan

- Project ini dikerjakan dengan pembagian tugas yang merata antar anggota kelompok.
- Pengetesan dilakukan di sistem Linux (Ubuntu 22.04 / WSL / VMware).
- Setiap fitur telah diuji dan dapat dipastikan semuanya berjalan dengan baik.

---

## Struktur Repository

Sisop-FP-2025-IT-B06/ 

├── server.c       
├── client.c       
└── README.md      

## Pengerjaan

#### Teori

1.With multi-tier programming languages, programmers can specify the locations of code to run in order to reduce development efforts for the web-based client-server model where programmers write client and server programs separately and test the multiple programs together. The RPC calculus, one of the foundations of those languages by Cooper and Wadler, has the feature of symmetric communication in programmer's writing arbitrarily deep nested client-server interactions. However, the existing research only considers dynamically typed locations. We propose a typed RPC calculus where locations are tracked in type-level. A new located type system paves the way for a theory of RPC calculi for the client-server model.
(In the following papers published in SCP2020 and PPDP2021, the typed RPC calculus will be enhanced with polymorphic locations and a type-based slicing compilation.)

2.Communication between processes running on different servers can be done using sockets and TCP/IP protocols. In the operating system context, this mechanism is known as Inter-Process Communication (IPC) through a network.

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

### SERVER SIDE

#### Teori
"A file descriptor is a small integer that the kernel uses to identify the open files being accessed by a process. Whenever a process opens an existing file or creates a new file, the kernel returns a file descriptor that is used to read or write the file."(Stevens et al., 1998, Ch. 3)

### Solusi
```c
int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
```

### Teori
"The protocol argument to the socket function is typically set to 0 for most applications, which selects the default protocol for the given domain and socket type."(Stevens et al., 1998, Ch. 4).

### Solusi
```c
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
```

### Teori
Most implementations and APIs provide a way to bypass this restriction. With
the Berkeley sockets API, the SO_REUSEADDR socket option enables the bypass
operation. It lets the caller assign itself a local port number even if that port number is part of some connection in the 2MSL wait state. We will see, however, that
even with this bypass mechanism for one socket (address, port number pair), the
rules of TCP still (should) prevent this port number from being reused by another
instantiation of the same connection that is in the 2MSL wait state.(Stevens, 1998, pp. 620)

### Solusi 
```c
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
```

### Teori
In IPv4, the sin_addr.s_addr field of the struct sockaddr_in structure is set to INADDR_ANY. In
IPv6, the sin6_addr field of the struct sockaddr_in6 structure is assigned into from the global
variable in6addr_any. Or, if you’re declaring a new struct in6_addr, you can initialize it to
IN6ADDR_ANY_INIT. (Beej's Guide, Ch. 5)

### Solusi
```c
address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
```

### Teori
"The bind function assigns a local protocol address to a socket. For TCP, calling bind lets us specify a local IP address and port number for the socket. A server binds a well-known port to its socket, so clients can connect to it." (Stevens et al., 1998, Ch. 4).

### Solusi
```c
if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
```

### Teori
"The listen function converts an unconnected socket into a passive socket, indicating that the kernel should accept incoming connection requests directed to this socket. The second argument, backlog, specifies the maximum number of connections the kernel should queue for this socket."(Stevens et al., 1998, Ch. 4)

### Solusi
```c
if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Server menunggu koneksi di port %d...\n", PORT);
```

### Teori
"The accept function extracts the first completed connection from the queue of pending connections for the listening socket (server_fd). It creates a new connected socket and returns a new file descriptor referring to this socket. The original listening socket remains open to accept further connections."(Stevens et al., 1998, Ch. 4)

### Solusi
```c
if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
    perror("accept error");
    exit(EXIT_FAILURE);
} else {
    printf("ACC bosku! Koneksi aman nih ye... (Socket fd: %d)\n", new_socket);   
}
```

### Teori
"A typical server uses an infinite loop to handle client connections persistently until explicitly terminated."(Beej's Guide, Ch. 7)

### Solusi
```c
while(1) {
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread <= 0) break;
        
        printf("Pesan diterima dari client: %s\n", buffer);
        
        char *response;
        
        if (strcmp(buffer, "dragon") == 0) {
            response = "rawr";
        } else if (strcmp(buffer, "wolf") == 0) {
            response = "awoo";
        } else if (strcmp(buffer, "dog") == 0) {
            response = "woof";
        } else {
            response = "unknown :(";
        }
        
        send(new_socket, response, strlen(response), 0);
        printf("Mengirim respons: %s\n", response);
        
        memset(buffer, 0, BUFFER_SIZE);
    }
```

```c
close(new_socket);
    close(server_fd);
    
    return 0;
}
```

## Video Menjalankan Program

https://youtu.be/TfTT56XyYHU

---

## Daftar Pustaka
1. Silberschatz, A., Galvin, P. B., & Gagne, G. (2020). Operating System Concepts.
2. Kerrisk, Michael. (2010). The Linux Programming Interface
3. Beej's Guide to Network Programming. - https://beej.us/guide/bgnet/html/ : A lightweight and popular guide for socket programming in C.
4. Linux man pages: `man socket`, `man bind`, `man connect`, `man send`, `man recv` : Official documentation for Linux system calls related to networking.
5. Stevens, W. R. (1994). TCP/IP Illustrated, Volume 1: The Protocols. Addison-Wesley.

---



