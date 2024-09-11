
SRCDIR+=src
CXXFLAGS += -Iinclude

SRC+=    $(SRCDIR)/AffectArray.cpp		\
	$(SRCDIR)/Armory.cpp		\
	$(SRCDIR)/Attack.cpp		\
	$(SRCDIR)/BaseAttribute.cpp	\
	$(SRCDIR)/Effects.cpp		\
	$(SRCDIR)/Factory.cpp		\
	$(SRCDIR)/Ground.cpp		\
	$(SRCDIR)/IronDefines.cpp	\
	$(SRCDIR)/IronIO.cpp		\
	$(SRCDIR)/Player.cpp		\
	$(SRCDIR)/Tile.cpp

OBJ = $(SRC:.cpp=.o)

NAME += IronGame

all: $(NAME)

$(NAME): $(OBJ)
		g++ $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean:         clean
		rm -rf $(NAME)

re:             fclean all

.PHONY: all clean fclean re
