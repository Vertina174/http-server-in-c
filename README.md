# Simple HTTP Web Server in C (Winsock)

A basic HTTP web server written in C using the Windows Winsock API. The server listens on port **8080**, accepts incoming TCP connections, receives HTTP requests, and serves an HTML file (`index.html`) to the client.

## Features

* Uses Winsock2 for networking
* Creates a TCP socket
* Binds to port 8080
* Listens for incoming client connections
* Accepts HTTP requests from browsers
* Sends HTTP response headers
* Serves an HTML file
* Proper socket cleanup and error handling

---

## How It Works

1. Initialize Winsock using `WSAStartup()`
2. Create a TCP socket using `socket()`
3. Bind the socket to port **8080**
4. Start listening for incoming connections
5. Accept a client connection
6. Receive the HTTP request
7. Send HTTP response headers
8. Read `index.html`
9. Send the file contents to the client
10. Close sockets and clean up Winsock resources

---

## Project Structure

```
.
├── server.c
├── hi1.html
└── README.md
```

---

## Requirements

* Windows Operating System
* GCC (MinGW/MSYS2) or Visual Studio
* Winsock2 Library

---

## Compilation

### GCC (MinGW/MSYS2)

```bash
gcc server.c -o server -lws2_32
```

---

## Running

Start the server:

```bash
server.exe
```

Expected output:

```text
WSA Started Successfully
Communication End-Point Established
Successful Binding to Port and IP Address
Successfully Listened to a Client
Waiting For Request:
```

Open your browser and visit:

```text
http://localhost:8080
```

The contents of `index.html` will be displayed.

---

## Example HTTP Response

```http
HTTP/1.1 200 OK
Content-Type: text/html
```

The server then sends the contents of `index.html`.

---

## Limitations

This project is intended for learning purposes and has several limitations:

* Handles only one client connection at a time
* Supports only HTTP
* No HTTPS support
* No multithreading
* Sends files one byte at a time (inefficient)
* No MIME type detection
* No request parsing beyond basic reception
* No support for POST requests

---

## Possible Improvements

* Add multithreading using Windows Threads
* Support multiple simultaneous clients
* Serve different file types
* Implement MIME type detection
* Parse HTTP methods and routes
* Add logging
* Improve file transfer performance using buffers
* Add HTTPS support using OpenSSL

---

## Learning Concepts Demonstrated

* TCP/IP Networking
* Socket Programming
* Winsock API
* HTTP Basics
* Client-Server Architecture
* File Handling in C
* Error Handling and Resource Cleanup

---

## Author

Aaditya Chauhan
