bcview:bcview.c
	gcc bcview.c -o bcview
install:
	cp ./bcview /usr/bin/
clean:
	rm -rf ./bcview
	rm -rf /usr/bin/bcview
