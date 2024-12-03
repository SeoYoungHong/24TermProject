# �����Ϸ��� �÷��� ����
CXX = g++
CXXFLAGS = -mconsole -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0

# �ҽ� ���� �� ��ü ����
SRCS = main.cpp Account.cpp ATM.cpp ATMInterface.cpp Bank.cpp Card.cpp History.cpp MoneyDict.cpp Session.cpp
OBJS = $(SRCS:.cpp=.o)

# ��� ����
TARGET = build/outDebug.exe

# �⺻ ���� Ÿ��
all: $(TARGET)

# ��ũ �ܰ�
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# �� �ҽ� ������ ���������� ������
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ŭ����
clean:
	rm -f $(OBJS) $(TARGET)
