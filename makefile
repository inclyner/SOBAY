all: frontend.o backend.o

frontend.o: frontend.c
	gcc frontend.c -o frontend
	@echo "frontend compiled"

backend.o: backend.c
	gcc backend.c users_lib.o -o backend
	@echo "backend compiled"

clean:
	rm frontend backend