all:
	gcc compare.c -lpthread -o compare

test:
	$(info "comparing swapcontext with direct procedure call and pthreads")
	./compare

clean:
	rm compare
