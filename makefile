clean:
	del *.exe
	del *.obj
	del *.lib

build:
	cl /c Queue.c
	lib /OUT:TicTacToeLib.lib Queue.obj
	cl /c TicTacToe.c
	link TicTacToe.obj TicTacToeLib.lib 
