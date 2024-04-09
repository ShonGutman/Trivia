import socket
import json

SERVER_PORT = 8826
SERVER_IP = '127.0.0.1'

LOGIN_CODE = 1
SIGN_UP_CODE = 2
ERROR_CODE = 99

MSG_LEN_SIZE = 4


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
                message_type = SIGN_UP_CODE

                message_data = {"username": username, "password": password, "mail": mail}
            else:
                message_type = ERROR_CODE

            # Add code and message length according to the format
            data = str(message_type)

            len_of_data = len(json.dumps(message_data))
            if len_of_data <= MSG_LEN_SIZE:
                data += (str(len_of_data).zfill(MSG_LEN_SIZE))  # Pad message length
            else:
                raise ValueError("Message length exceeds maximum allowed size")

            data += json.dumps(message_data)

            # Send message to server as string
            server_sock.sendall(data.encode())

            # Receive response from server as json
            server_data = server_sock.recv(1024).decode()
            if server_data == str(ERROR_CODE):
                raise Exception("Error occurred on the server side")
            elif server_data == str(SIGN_UP_CODE):
                print("Signup!")
            elif server_data == str(LOGIN_CODE):
                print("Login!")

        except Exception as e:
            print("Error:", e)
            server_sock.close()  # Close the connection


if __name__ == "__main__":
    main()
