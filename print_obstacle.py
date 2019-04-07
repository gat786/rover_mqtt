def read_lines(port,callback):
    while True:
	    if(port.inWaiting()>0):
		    print(port.readline())
		else:
			print("No Danger")

