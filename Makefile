# 컴파일러와 플래그 설정
CXX = g++
CXXFLAGS = -mconsole -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0

# 소스 파일 및 객체 파일
SRCS = main.cpp Account.cpp ATM.cpp ATMInterface.cpp Bank.cpp Card.cpp History.cpp MoneyDict.cpp Session.cpp
OBJS = $(SRCS:.cpp=.o)

# 출력 파일
TARGET = build/outDebug.exe

# 기본 빌드 타겟
all: $(TARGET)

# 링크 단계
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 각 소스 파일을 개별적으로 컴파일
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 클린업
clean:
	rm -f $(OBJS) $(TARGET)
