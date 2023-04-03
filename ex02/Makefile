# Name of the program.
NAME     := PmergeMe

# Sources and objects.
SRCS     := src/PmergeMe.cpp \
		src/Svector.cpp \
		src/Slist.cpp 

HDRS     := inc/PmergeMe.hpp \
	    inc/Svector.hpp \
	    inc/Slist.hpp

OBJS     := $(SRCS:.cpp=.o)

# Define all the compiling flags.
CXX      := c++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98

# Compile and create everything.
all: $(NAME) $(HDRS)

# Compile the program with the objects.
$(NAME): $(OBJS) $(HDRS)
	@$(CXX) $(OBJS) -o $@

# This won't run if the source files don't exist or are not modified.
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Rule to remove all the object files.
clean:
	@rm -f $(OBJS)
	@echo "Objects removed!"

# Rule to remove everything that has been created by the makefile.
fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed!"

# Rule to re-make everything.
re:     fclean all

# Makes sure that gnu make will still run even if files called
# clean / fclean / all and re already exist in the directory
.PHONY: all clean fclean re

