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
    plib = None
    cmds = None

    def setup(self):
        logging.basicConfig(level=logging.INFO)

        self.plib = ProcessHandler(logging.getLogger("ProcessHandler"))
        self.cmds = CommandParser(logging.getLogger("CommandParser"))
        # Registering known applications and path to their executables.
        self.plib.register_process(
            "VLC", "/Applications/VLC.app/Contents/MacOS/VLC")
        self.plib.register_process(
            "VLCWIN", "C:/Program Files (x86)/VideoLAN/VLC/vlc.exe")
        # Registering commands and functions to be associated with them.
        self.cmds.add_command("start movie", start_movie)
        self.cmds.add_command("kill", kill_process)

        # cmds.parse_command("start movie", plib)

    def handle(self):
        print("Handle requests")

        # self.request is the TCP socket connected to the client
        self.data = self.request.recv(1024).strip()
        print("{} wrote:".format(self.client_address[0]))
        print(str(self.data, "utf-8"))

        self.cmds.parse_command(str(self.data, "utf-8"), self.plib)

        # just send back the same data, but upper-cased
        self.request.sendall(self.data.upper())
