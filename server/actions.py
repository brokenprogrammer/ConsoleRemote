#!/usr/bin/python3

import subprocess
import time


def start_movie(mediaPath):
    print("Its live")
    vlc = subprocess.Popen(["/Applications/VLC.app/Contents/MacOS/VLC",
                           "/Users/oskarmendel/Music/Red Hot Chilli Peppers - Greatest Hits [Bubanee]"])
    killsoon(vlc)

def killsoon(anarg):
    time.sleep(5)
    anarg.kill()
