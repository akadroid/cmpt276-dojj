all: IssueTracker

IssueTracker: main.o UI.o ScenarioControl.o Product.o ProductRelease.o ChangeItem.o ChangeRequest.o Customer.o
	g++ -Wall -Wpedantic -std=c++17 -o IssueTracker main.o UI.o ScenarioControl.o Product.o ProductRelease.o ChangeItem.o ChangeRequest.o Customer.o

main: main.cpp
	g++ -Wall -Wpedantic -std=c++17 -c main.cpp

UI: UI.h UI.cpp
	g++ -Wall -Wpedantic -std=c++17 -c UI.cpp

ScenarioControl: ScenarioControl.h ScenarioControl.cpp
	g++ -Wall -Wpedantic -std=c++17 -c ScenarioControl.cpp

Product: Product.h Product.cpp
	g++ -Wall -Wpedantic -std=c++17 -c Product.cpp

ProductRelease: ProductRelease.h ProductRelease.cpp
	g++ -Wall -Wpedantic -std=c++17 -c ProductRelease.cpp

ChangeItem: ChangeItem.h ChangeItem.cpp
	g++ -Wall -Wpedantic -std=c++17 -c ChangeItem.cpp

ChangeRequest: ChangeRequest.h ChangeRequest.cpp
	g++ -Wall -Wpedantic -std=c++17 -c ChangeRequest.cpp

Customer: Customer.h Customer.cpp
	g++ -Wall -Wpedantic -std=c++17 -c Customer.cpp

clean:
	rm -f IssueTracker *.o
