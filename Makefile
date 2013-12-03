.PHONY: all clean

CXXFLAGS = -O3 -std=c++11

all: libjsonpp.a

OBJS = json_st.o json.tab.o lex.yy.o

BISON = /usr/local/Cellar/bison/3.0.1/bin/bison


test: test.o
	$(CXX) -std=c++11 -o $@ $^

json.tab.c: json.y
	$(BISON) -d json.y

json.tab.o: json.tab.c
	$(CXX) $(CXXFLAGS) -c $^

lex.yy.c: json.l
	flex json.l

lex.yy.o: lex.yy.c
	$(CXX) $(CXXFLAGS) -c $^

libjsonpp.a: $(OBJS)
	ar cr $@ $(OBJS)


clean:
	rm -rf json.tab.c json.tab.h lex.yy.c test $(OBJS) libjsonpp.a
