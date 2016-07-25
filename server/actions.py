#!/usr/bin/python3

import subprocess
import time


def start_movie(processHandler, option):
    print("Its live")
    vlc = subprocess.Popen([processHandler.processPaths["VLCWIN"], option])
    processHandler.processes["VLC"] = vlc


def kill_process(processHandler, pname):
    process = processHandler.processes[pname]
    process.kill()
    processHandler.processes[pname] = None


def killsoon(anarg):
    time.sleep(5)
    anarg.kill()
