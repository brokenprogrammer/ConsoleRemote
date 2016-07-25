#!/usr/bin/python3

import socketserver
import logging
from .actions import *
from util.processhandler import ProcessHandler
from util.commandparser import CommandParser


class ServerHandler(socketserver.BaseRequestHandler):
    """
    The RequestHandler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """
    plib = ProcessHandler(logging.getLogger("ProcessHandler"))
    cmds = CommandParser(logging.getLogger("CommandParser"))

    def setup(self):
        """
        setups the connections by preparing all the available processes
        and commands that the server can manage.
        """
        logging.basicConfig(level=logging.INFO)

        # Registering known applications and path to their executables.
        self.plib.register_process(
            "VLC", "/Applications/VLC.app/Contents/MacOS/VLC")
        self.plib.register_process(
            "VLCWIN", "C:/Program Files (x86)/VideoLAN/VLC/vlc.exe")

        # Registering commands and functions to be associated with them.
        self.cmds.add_command("start movie", start_movie)
        self.cmds.add_command("kill", kill_process)

    def handle(self):
        """
        The connection handler that handles the connection between
        server and client.
        """
        logging.info("Handling a new request.")

        # Inifite loop that is active as long as the connection is persistent.
        while True:
            # self.request is the TCP socket connected to the client
            self.data = self.request.recv(1024).strip()

            # Brean the loop since connection is broken.
            if not self.data:
                break

            print("{} wrote:".format(self.client_address[0]))
            print(str(self.data, "utf-8"))

            # Temporary method of splitting the command into Command | option
            dataList = str(self.data, "utf-8").split(":", 1)
            if len(dataList) < 2:
                dataList.append("")

            # Parse the given message
            self.cmds.parse_command(dataList[0], dataList[1], self.plib)

            # just send back the same data, but upper-cased
            self.request.sendall(self.data.upper())
        logging.info("Client has disconnected.")
