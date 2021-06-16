import CACConnection


# Starts the connection to the cac
def main():
    global con
    # Creates the cac-connection
    con = CACConnection.CACConnection("ws://localhost/ws/pi")

    # Registers the key-packet-handler with the packet-id 0
    con.registerPacket(0, handleKeyupdate)

    # Starts the cac-connection to the server
    con.connect()


# Waits for a key-update packet
def handleKeyupdate(pkt: CACConnection.Packet):
    # Defines all keys that are required inside the packet
    keys = ["w", "a", "s", "d", "up", "down", "left", "right"]

    try:
        # Maps them to their respective values or throws an exception
        keys = dict(map(lambda k: [k, pkt.get_if_type_else_exception(k, bool)], keys))

        '''
        Keys will now contain a dictionary with "<Keyname>": <True/False>

        Access it by keys["<keyname>"]
        Eg: keys["w"] would now return either True or False
        '''
    except:

        # This will execute if the packet did'nt contain all key's or one key wasn't valid

        pass


main()