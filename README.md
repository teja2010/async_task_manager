# async_task_manager (WIP)

1. Simple task manager which starts N_CPU kernel threads.
2. Tasks submitted to the manager are run using lightweigth fibers. IO using async IO (liburing).
3. Simple Go-like channel for communication between fibers.

### Resources:
- https://www.gnu.org/software/pth/pth-manual.html
- https://www.evanjones.ca/software/threading.html
- https://web.archive.org/web/20180626195333/http://www.linux-mag.com/id/792/
- https://kernel.dk/io_uring.pdf
