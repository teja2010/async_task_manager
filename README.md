# async_task_manager (WIP)

Build a system which brings a few functional programming concepts to C. The program is made of functions and their connections.
Submit all functions and a description of connection to build the the program.

1. Simple task manager which starts N_CPU kernel threads.
2. Tasks submitted to the manager are run using lightweigth fibers. IO using async IO (epoll).
3. Simple Go-like channel for communication between fibers. fibers can be
   - within the process
   - between processes within a machine
   - between processes across machines
   
4. Add new channels and functions without restarting the process. 

### Resources:
- https://www.gnu.org/software/pth/pth-manual.html
- https://www.evanjones.ca/software/threading.html
- https://web.archive.org/web/20180626195333/http://www.linux-mag.com/id/792/
- https://kernel.dk/io_uring.pdf
