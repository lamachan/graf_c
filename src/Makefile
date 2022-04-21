objects = main.o graph.o bfs.o dijkstry.o arguments.o

default: $(objects)
	cc $(objects)
debug: $(objects)
	cc $(objects) -DDEBUG
debug_graph: $(objects)
	cc $(objects) -DDEBUG_GRAPH
main.o: main.c graph.h bfs.h dijkstry.h
	cc -c main.c
graph.o: graph.c graph.h
	cc -c graph.c
bfs.o: bfs.c bfs.h graph.h
	cc -c bfs.c
dijkstry.o: dijkstry.c dijkstry.h graph.h
	cc -c dijkstry.c
arguments.o: arguments.c arguments.h
	cc -c arguments.c

.PHONY: clean

clean:
	rm $(objects) a.out
