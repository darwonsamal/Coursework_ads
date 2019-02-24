clean:
	del *.exe
	del *.obj
	del *.lib

build:
	cl /c CircularQueue.c
	lib /OUT:TicTacToeLib.lib CircularQueue.obj
	cl /c TicTacToe.c
	link TicTacToe.obj TicTacToeLib.lib 
