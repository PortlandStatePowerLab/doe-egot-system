# doe-egot-dtm
Engery Grid of Things: Distributed Trust Management 

## DTM http Server and DCM http Client 

Developed by Whitman Spitzer 

Raspi implementation for the DTM and DCM Raspberry Pi prototypes, written in Python 3, using standard library objects. Find in DTM-Server > raspi_implementation

Loopback implementation for non-raspi testing and development, running client and server simultaneously on one machine with `localhost`. Find in DTM-Server > loopback_implementation


### Some Loopback Instructions!

In DTM-Server > loopback_implementation > server/testing there is a python file called `DTMServer_loopback1.py`. This is the loopback version of the DTM http server, 
which substitutes random numbers for the GPU temperature data the raspi implementation uses.

DTM-Server > loopback_implementation > client/testing contains `httpClient_loopback1.py`, which is the loopback version of the DCM client.

These programs function and interact exactly like the raspi versions, except that they are two scripts running on one machine, and communicating
with a web browser on that same machine. When you have them running, go to your browser and copy/paste `localhost:8887` into the URL to bring
up the html page. 

The way I did this was the Multirun plugin in for the PyCharm IDE. Using the IDE, I installed the plugin, and created a `Run > Edit Configurations > Multirun` configuration
for the scripts. This required first creating simple Python configurations for each of the scripts separately to then add to the multirun configuration. For each of them 
I checked the box marked `Emulate Terminal in Output Console`. In the multirun configuration pane, check the box in the upper right marked `Allow Parallel Run`. This will let 2 scripts (client and server) run simultaneously for debugging. Woo! 

Anyways, good luck! Also sidebar the loopback DTM server updates the `TrustLog_loopback.xml` file ever 10 seconds (every other client contact, you can mess with this in appendLog(), its an if with a % 2 operator to execute every other instance of the global posts_received counter) so be careful about that! (and don't delete the entire contents of the file or you might mess up the XML parsing. Also, if you add a new .xml log file, make sure to copy/paste the original, minus all but the first DCMContact instance, and then change the name in the appendLog() method in the server script to match your new file). 

### Some Raspi Instructions! 

First, clone this repo to a wifi enable raspberry pi.

Next, find the IP address of that Raspberry Pi. You can use the command `hostname -I`

In the DTM-Server > raspi_implementation > server/testing folder, theres a python file, called `DTMServer3.py`

Open it from the raspi and edit `host_name` to be the raspi's IP address

Now you can run it from the command line by typing `python3 DTMServer3.py`, which will start the DTM Server. 
This should not require you to add any dependencies (unless your python version isn't up to date).

Now do the same thing from your other wifi enabled raspi, except this time
in the client/testing folder, edit the `httpClient1.py` file,
change the  `host_name` to the DTM hostname. NOT the DCM (second raspi).
You're editing the `httpClient1.py` file to include the IP address of the other raspi, not itself. 
Now if you run it (while the DTM server is running), with `python3 httpClient1.py` 
(the default python version on raspi's isn't 3)
The DCM should connect to the DTM server and start sending XML POST requests every 5 seconds, 
which the DTM server will be parsing, adding some information, and storing in the `TrustLogv2.xml file`.

The DTM server will also update a webpage, visible from any browser on the network by pasting
`[IP address XX.XX.XX.etc]:8889`, where `8889` is the port number in the code (but it can be changed).

Also probably read the stuff at the end of the loopback implementation instructions about the appendLog() .xml file modification, it all holds true 
except that the Raspi DTM server only updates the log once per minute instead of every 10 seconds and the logfile name is different.

Good luck :) let me know if you have any questions, this was super fun to build!

