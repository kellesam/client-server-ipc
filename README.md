# client-server-ipc

**Instructions:**  
1. run `make` in the project directory
2. run `./server &` to start the server daemon
3. run `./client`
4. enter text and press enter to submit
5. formatted results will be printed to stdout
6. kill the background server
7. run `make clean` to remove the executables

To run the test script replace step #3 above with the command `./testscript`

**Which IPC mechanism did you choose and why?**  
I chose to use network sockets for my IPC. I'm familiar with how they work and
how to set them up, they can be quickly re-written to operate over a network
if needed (currently using "localhost" as hostname), and they can send data in
either direction.

**What are the strengths and weaknesses of your chosen IPC mechanism?**  
Strengths: bi-directional data flow, can be re-purposed for same machine or
network communication, can be used for TCP or UDP.  
Weaknesses: higher overhead compared to other solutions like pipes, relies on
C libraries and C-style strings, not supported by all OS.

**Could your system scale up to handle thousands of requests per second?**  
No, it is written as a single thread application and blocks until data is
sent or read. This could be re-written to implement other methods such as
creating child processes to handle requests or maintaining multiple file
descriptors to use with select statements.