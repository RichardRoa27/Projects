import hashlib
import bluetooth

def start_server(secret_key):
    """Starts the Bluetooth server, binds to a port, and listens for client connections."""
    server_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    port = 1  # RFCOMM port to bind, can generally be between 1 and 30
    server_sock.bind(("", port))
    server_sock.listen(1)
    print("Waiting for a connection on RFCOMM port", port)

    client_sock, client_info = server_sock.accept()
    print("Accepted connection from ", client_info)

    try:
        manage_data_transfer(client_sock)
    except Exception as e:
        print("Error during data transfer:", e)
    finally:
        client_sock.close()
        server_sock.close()

def manage_data_transfer(client_sock):
    """Manages the data transfer process including receiving, acknowledging, and verifying data integrity."""
    size_b = client_sock.recv(2048)  # First, receive the data size
    size = int(size_b.decode())
    client_sock.send(size_b)  # Send ACK for size

    data = receive_data(client_sock, size)
    hash_obj = hashlib.sha256(data)
    hashed_data = hash_obj.digest()
    print("Received data hash:", hashed_data)

    client_sock.send(hashed_data)  # Send hash back to client for integrity check

def receive_data(client_sock, expected_size):
    """Receives data in chunks from the client until the expected size is met."""
    data = b""
    while len(data) < expected_size:
        new_data = client_sock.recv(2048)
        if not new_data:
            break
        data += new_data
        print("Received:", len(new_data), "bytes")
    return data

def verify_user():
    """Asks the user for a key and verifies it against the predefined secret key to authorize server access."""
    secret_key = "54547"  # Secret key should be a string for security reasons
    user_input = input('Enter key: ')
    return user_input == secret_key

if __name__ == "__main__":
    if verify_user():
        start_server()
    else:
        print("Access denied")
