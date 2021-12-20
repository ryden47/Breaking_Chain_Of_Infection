# All Targets
all: bin/cTrace

bin/cTrace: bin/main.o bin/agent.o bin/session.o bin/graph.o bin/tree.o bin/maxranktree.o bin/roottree.o bin/cycletree.o bin/virus.o bin/contacttracer.o
	@echo 'Building target: main'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/cTrace bin/main.o bin/agent.o bin/graph.o bin/tree.o bin/session.o bin/maxranktree.o bin/roottree.o bin/cycletree.o bin/virus.o bin/contacttracer.o
	@echo 'Finished building target: main'
	@echo ' '

bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

bin/agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/agent.o src/Agent.cpp

bin/session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/session.o src/Session.cpp

bin/graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/graph.o src/Graph.cpp

bin/tree.o: src/Tree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/tree.o src/Tree.cpp

bin/maxranktree.o: src/MaxRankTree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/maxranktree.o src/MaxRankTree.cpp

bin/roottree.o: src/RootTree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/roottree.o src/RootTree.cpp

bin/cycletree.o: src/CycleTree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/cycletree.o src/CycleTree.cpp

bin/virus.o: src/Virus.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/virus.o src/Virus.cpp

bin/contacttracer.o: src/MaxRankTree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/contacttracer.o src/ContactTracer.cpp


