FILENAME = test.cpp _funNode.cpp _funNode_iterator.cpp _funXML.cpp _Cfile.cpp
O = g++ -g -o

all:$(FILENAME)
	$(O) test $(FILENAME)

clean:
	rm -f test
