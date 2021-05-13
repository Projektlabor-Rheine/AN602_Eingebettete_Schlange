import websocket
import json

try:
    import thread
except ImportError:
    import _thread as thread


class Packet:

    # Takes the data of the packet
    def __init__(self, jsonData):
        self.__json = jsonData

    # Returns a given object if it is firstly given and secondly has the provided type; otherwise returns none
    def get_if_type(self, key: str, required_type: type):
        # Gets the object
        obj = self.__json[key]

        # Checks if the object has the required type
        if isinstance(obj, required_type):
            return obj
        return None

    # Returns a given object if it is given; otherwise raises an exception
    def get_if_type_else_exception(self, key: str, required_type: type):
        # Gets the element
        val = self.get_if_type(key, required_type)

        # Checks if the value is invalid
        if val is None:
            raise Exception

        return val


class CACConnection:
    def __init__(self, url, evt_connect=None, evt_disconnect=None):
        self.url = url
        self.evt_connect = evt_connect
        self.evt_disconnect = evt_disconnect
        self.ws = None
        self.__registeredPackets = {}

    # Starts or restarts the websocket-connection
    def connect(self):
        # Creates the websocket
        self.ws = websocket.WebSocketApp(self.url, on_open=self.__on_open, on_message=self.__on_packet,
                                         on_close=self.__on_close)
        # Connects the socket
        self.ws.run_forever()

    '''
    Register a packet-handler
    If a packet with that id gets received, the corresponding handler will
    be called with the parsed packet
    '''

    def registerPacket(self, packet_id: int, handler: staticmethod):
        self.__registeredPackets[packet_id] = handler

    # Event handler for the open socket event
    def __on_open(self, _):
        # Executes the connect event if it is set
        if self.evt_connect:
            self.evt_connect()

    # Event handler for the close socket event
    def __on_close(self, _):
        # Executes the disconnect event if it is set
        if self.evt_disconnect:
            self.evt_disconnect()
        # Reconnects
        self.connect()

    # Event handler for the packet event
    def __on_packet(self, _, packet):
        try:
            # Tries to load the packet as a json-object
            parsed = json.loads(packet)

            # Gets the handler and data
            handler = self.__registeredPackets[parsed["id"]]
            data = parsed["data"]

            # Checks that the data is given
            if data is None or not isinstance(data, dict):
                return

            # Checks if the handler exists
            if handler is None:
                return

            # Executes the handler with the packet
            pkt = Packet(data)
            handler(pkt)

        except:
            pass
