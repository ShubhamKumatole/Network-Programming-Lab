## Echo Server and Client Communication

This is a TCP/IP based client server communication demo program.

  - In a local environment we can test this out in multiple terminal windows 
  - First of all clone the repository and `cd Network-Programming-Lab/Echo\ Server\ and\ Client/` ,
      then compile and run [echo_server.c](https://github.com/ShubhamKumatole/Network-Programming-Lab/blob/main/Echo%20Server%20and%20Client/echo_server.c)
         <details><summary>Run as</summary>
            `gcc -Wall echo_server.c -o server && ./server`
          </details>
  - Open a new terminal window, compile and run [echo_client.c](https://github.com/ShubhamKumatole/Network-Programming-Lab/blob/main/Echo%20Server%20and%20Client/echo_client.c)
         <details><summary>Run as</summary>
            `gcc -Wall echo_client.c -o client && ./client 127.0.0.1`
          </details>
  - Enter some text to to send to server and server sends the same text back 
  - Open another terminal and navigate to this this folder and run `./client 127.0.0.2`   

  <details><summary>Server</summary> <img src="https://github.com/ShubhamKumatole/Network-Programming-Lab/blob/main/Echo%20Server%20and%20Client/Server.jpg" \/></details>
  <details><summary>Client 1</summary> <img src="https://github.com/ShubhamKumatole/Network-Programming-Lab/blob/main/Echo%20Server%20and%20Client/client1.jpg" \/></details>
  <details><summary>Client 2</summary> <img src="https://github.com/ShubhamKumatole/Network-Programming-Lab/blob/main/Echo%20Server%20and%20Client/client2.jpg" \/></details>


