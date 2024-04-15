import socket
import json
import struct

SERVER_PORT = 8826
SERVER_IP = '127.0.0.1'

SUCCESS_CODE = 100
ERROR_CODE = 101

LOGIN_CODE = 1
SIGN_UP_CODE = 2

MSG_LEN_SIZE = 4

ERROR_MSG_KEY = 'message'
STATUS_KEY = 'status'

def connect_to_server():
    """
    The function will establish a TCP connection with the server
    # Note: Connection must be closed outside the function
    :return: server_sock
    :rtype: TCP socket
    """
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    server_sock.connect(server_address)
    return server_sock


def convert_to_byte_string(num):
    """
    Convert a number to a byte string representation and reverse it.

    Note: This function assumes that the input number can be represented
    as a 4-byte unsigned integer in little-endian byte order.

    :param num: The number to be converted to a byte string.
    :type num: int
    :return: The reversed byte string representation of the input number.
    :rtype: str
    """

    bytesBuffer = struct.pack("I", num)  # Pack the number into bytes

    # need to reverse string
    return bytesBuffer.decode('utf-8')[::-1]


def main():
    server_sock = None  # Initialize server_sock outside the try block
    try:
        # Attempt to connect to the server
        server_sock = connect_to_server()
        print("Connection successful")
    except Exception as e:
        print("Could not connect:", e)

    while True:
        try:
            message_type_choice = input("Type 'login' or 'signup': ").lower()
            message_data = {}
            message_type = 0

            if message_type_choice == 'login':
                # Prepare login message in JSON format
                username = input("Enter your username: ")
                password = input("Enter your password: ")
                message_type = LOGIN_CODE
                message_data = {"username": username, "password": password}

            elif message_type_choice == 'signup':
                # Prepare signup message in JSON format
                username = input("Enter your username: ")
                password = input("Enter your password: ")
                mail = input("Enter your email: ")
                address = input("Enter your address: ")
                phoneNumber = input("Enter your phone number: ")
                birthday = input("Enter your birthday: ")
                
                message_type = SIGN_UP_CODE
                
                message_data = {"username": username, "password": password, "email": mail, "address": address, "phoneNumber": phoneNumber, "birthday": birthday}
            else:
                message_type = ERROR_CODE

            # Add code and message length according to the format
            data = chr(message_type)

            len_of_data = len(json.dumps(message_data))
            data += convert_to_byte_string(len_of_data)

            data += json.dumps(message_data)

            # Send message to server as string
            server_sock.sendall(data.encode())

            # Receive response from server as json
            response = server_sock.recv(1024).decode()
            
            # first byte is the code that helps us determine the type of response
            server_data_code = response[0]

            # first 5 bytes are header from server, irrelevant in python demo client
            server_data = json.loads(response[5:])
            
            if server_data[STATUS_KEY] == ERROR_CODE:
                print(server_data[ERROR_MSG_KEY])
            elif server_data[STATUS_KEY] == SUCCESS_CODE:
                if server_data_code == chr(LOGIN_CODE):
                    print("User logged in successfully")
                if server_data_code == chr(SIGN_UP_CODE):
                    print("User signed up successfully")

        except Exception as e:
            print("Error:", e)
            server_sock.close()  # Close the connection


if __name__ == "__main__":
    main()
