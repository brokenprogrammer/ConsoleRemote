#!/usr/bin/python3

import subprocess
import time


def start_movie(processHandler):
    print("Its live")
    vlc = subprocess.Popen([processHandler.processPaths["VLC"],
                           "/Users/oskarmendel/Music/Red Hot Chilli Peppers - Greatest Hits [Bubanee]"])
    processHandler.processes["VLC"] = vlc
    killsoon(vlc)


def kill_process(processHandler, pname):
    process = processHandler.processes[pname]
    process.kill()
    processHandler.processes[pname] = None


def killsoon(anarg):
    time.sleep(5)
    anarg.kill()
