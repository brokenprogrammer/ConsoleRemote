#!/usr/bin/python3


class CommandParseError(Exception):

    def __init__(self, msg):
        self.msg = msg

    def __str__(self):
        return self.msg


class CommandValueError(CommandParseError):
    """
    Raised if an invalid option value is encountered or an command
    already exists.
    """


class CommandParser():
    """
    The CommandParser class for our server.

    It stores all the commands and parses messages comparing commands
    and then execute functions depending on what command was parsed.
    """
    cmds = {}
    # TODO: Add logger.

    def __init__(self):
        print("DoIT")

    def add_command(self, command, function):
        if command not in self.cmds:
            # Add command to the command dict.
            self.cmds[command] = function
        else:
            # Raise error
            raise CommandValueError(("Error adding command: %s") % (command))

    def parse_command(self, command):
        if command in self.cmds:
            # Call the function for the specified command.
            self.cmds[command]()
        else:
            # Raise error
            raise CommandParseError(("Error parsing command: %s") % (command))

    def set_help_command(self, command):
        return

    def get_help_command(self, command):
        return
