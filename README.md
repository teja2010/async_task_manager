# async_task_manager (WIP)

Build a system which brings a few functional programming concepts to C. The program is made of functions and their connections.
Submit all functions and a description of connection to build the program.

1. Simple task manager which manages N user threads over M kernel threads (M:N model)

2. Tasks submitted to the manager are run using lightweight fibers.

3. IO using async IO (epoll, liuring?).

4. Simple Go-like channel for communication between fibers. fibers can be
   - within the process
   - between processes within a machine
   - between processes across machines

5. Build a program as a graph, where nodes are functions and edges are channels.


6. Complete control over scheduling & CPU allocation.

7. Add new channels and functions without restarting the process.

### Resources:
- https://www.gnu.org/software/pth/pth-manual.html
- https://www.evanjones.ca/software/threading.html
- https://web.archive.org/web/20180626195333/http://www.linux-mag.com/id/792/
- https://kernel.dk/io_uring.pdf
